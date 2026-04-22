#include "rclcpp/rclcpp.hpp"
#include "config/config.h"
#include "camera_stream/msg/share_image.hpp"
#include "vision_detector/msg/drone_diff.hpp"
#include "vision_detector/msg/gimbal_info.hpp"
#include "ekf_tracker.h"
#include <opencv2/opencv.hpp>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <chrono>
#include <deque>
#include <cmath>
extern std::vector<cv::Point2f> detectLaserSpot(const cv::Mat& frame);
extern std::vector<cv::Point2f> detectLaserModule(const cv::Mat& frame);
const double LOST_RETURN_TIMEOUT = 3000; // 目标丢失后，超过这个时间（毫秒）没有重新发现目标，就认为需要回中 
static bool is_valid_frame = false;
// --- 云台历史状态缓存 ---
struct GimbalState {
    uint32_t timestamp_us;
    float yaw;
    float pitch;
};

// 【极其重要】：控制 Pitch 轴的正负号换算
// 图像中 Y 轴向下增长。如果你的云台抬头(向上) Pitch 增加，请将此设为 -1.0f；
// 如果你的云台低头(向下) Pitch 增加，请将其设为 1.0f。
const float PITCH_DIR = 1.0f;
const float YAW_DIR = -1.0f; // 如果你的云台左转 Yaw 增加，请设为 1.0f；右转 Yaw 增加，请设为 -1.0f。

static void mouseCallback(int event, int x, int y, int flags, void* userdata);

class VisionDroneDetector : public rclcpp::Node
{
public:
    VisionDroneDetector(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动(相机内参绝对角度前馈版本).", name.c_str());

        auto qos = rclcpp::QoS(2)
            .best_effort();                    // 不保证送达，适合实时数据
        command_subscribe_ = this->create_subscription<camera_stream::msg::ShareImage>(
            "share_image", qos, std::bind(&VisionDroneDetector::command_callback, this, std::placeholders::_1));
            
        drone_diff_publisher_ = this->create_publisher<vision_detector::msg::DroneDiff>("drone_diff", 10);
        
        gimbal_subscribe_ = this->create_subscription<vision_detector::msg::GimbalInfo>(
            "gimbal_info", 10, std::bind(&VisionDroneDetector::gimbal_callback, this, std::placeholders::_1));
            
        timer_ = this->create_wall_timer(
        std::chrono::milliseconds(1), 
        std::bind(&VisionDroneDetector::timer_callback_, this));
        
        laser_center_point_ = cv::Point(LASER_DRONE_CENTER_X, LASER_DRONE_CENTER_Y);
        camera_center_point_ = cv::Point2f(camera_matrix_.at<double>(0, 2), camera_matrix_.at<double>(1, 2));
    }
    
    ~VisionDroneDetector() override {
        detach_cached_shm();
    }

    cv::Point laser_center_point_;
    cv::Point2f camera_center_point_;
    cv::Mat camera_matrix_ = CAMERA_MATRIX;
    cv::Mat distort_coeffs_ = DISTORT_COEFFS;

private:
    class EKFTracker tracker_;
    
    int init_hit_count_ = 0;
    cv::Point2f init_last_pos_pix_ = cv::Point2f(-1, -1);
    const int REQUIRED_INIT_FRAMES = 5;

    std::deque<GimbalState> gimbal_history_;

    // 平滑处理的数据
    uint32_t smoothed_rtt_us_ = 12000; 
    float smoothed_v_yaw_ = 0.0f;
    float smoothed_v_pitch_ = 0.0f;
    
    uint32_t current_rtt_us_ = 12000; 
    float current_real_yaw_ = 0.0;
    float current_real_pitch_ = 0.0;

    rclcpp::Subscription<camera_stream::msg::ShareImage>::SharedPtr command_subscribe_;
    rclcpp::Publisher<vision_detector::msg::DroneDiff>::SharedPtr drone_diff_publisher_;
    rclcpp::Subscription<vision_detector::msg::GimbalInfo>::SharedPtr gimbal_subscribe_;
    rclcpp::TimerBase::SharedPtr timer_;
    
    cv::Mat now_frame_;
    bool now_frame_is_using_ = false;
    rclcpp::Time last_img_msg_stamp_;
    rclcpp::Time last_target_time_; 

    // --- 新增：基于相机内参的坐标转换核心函数 ---
    
    // 1. 像素坐标 -> 去畸变的物理角度偏差 (单位:度)
    cv::Point2f getAngleOffset(const cv::Point2f& pt) {
        std::vector<cv::Point2f> src = {pt};
        std::vector<cv::Point2f> dst;
        // undistortPoints 返回的是归一化相机坐标 (x,y)，相当于 (u-cx)/fx, (v-cy)/fy
        cv::undistortPoints(src, dst, camera_matrix_, distort_coeffs_);
        
        // 计算真实偏角
        float yaw_offset = std::atan(dst[0].x) * 180.0 / CV_PI * YAW_DIR; // 乘以方向系数，调整正负号
        float pitch_offset = std::atan(dst[0].y) * 180.0 / CV_PI * PITCH_DIR; 
        
        return cv::Point2f(yaw_offset, pitch_offset);
    }

    // 2. 物理角度偏差 -> 带畸变的像素坐标 (用于反向投影画图)
    cv::Point2f getPixelFromAngle(const cv::Point2f& angle_offset) {
        // 反解出归一化平面的 x, y
        float x_norm = std::tan(angle_offset.x / YAW_DIR * CV_PI / 180.0);
        float y_norm = std::tan(angle_offset.y / PITCH_DIR * CV_PI / 180.0);
        
        std::vector<cv::Point3f> objectPoints = {cv::Point3f(x_norm, y_norm, 1.0f)};
        std::vector<cv::Point2f> imagePoints;
        cv::Mat rvec = cv::Mat::zeros(3, 1, CV_64F);
        cv::Mat tvec = cv::Mat::zeros(3, 1, CV_64F);
        
        // 投影回像素平面，重新带入畸变
        cv::projectPoints(objectPoints, rvec, tvec, camera_matrix_, distort_coeffs_, imagePoints);
        return imagePoints[0];
    }
    void gimbal_callback(const vision_detector::msg::GimbalInfo::SharedPtr msg);
    void command_callback(const camera_stream::msg::ShareImage::SharedPtr msg);
    void timer_callback_(void);

    // 最终下发目标二次滤波状态（角度单位：deg）
    float cmd_target_yaw_filt_ = 0.0f;
    float cmd_target_pitch_filt_ = 0.0f;
    bool cmd_filt_inited_ = false;

    // 参数：可按现场再调
    const float CMD_LPF_ALPHA_ = 0.50f;          // 0.30 -> 0.50，提升跟手性
    const float CMD_MAX_RATE_DPS_ = 260.0f;      // 180 -> 260，放宽每帧变化上限
    const float CMD_DEADZONE_DEG_ = 0.01f;      // 0.005 -> 0.002，减小迟滞

    // 自适应前馈参数
    const float LEAD_BASE_S_ = 0.050f;           // 基础超前时间
    const float LEAD_GAIN_S_ = 0.002f;          // 随速度增加的超前增益
    const float LEAD_MAX_S_ = 0.90f;            // 超前上限

    // 稳态抑制参数
    const float STEADY_VEL_TH_DPS_ = 0.35f;      // 稳态速度阈值
    const float STEADY_ERR_TH_DEG_ = 0.1f;      // 稳态误差阈值
    const float STEADY_LEAD_SCALE_ = 0.15f;      // 稳态前馈缩放
    const float STEADY_LPF_ALPHA_ = 0.22f;       // 稳态更重低通
    const float STEADY_DEADZONE_DEG_ = 0.03f;    // 稳态更大死区

    // SHM 缓存（避免每帧 shmat/shmdt）
    int cached_shm_id_ = -1;
    void* cached_shm_ptr_ = nullptr;
    size_t cached_shm_size_ = 0;

    bool ensure_shm_mapped(int shm_id, size_t shm_size) {
        if (cached_shm_ptr_ != nullptr && cached_shm_id_ == shm_id) {
            if (shm_size > cached_shm_size_) cached_shm_size_ = shm_size;
            return true;
        }

        detach_cached_shm();

        void* ptr = shmat(shm_id, nullptr, 0);
        if (ptr == (void*)-1) {
            cached_shm_ptr_ = nullptr;
            cached_shm_id_ = -1;
            cached_shm_size_ = 0;
            return false;
        }

        cached_shm_ptr_ = ptr;
        cached_shm_id_ = shm_id;
        cached_shm_size_ = shm_size;
        return true;
    }

    void detach_cached_shm() {
        if (cached_shm_ptr_ != nullptr) {
            shmdt(cached_shm_ptr_);
            cached_shm_ptr_ = nullptr;
        }
        cached_shm_id_ = -1;
        cached_shm_size_ = 0;
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VisionDroneDetector>("node_vision_drone_detector");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

void VisionDroneDetector::command_callback(const camera_stream::msg::ShareImage::SharedPtr msg){
    rclcpp::Time start = this->now();

    if (msg->enable == 0 || msg->camera_select != CAMERA_SELECT_DRONE) {
        is_valid_frame = false;
        return;
    }

    const int64_t now_ts_us = this->now().nanoseconds() / 1000;
    if (std::abs(now_ts_us - static_cast<int64_t>(msg->timestamp_us)) > 100000) {
        return; // 丢弃过旧帧
    }

    const int h = msg->height;
    const int w = msg->width;
    const size_t expect_size = static_cast<size_t>(h) * static_cast<size_t>(w) * 3;
    if (h <= 0 || w <= 0 || msg->shm_size < expect_size) return;

    is_valid_frame = true;

    if (!ensure_shm_mapped(msg->shm_id, msg->shm_size)) {
        RCLCPP_ERROR_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "Failed to map shared memory");
        return;
    }

    if (!now_frame_is_using_) {
        now_frame_is_using_ = true;

        if (now_frame_.rows != h || now_frame_.cols != w || now_frame_.type() != CV_8UC3) {
            now_frame_.create(h, w, CV_8UC3);
        }

        std::memcpy(now_frame_.data, cached_shm_ptr_, expect_size);
        last_img_msg_stamp_ = rclcpp::Time(msg->timestamp_us * 1000ULL);

        now_frame_is_using_ = false;
    }

    rclcpp::Time end = this->now();
    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
        "command_callback cost: %ld ms", (end - start).nanoseconds() / 1000000
    );
}

void VisionDroneDetector::gimbal_callback(const vision_detector::msg::GimbalInfo::SharedPtr msg) {
    rclcpp::Time start = this->now();
    uint32_t now_us_32 = (uint32_t)(this->now().nanoseconds() / 1000); 
    
    if (msg->last_pc_timestamp_us != 0) {
        uint32_t raw_rtt = now_us_32 - msg->last_pc_timestamp_us;
        if (raw_rtt < 500000) { // 剔除异常大跳变
            smoothed_rtt_us_ = 0.9 * smoothed_rtt_us_ + 0.1 * raw_rtt;
            // 修复 Bug 1：同步更新 current_rtt_us_ 用于打印，但核心算法以后全用 smoothed_rtt_us_
            current_rtt_us_ = raw_rtt; 
        }
    }

    current_real_yaw_ = msg->current_yaw;
    current_real_pitch_ = msg->current_pitch;

    // 修复 Bug 2：【极其重要】推算云台真正处于当前角度的物理时间！
    // 物理时间 ≈ 收到数据的现在 - (一半的往返延迟)
    uint32_t physical_gimbal_time_us = now_us_32 - (smoothed_rtt_us_ / 2);

    GimbalState st = {physical_gimbal_time_us, msg->current_yaw, msg->current_pitch};
    gimbal_history_.push_back(st);
    if (gimbal_history_.size() > 50) gimbal_history_.pop_front();
    
    // 每秒打印一次，不要刷屏
    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
         "回传: yaw=%.2f, pitch=%.2f, RTT=%u us, 平滑RTT=%u us",
         st.yaw, st.pitch, current_rtt_us_, smoothed_rtt_us_);
    rclcpp::Time end = this->now();
    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "gimbal_callback 处理时间: %ld ms", (end - start).nanoseconds() / 1000000);
}

void VisionDroneDetector::timer_callback_(void){
    rclcpp::Time start = this->now();
    uint64_t img_time_ns = last_img_msg_stamp_.nanoseconds(); 
    if (img_time_ns == 0) {return; }
    
    uint32_t img_time_us_32 = (uint32_t)(img_time_ns / 1000);
    static uint32_t last_img_time_us_32 = img_time_us_32;
    if (img_time_us_32 == last_img_time_us_32) return; // 图像没变，不许计算

    double dt = (img_time_us_32 - last_img_time_us_32) / 1000000.0;
    if (dt <= 0.0 || dt > 0.1) dt = 0.01; // 防止异常 dt 导致输出突变
    last_img_time_us_32 = img_time_us_32;

    

    if(now_frame_is_using_){return;}
    now_frame_is_using_ = true;
    if(now_frame_.empty()){
        now_frame_is_using_ = false;
        
        // 没收到图也强行弹个窗口告诉你！
        cv::Mat black_img = cv::Mat::zeros(480, 640, CV_8UC3);
        cv::putText(black_img, "WAITING FOR CAMERA STREAM...", cv::Point(50, 240), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
        cv::imshow("Vision Debugger", black_img);
        cv::waitKey(1);
        return;
    }
    cv::Mat display_frame = now_frame_.clone();
    now_frame_is_using_ = false;


    GimbalState matched_state = {img_time_us_32, current_real_yaw_, current_real_pitch_};
    uint32_t min_diff = 0xFFFFFFFF;
    for (const auto& st : gimbal_history_) {
        uint32_t diff = std::abs((int32_t)(st.timestamp_us - img_time_us_32));
        if (diff < min_diff) {
            min_diff = diff;
            matched_state = st; 
        }
    }
    rclcpp::Time detect_time_start = this->now();
    //std::vector<cv::Point2f> candidates = detectLaserSpot(display_frame);
    std::vector<cv::Point2f> candidates = detectLaserModule(display_frame);
    rclcpp::Time detect_time_end = this->now();
    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "目标检测时间: %ld ms", (detect_time_end - detect_time_start).nanoseconds() / 1000000);

    tracker_.predict(dt); 

    if (!tracker_.isInitialized()) {
        if (!candidates.empty()) {
            cv::Point2f best_cand_pix = candidates[0];
            if (init_last_pos_pix_.x >= 0) {
                double min_d = 1e9;
                for (auto& pt : candidates) {
                    double d = cv::norm(pt - init_last_pos_pix_);
                    if (d < min_d) { min_d = d; best_cand_pix = pt; }
                }
                if (min_d < 150.0) { 
                    init_hit_count_++;
                } else {
                    init_hit_count_ = 1;
                }
            } else {
                init_hit_count_ = 1;
            }
            init_last_pos_pix_ = best_cand_pix;
            cv::circle(display_frame, cv::Point(cvRound(best_cand_pix.x), cvRound(best_cand_pix.y)), 6, cv::Scalar(0, 255, 255), 2);

            if (init_hit_count_ >= REQUIRED_INIT_FRAMES) {
                // 【核心转换1】：初始化 EKF 时，通过相机光心计算目标的绝对世界角度
                cv::Point2f target_angle_offset = getAngleOffset(best_cand_pix);
                float abs_yaw = matched_state.yaw + target_angle_offset.x;
                float abs_pitch = matched_state.pitch + target_angle_offset.y;
                
                tracker_.init(cv::Point2f(abs_yaw, abs_pitch));
                
                init_hit_count_ = 0;
                init_last_pos_pix_ = cv::Point2f(-1, -1);
                RCLCPP_INFO(this->get_logger(), "已确认目标，开始内参绝对角度追踪！");
            }
        } else {
            init_hit_count_ = 0;
            init_last_pos_pix_ = cv::Point2f(-1, -1);
        }
        
    } else {
        cv::Point2f measured_abs(-1000, -1000); 
        
        if (!candidates.empty()) {
            // 【核心转换2】：将 EKF 预测的世界绝对角度，反向投影回当前画面像素，用于距离关联筛选
            cv::Point2f est_pos_abs = tracker_.getEstimatedPos(); 
            cv::Point2f predicted_angle_offset(
                est_pos_abs.x - matched_state.yaw, 
                est_pos_abs.y - matched_state.pitch
            );
            cv::Point2f predicted_pix = getPixelFromAngle(predicted_angle_offset);

            double min_dist = 200.0; 
            cv::Point2f best_cand_pix(-1, -1);
            for (auto& pt : candidates) {
                cv::circle(display_frame, cv::Point(cvRound(pt.x), cvRound(pt.y)), 4, cv::Scalar(255, 0, 255), 2);
                double dist = cv::norm(pt - predicted_pix);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cand_pix = pt;
                }
            }

            if (best_cand_pix.x >= 0) {
                // 【核心转换3】：将匹配到的光斑像素点，转为绝对坐标喂给 EKF 测量器
                cv::Point2f target_angle_offset = getAngleOffset(best_cand_pix);
                measured_abs = cv::Point2f(
                    matched_state.yaw + target_angle_offset.x, 
                    matched_state.pitch + target_angle_offset.y
                );
                last_target_time_ = this->now();
                cv::circle(display_frame, cv::Point(cvRound(best_cand_pix.x), cvRound(best_cand_pix.y)), 4, cv::Scalar(0, 0, 255), 2);
            }
            
        }

        if (measured_abs.x > -900) {
            tracker_.update(measured_abs);
        } else {
            tracker_.handleLost(); 
        }
    }


    // --- 增强可视化信息展示 ---

    // 1. 绘制一个半透明的状态背景区域（左上角）

    int base_y = 35;
    int step_y = 25;
    cv::Scalar text_color(255, 255, 255); // 白色文字
    double font_scale = 0.5;

    // 2. 打印云台当前角度 (Gimbal Feedback)
    std::string gimbal_str = cv::format("Gimbal Now:  Y:%.2f  P:%.2f", matched_state.yaw, matched_state.pitch);
    cv::putText(display_frame, gimbal_str, cv::Point(20, base_y), cv::FONT_HERSHEY_SIMPLEX, font_scale, text_color, 1);

    // 3. 打印追踪状态
    std::string status_str = tracker_.isInitialized() ? "STATUS: TRACKING" : "STATUS: SEARCHING";
    cv::Scalar status_color = tracker_.isInitialized() ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255);
    cv::putText(display_frame, status_str, cv::Point(20, base_y + step_y), cv::FONT_HERSHEY_SIMPLEX, font_scale, status_color, 1);
    uint32_t now_us_32 = (uint32_t)(this->now().nanoseconds() / 1000);
    if (tracker_.isInitialized()) {
        // 计算预测步长
        double process_delay = (now_us_32 - img_time_us_32) / 1000000.0;
        double uart_delay = (smoothed_rtt_us_ / 2.0) / 1000000.0;

        cv::Point2f est_pos = tracker_.getEstimatedPos(); 
        cv::Point2f est_vel = tracker_.getEstimatedVel(); 

        // 速度滤波更“跟手”
        smoothed_v_yaw_ = 0.55f * smoothed_v_yaw_ + 0.45f * est_vel.x;     // 原 0.7/0.3
        smoothed_v_pitch_ = 0.55f * smoothed_v_pitch_ + 0.45f * est_vel.y; // 原 0.7/0.3

        // 自适应前馈：速度越大，超前越多
        float vel_mag = std::sqrt(smoothed_v_yaw_ * smoothed_v_yaw_ + smoothed_v_pitch_ * smoothed_v_pitch_);
        cv::Point2f laser_offset_angle = getAngleOffset(laser_center_point_);
        float err_yaw = est_pos.x - (matched_state.yaw + laser_offset_angle.x);
        float err_pitch = est_pos.y - (matched_state.pitch + laser_offset_angle.y);
        float err_mag = std::sqrt(err_yaw * err_yaw + err_pitch * err_pitch);

        bool is_steady = (vel_mag < STEADY_VEL_TH_DPS_) && (err_mag < STEADY_ERR_TH_DEG_);

        float lead_s = LEAD_BASE_S_ + LEAD_GAIN_S_ * vel_mag;
        if (is_steady) lead_s *= STEADY_LEAD_SCALE_; // 关键：稳态抑制前馈
        lead_s = std::clamp(lead_s, 0.0f, LEAD_MAX_S_);

        double predict_dt = process_delay + uart_delay + lead_s;
        if (predict_dt < 0.0) predict_dt = 0.0;
        if (predict_dt > 0.30) predict_dt = 0.30;

        float raw_target_yaw = (est_pos.x + smoothed_v_yaw_ * predict_dt) - laser_offset_angle.x;
        float raw_target_pitch = (est_pos.y + smoothed_v_pitch_ * predict_dt) - laser_offset_angle.y;

        if (!cmd_filt_inited_) {
            cmd_target_yaw_filt_ = raw_target_yaw;
            cmd_target_pitch_filt_ = raw_target_pitch;
            cmd_filt_inited_ = true;
        }

        float max_step = CMD_MAX_RATE_DPS_ * static_cast<float>(dt);
        float dy = std::clamp(raw_target_yaw - cmd_target_yaw_filt_, -max_step, max_step);
        float dp = std::clamp(raw_target_pitch - cmd_target_pitch_filt_, -max_step, max_step);

        float alpha = is_steady ? STEADY_LPF_ALPHA_ : CMD_LPF_ALPHA_;
        cmd_target_yaw_filt_ += alpha * dy;
        cmd_target_pitch_filt_ += alpha * dp;

        float out_yaw = cmd_target_yaw_filt_;
        float out_pitch = cmd_target_pitch_filt_;
        float deadzone = is_steady ? STEADY_DEADZONE_DEG_ : CMD_DEADZONE_DEG_;
        if (std::fabs(out_yaw - current_real_yaw_) < deadzone) out_yaw = current_real_yaw_;
        if (std::fabs(out_pitch - current_real_pitch_) < deadzone) out_pitch = current_real_pitch_;

        // 发送消息给下位机
        vision_detector::msg::DroneDiff msg;
        msg.target_yaw = deg_to_rad(out_yaw);
        msg.target_pitch = deg_to_rad(out_pitch);
        msg.v_yaw = deg_to_rad(smoothed_v_yaw_);
        msg.v_pitch = deg_to_rad(smoothed_v_pitch_);
        msg.pc_timestamp_us = now_us_32;
        drone_diff_publisher_->publish(msg);

        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 100,
            "ToSTM: yaw=%.3f, pitch=%.3f", msg.target_yaw, msg.target_pitch);

        // ==========================================================
        // 【可视化仪表盘逻辑 - 必须放在这里，因为这里才能访问 target_yaw】
        // ==========================================================
        
        // 1. 绘制背景遮罩

        // 2. 绘制文字信息
        int base_y = 155;
        cv::Scalar white(255, 255, 255);
        
        // 当前云台状态
        cv::putText(display_frame, cv::format("Gimbal: Y:%.2f P:%.2f", matched_state.yaw, matched_state.pitch), 
                    cv::Point(20, base_y), cv::FONT_HERSHEY_SIMPLEX, 0.5, white, 1);
        
        // 目标绝对坐标
        cv::putText(display_frame, cv::format("Target: Y:%.2f P:%.2f", est_pos.x, est_pos.y), 
                    cv::Point(20, base_y + 25), cv::FONT_HERSHEY_SIMPLEX, 0.5, white, 1);

        // 发送给下位机的增量（偏差值）
        float off_yaw = out_yaw - matched_state.yaw;
        float off_pitch = out_pitch - matched_state.pitch;
        cv::putText(display_frame, cv::format("Offset: dY:%.2f dP:%.2f", off_yaw, off_pitch), 
                    cv::Point(20, base_y + 50), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1);

        // 目标速度
        cv::putText(display_frame, cv::format("V_Deg/s: dY:%.1f dP:%.1f", est_vel.x, est_vel.y), 
                    cv::Point(20, base_y + 75), cv::FONT_HERSHEY_SIMPLEX, 0.5, white, 1);

        // 3. 绘制前馈预测点（绿色）
        cv::Point2f future_angle_offset(
            (out_yaw + laser_offset_angle.x) - matched_state.yaw,
            (out_pitch + laser_offset_angle.y) - matched_state.pitch
        );
        cv::Point2f future_pix = getPixelFromAngle(future_angle_offset);
        cv::circle(display_frame, future_pix, 4, cv::Scalar(0, 255, 255), -1);
        cv::arrowedLine(display_frame, laser_center_point_, future_pix, cv::Scalar(255, 255, 255), 2);

    } else {
        // 【新增】目标丢失处理及超时回中功能
        auto time_since_lost = (this->now().nanoseconds() - last_target_time_.nanoseconds())/ 1000000.0; // 单位：毫秒
        
        vision_detector::msg::DroneDiff msg;
        msg.v_yaw = 0.0f; msg.v_pitch = 0.0f;
        msg.pc_timestamp_us = now_us_32;

        if (time_since_lost > LOST_RETURN_TIMEOUT) {
            // 丢失超过设定时间，云台回中
            msg.target_yaw = deg_to_rad(-11.2f); 
            msg.target_pitch = deg_to_rad(4.13f);
            cv::putText(display_frame, "STATUS: RETURN TO CENTER", cv::Point(20, 80), 0, 0.6, cv::Scalar(0, 0, 255), 2);
        } else {
            // 刚丢失，保持在最后停留的位置
            msg.target_yaw = deg_to_rad(current_real_yaw_);
            msg.target_pitch = deg_to_rad(current_real_pitch_);
            cv::putText(display_frame, "STATUS: SEARCHING", cv::Point(20, 80), 0, 0.6, cv::Scalar(0, 165, 255), 2);
        }
        drone_diff_publisher_->publish(msg);
    }

    // 绘制基准参考点
    cv::circle(display_frame, camera_center_point_, 4, cv::Scalar(255, 0, 0), -1); // 蓝点：光心
    cv::circle(display_frame, laser_center_point_, 4, cv::Scalar(0, 255, 0), -1);  // 绿点：激光
    
    cv::imshow("Vision Debugger", display_frame);
    static bool is_mouse_set = false;
    if (!is_mouse_set) {
        cv::setMouseCallback("Vision Debugger", mouseCallback, this);
        is_mouse_set = true;
    }
    cv::waitKey(1);
    rclcpp::Time end = this->now();
    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "timer_callback_ 处理时间: %ld ms", (end - start).nanoseconds() / 1000000);
}


// --------- 余下辅助代码保持不变 ---------

static void mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        ((VisionDroneDetector*)userdata)->laser_center_point_ = cv::Point(x, y);
    } 
}