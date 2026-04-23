#include <opencv2/opencv.hpp>
#include "config/config.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <memory>
std::vector<cv::Point2f> detectLaserSpot(const cv::Mat& frame);
std::vector<cv::Point2f> detectLaserModule(const cv::Mat& frame);



// 检查矩形是否大小和形状合理
bool isValidRect(const cv::Rect& rect) {
    int area = rect.width * rect.height;
    double wh_ratio = double(rect.width) / rect.height;
    return area > 100 && area < 2000 && wh_ratio > 0.5 && wh_ratio < 2.0;
}

// 返回每排最中心的y值，判定谁属于直线（±max_delta范围内）
std::vector<int> filterAligned(const std::vector<cv::Rect>& group, double max_delta = 10.0) {
    std::vector<int> centerYs;
    for (const auto& r : group) centerYs.push_back(r.y + r.height / 2);
    double meanY = std::accumulate(centerYs.begin(), centerYs.end(), 0.0) / centerYs.size();
    std::vector<int> alignedIdx;
    for (size_t i = 0; i < centerYs.size(); ++i) {
        if (std::abs(centerYs[i] - meanY) <= max_delta)
            alignedIdx.push_back(i);
    }
    return alignedIdx;
}

// 求两线交点
cv::Point2f intersectionPoint(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3, cv::Point2f p4) {
    float A1 = p2.y - p1.y;
    float B1 = p1.x - p2.x;
    float C1 = A1 * p1.x + B1 * p1.y;

    float A2 = p4.y - p3.y;
    float B2 = p3.x - p4.x;
    float C2 = A2 * p3.x + B2 * p3.y;

    float det = A1 * B2 - A2 * B1;
    if (std::abs(det) < 1e-5) // 平行
        return cv::Point2f(-1, -1);

    float x = (B2 * C1 - B1 * C2) / det;
    float y = (A1 * C2 - A2 * C1) / det;
    return cv::Point2f(x, y);
}

std::vector<cv::Point2f> detectLaserSpot(const cv::Mat& frame) {
    std::vector<cv::Point2f> candidates;
    
    cv::Mat hsvImage;
    cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);   // BGR → HSV

    std::vector<cv::Mat> hsvChannels;
    cv::split(hsvImage, hsvChannels);                      // 分离 H, S, V

    cv::Mat hChannel = hsvChannels[0];  // 色调通道 (Hue)
    cv::Mat sChannel = hsvChannels[1];  // 饱和度通道 (Saturation)
    cv::Mat vChannel = hsvChannels[2];  // 明度通道 (Value)
    cv::Scalar lower_green(40, 0, 150);
    cv::Scalar upper_green(75, 255, 255);
    cv::Mat green_mask;
    cv::inRange(hsvImage, lower_green, upper_green, green_mask);
    //cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_OPEN, kernel);

    //cv::erode(green_mask, green_mask, cv::Mat(), cv::Point(-1,-1), 2);
    //cv::dilate(green_mask, green_mask, cv::Mat(), cv::Point(-1,-1), 2);
    //cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    //cv::Mat processed;
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_CLOSE, kernel);

    // 可选：开运算去除残留的小噪点（先闭后开）
    //cv::morphologyEx(green_mask, green_mask, cv::MORPH_OPEN, kernel);
    // 查找轮廓（含层级）
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(green_mask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    double min_area = 50;
    double max_area = 999999;
    double circ_thresh = 0.8;//
    double concentric_thresh = 0.2; //

    for (size_t i = 0; i < contours.size(); i++) {
        if (hierarchy[i][2] == -1) continue; // 无子轮廓，跳过

        // 外部轮廓
        std::vector<cv::Point> outer = contours[i];
        double outer_area = cv::contourArea(outer);
        if (outer_area < min_area || outer_area > max_area) continue;

        // 凸包 + 圆度
        std::vector<cv::Point> hull;
        cv::convexHull(outer, hull);
        double hull_area = cv::contourArea(hull);
        double peri = cv::arcLength(hull, true);
        if (peri == 0) continue;
        double circ = 4 * CV_PI * hull_area / (peri * peri);
        if (circ < circ_thresh) continue;

        cv::Point2f outer_center;
        float outer_radius;
        cv::minEnclosingCircle(outer, outer_center, outer_radius);

        // 遍历子轮廓
        int child = hierarchy[i][2];
        while (child != -1) {
            std::vector<cv::Point> inner = contours[child];
            double inner_area = cv::contourArea(inner);
            if (inner_area > min_area/4) {
                // 计算内部轮廓圆度
                std::vector<cv::Point> inner_hull;
                cv::convexHull(inner, inner_hull);
                double inner_hull_area = cv::contourArea(inner_hull);
                double inner_peri = cv::arcLength(inner_hull, true);
                if (inner_peri > 0) {
                    double inner_circ = 4 * CV_PI * inner_hull_area / (inner_peri * inner_peri);
                    if (inner_circ > circ_thresh) {
                        cv::Point2f inner_center;
                        float inner_radius;
                        cv::minEnclosingCircle(inner, inner_center, inner_radius);
                        double dist = cv::norm(outer_center - inner_center);
                        if (dist / outer_radius < concentric_thresh) {
                            // 识别到圆环
                            candidates.push_back(outer_center);
                            break;
                        }
                    }
                }
            }
            child = hierarchy[child][0]; // 下一个兄弟
        }
    }
    return candidates;
}



std::vector<cv::Point2f> detectLaserModule(const cv::Mat& frame){
    std::vector<cv::Point2f> candidates;
    if (frame.empty()) {
        return candidates;
    }

    // ROI 状态缓存：依据上一帧检测中心和速度，预测下一帧搜索区域。
    static bool roi_track_valid = false;
    static cv::Point2f roi_track_center(0.0f, 0.0f);
    static cv::Point2f roi_track_vel(0.0f, 0.0f); // 像素/帧
    static int roi_lost_frames = 0;
    static int roi_frame_counter = 0;
    ++roi_frame_counter;

    // ===================== 可调参数区（建议现场调参） =====================
    // 调试开关：打开后会显示每个关键步骤的中间图像。
    const bool DEBUG_SHOW = true;
    const int DEBUG_UPDATE_INTERVAL = 3;            // 调试窗口每 N 帧更新一次

    // 是否启用“速度自适应 ROI 加速”。
    const bool ENABLE_DYNAMIC_ROI = true;
    const int ROI_LOST_KEEP_FRAMES = 8;             // 丢失后继续用预测 ROI 的最大帧数
    const int ROI_FORCE_FULL_FRAME_INTERVAL = 20;   // 每 N 帧全图重扫一次，防止 ROI 漂移
    const float ROI_BASE_HALF_SIZE = 160.0f;        // ROI 基础半边长（像素）
    const float ROI_SPEED_GAIN = 5.2f;              // 随速度扩张 ROI 的增益
    const float ROI_MIN_HALF_SIZE = 110.0f;
    const float ROI_MAX_HALF_SIZE_RATIO = 0.45f;    // ROI 最大占较短边比例
    const float ROI_PREDICT_LEAD = 1.0f;            // 预测超前（帧）
    const float ROI_VEL_DECAY_WHEN_LOST = 0.85f;    // 丢失时速度衰减
    const float ROI_VEL_SMOOTH_ALPHA = 0.35f;       // 新速度融合系数

    // ROI 内进一步降采样处理（仅影响检测计算，不影响最终显示尺寸）。
    const bool ENABLE_PROC_DOWNSAMPLE = true;
    const int PROC_DOWNSAMPLE_TRIGGER_SIDE = 260;   // ROI 较短边超过该值时开始降采样
    const int PROC_TARGET_MAX_SIDE = 300;           // ROI 较长边目标尺寸
    const float PROC_MIN_SCALE = 0.65f;             // 最小降采样比例，避免过度损失细节

    // 是否启用“蓝色通道差分辅助掩膜”（用于压制部分非目标蓝光反射）。
    // 默认关闭，仅使用 HSV；当背景蓝光干扰很重时可尝试打开。
    const bool USE_BLUE_DIFF_ASSIST = true;

    // 是否启用“白高光抑制”：用于去除背景反射高光造成的误检。
    const bool ENABLE_WHITE_GLARE_SUPPRESS = true;

    // HSV 阈值（OpenCV H 范围: 0~179）。
    // 该范围覆盖青蓝色高亮 LED，且要求较高的 S/V 以过滤暗背景噪声。
    const cv::Scalar HSV_LOWER_CYAN_BLUE(80, 80, 150);
    const cv::Scalar HSV_UPPER_CYAN_BLUE(135, 255, 255);

    // 成功瞄准后模块可能偏粉紫/紫色：单独加一段紫色范围，避免“卡蓝色太死”。
    const cv::Scalar HSV_LOWER_MAGENTA(135, 60, 150);
    const cv::Scalar HSV_UPPER_MAGENTA(179, 255, 255);

    // 白高光 HSV 阈值：低饱和 + 高亮，典型于反光白点。
    const cv::Scalar HSV_LOWER_WHITE_GLARE(0, 0, 230);
    const cv::Scalar HSV_UPPER_WHITE_GLARE(179, 70, 255);
    const int WHITE_GLARE_DILATE_ITERS = 1;          // 稍微膨胀，覆盖反光边缘
    const float WHITE_OVERLAP_MAX_RATIO = 0.35f;     // 轮廓与白高光重叠比例上限

    // 通道差分辅助（仅在 USE_BLUE_DIFF_ASSIST=true 时生效）。
    // 注意：不能只用 B-R，否则紫/粉紫会被直接掐掉。
    const int BLUE_DIFF_THRESH = 18;
    const int BRG_DIFF_THRESH = 18;                  // max(B,R)-G 阈值（兼容蓝/紫/粉紫）
    const float MIN_MEAN_SATURATION = 70.0f;         // 轮廓平均饱和度下限
    const float MIN_MEAN_MAXBR_MINUS_G = 18.0f;      // mean(max(B,R)-G) 下限，抑制白高光

    // 单灯块轮廓面积筛选（按图像分辨率自适应比例）。
    const double MIN_CONTOUR_AREA_RATIO = 0.000010;  // 1080p约12像素
    const double MAX_CONTOUR_AREA_RATIO = 0.0030;    // 1080p约6200像素

    // 聚类距离阈值（像素），使用较短边比例做自适应，适配 720p/1080p。
    const float CLUSTER_DIST_RATIO = 0.085f;

    // 组特征约束：至少包含若干灯块，整体包围框长宽比接近 1。
    const int MIN_LIGHTS_IN_GROUP = 4;
    const int MAX_LIGHTS_IN_GROUP = 24;
    const float GROUP_AR_MIN = 0.6f;
    const float GROUP_AR_MAX = 1.4f;

    // 灯块填充密度：用于过滤“非常稀疏”或“几乎实心”非目标区域。
    const float GROUP_DENSITY_MIN = 0.05f;
    const float GROUP_DENSITY_MAX = 0.75f;

    // 组内离群灯块过滤：抑制“突然并入的反光块”导致框体膨胀。
    const float BLOCK_AREA_MIN_SCALE = 0.20f;        // 相对中位面积下限
    const float BLOCK_AREA_MAX_SCALE = 4.50f;        // 相对中位面积上限
    const float GROUP_OUTLIER_DIST_SCALE = 1.20f;    // 相对聚类阈值的距离上限

    // 组内杂点抑制：进一步过滤孤立/离群灯块，避免框体突然变大。
    const float GROUP_NEIGHBOR_DIST_SCALE = 0.70f;   // 邻域判断距离阈值比例
    const int GROUP_MIN_NEIGHBORS = 1;               // 至少要有 1 个近邻，抑制孤立噪点
    const float GROUP_MAD_SCALE = 2.6f;              // MAD 离群阈值倍数
    const float GROUP_MAD_MIN_PIX = 7.0f;            // MAD 最小像素容差
    const float GROUP_MAX_MEAN_DIST_SCALE = 0.82f;   // 组平均半径上限比例
    const float GROUP_MAX_RADIUS_SCALE = 1.35f;      // 组最大半径上限比例
    const float GROUP_CORE_RADIUS_SCALE = 1.75f;     // 相对中位半径的核心筛选阈值
    const float GROUP_CORE_RADIUS_MIN_PIX = 9.0f;    // 核心筛选最小像素半径

    // 目标整体尺寸上限：防止 module_4 黄框突然闪动放大。
    const float GROUP_MAX_FRAME_AREA_RATIO = 0.10f;  // 目标占画面比例上限（10%）
    const float GROUP_MAX_FRAME_W_RATIO = 0.38f;
    const float GROUP_MAX_FRAME_H_RATIO = 0.38f;
    // =====================================================================

    const bool debug_update_this_frame =
        DEBUG_SHOW && (DEBUG_UPDATE_INTERVAL <= 1 || (roi_frame_counter % DEBUG_UPDATE_INTERVAL == 0));

    // 获取中位数（组尺寸较小，nth_element 开销可接受）。
    auto medianValue = [](std::vector<float> vals) -> float {
        if (vals.empty()) return 0.0f;
        auto mid_it = vals.begin() + static_cast<long>(vals.size() / 2);
        std::nth_element(vals.begin(), mid_it, vals.end());
        return *mid_it;
    };

    // 0) 依据历史速度预测 ROI，减少全图搜索开销。
    cv::Rect roi_rect(0, 0, frame.cols, frame.rows);
    bool use_roi = false;
    if (ENABLE_DYNAMIC_ROI && roi_track_valid && roi_lost_frames <= ROI_LOST_KEEP_FRAMES) {
        const bool do_full_refresh =
            (ROI_FORCE_FULL_FRAME_INTERVAL > 0) && (roi_frame_counter % ROI_FORCE_FULL_FRAME_INTERVAL == 0);
        if (!do_full_refresh) {
            const float speed = cv::norm(roi_track_vel);
            float roi_half = ROI_BASE_HALF_SIZE + ROI_SPEED_GAIN * speed;
            const float roi_half_max = ROI_MAX_HALF_SIZE_RATIO * static_cast<float>(std::min(frame.cols, frame.rows));
            roi_half = std::clamp(roi_half, ROI_MIN_HALF_SIZE, std::max(ROI_MIN_HALF_SIZE, roi_half_max));

            const cv::Point2f predicted_center = roi_track_center + roi_track_vel * ROI_PREDICT_LEAD;
            const int x1 = std::clamp(static_cast<int>(std::round(predicted_center.x - roi_half)), 0, frame.cols - 1);
            const int y1 = std::clamp(static_cast<int>(std::round(predicted_center.y - roi_half)), 0, frame.rows - 1);
            const int x2 = std::clamp(static_cast<int>(std::round(predicted_center.x + roi_half)), 1, frame.cols);
            const int y2 = std::clamp(static_cast<int>(std::round(predicted_center.y + roi_half)), 1, frame.rows);

            if (x2 - x1 >= 24 && y2 - y1 >= 24) {
                roi_rect = cv::Rect(x1, y1, x2 - x1, y2 - y1);
                use_roi = true;
            }
        }
    }

    const cv::Mat frame_roi = frame(roi_rect);

    float proc_scale = 1.0f;
    if (ENABLE_PROC_DOWNSAMPLE) {
        const int roi_long_side = std::max(roi_rect.width, roi_rect.height);
        const int roi_short_side = std::min(roi_rect.width, roi_rect.height);
        if (roi_short_side >= PROC_DOWNSAMPLE_TRIGGER_SIDE) {
            const float target_scale = static_cast<float>(PROC_TARGET_MAX_SIDE) /
                                       static_cast<float>(std::max(1, roi_long_side));
            proc_scale = std::clamp(target_scale, PROC_MIN_SCALE, 1.0f);
        }
    }

    cv::Mat frame_proc;
    if (proc_scale < 0.999f) {
        cv::resize(frame_roi, frame_proc, cv::Size(), proc_scale, proc_scale, cv::INTER_AREA);
    } else {
        frame_proc = frame_roi;
    }

    // 将 ROI 内中间图补回全尺寸，避免调试窗口随 ROI 跳动。
    auto restoreToRoiSize = [&](const cv::Mat& proc_img, int interp_method) {
        if (proc_scale >= 0.999f) {
            return proc_img;
        }
        cv::Mat roi_img;
        cv::resize(proc_img, roi_img, roi_rect.size(), 0, 0, interp_method);
        return roi_img;
    };

    auto expandToFull = [&](const cv::Mat& roi_img) {
        cv::Mat full_img(frame.size(), roi_img.type(), cv::Scalar::all(0));
        roi_img.copyTo(full_img(roi_rect));
        return full_img;
    };

    // 1) 预处理与颜色提取：BGR -> HSV，提取高亮青蓝色区域。
    cv::Mat hsv;
    cv::cvtColor(frame_proc, hsv, cv::COLOR_BGR2HSV);

    cv::Mat hsv_mask_cyanblue;
    cv::inRange(hsv, HSV_LOWER_CYAN_BLUE, HSV_UPPER_CYAN_BLUE, hsv_mask_cyanblue);
    cv::Mat hsv_mask_magenta;
    cv::inRange(hsv, HSV_LOWER_MAGENTA, HSV_UPPER_MAGENTA, hsv_mask_magenta);

    cv::Mat hsv_mask;
    cv::bitwise_or(hsv_mask_cyanblue, hsv_mask_magenta, hsv_mask);

    // 1.1) 白高光掩膜：先单独提取反光白点。
    cv::Mat white_glare_mask = cv::Mat::zeros(frame_proc.size(), CV_8UC1);
    if (ENABLE_WHITE_GLARE_SUPPRESS) {
        cv::inRange(hsv, HSV_LOWER_WHITE_GLARE, HSV_UPPER_WHITE_GLARE, white_glare_mask);
        if (WHITE_GLARE_DILATE_ITERS > 0) {
            cv::Mat k = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
            cv::dilate(white_glare_mask, white_glare_mask, k, cv::Point(-1, -1), WHITE_GLARE_DILATE_ITERS);
        }
    }

    // 可选：B-R 差分增强蓝色显著性，用于抑制部分“高亮但非蓝色”噪声。
    cv::Mat color_mask = hsv_mask.clone();
    if (USE_BLUE_DIFF_ASSIST) {
        std::vector<cv::Mat> bgr;
        cv::split(frame_proc, bgr); // B,G,R

        // 兼容蓝/紫/粉紫：
        // - (B-R) 强：典型蓝
        // - (R-B) 强：偏紫/粉紫
        // - max(B,R)-G 强：蓝/紫的共同特征（G 相对更低），同时对白色高光不敏感
        cv::Mat b_minus_r, r_minus_b, b_minus_g, r_minus_g;
        cv::subtract(bgr[0], bgr[2], b_minus_r);
        cv::subtract(bgr[2], bgr[0], r_minus_b);
        cv::subtract(bgr[0], bgr[1], b_minus_g);
        cv::subtract(bgr[2], bgr[1], r_minus_g);

        cv::Mat mask_br, mask_rb, mask_bg, mask_rg;
        cv::threshold(b_minus_r, mask_br, BLUE_DIFF_THRESH, 255, cv::THRESH_BINARY);
        cv::threshold(r_minus_b, mask_rb, BLUE_DIFF_THRESH, 255, cv::THRESH_BINARY);
        cv::threshold(b_minus_g, mask_bg, BRG_DIFF_THRESH, 255, cv::THRESH_BINARY);
        cv::threshold(r_minus_g, mask_rg, BRG_DIFF_THRESH, 255, cv::THRESH_BINARY);

        cv::Mat diff_mask;
        cv::bitwise_or(mask_br, mask_rb, diff_mask);
        cv::bitwise_or(diff_mask, mask_bg, diff_mask);
        cv::bitwise_or(diff_mask, mask_rg, diff_mask);

        cv::bitwise_and(hsv_mask, diff_mask, color_mask);
    }

    // 1.2) 从蓝色候选中减去白高光，抑制反光误检。
    if (ENABLE_WHITE_GLARE_SUPPRESS) {
        cv::Mat non_glare_mask;
        cv::bitwise_not(white_glare_mask, non_glare_mask);
        cv::bitwise_and(color_mask, non_glare_mask, color_mask);
    }

    // 2) 形态学处理：先闭运算补小孔，再轻微膨胀让破碎灯块连通。
    cv::Mat morph_mask;
    cv::Mat kernel_close = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat kernel_dilate = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(color_mask, morph_mask, cv::MORPH_CLOSE, kernel_close, cv::Point(-1, -1), 1);
    cv::dilate(morph_mask, morph_mask, kernel_dilate, cv::Point(-1, -1), 1);

    // 3) 轮廓提取。
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(morph_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 4) 轮廓初筛：面积过小/过大都过滤。
    const double frame_area = static_cast<double>(frame.rows) * static_cast<double>(frame.cols);
    const double proc_area_scale = static_cast<double>(proc_scale) * static_cast<double>(proc_scale);
    const double min_contour_area = std::max(4.0, frame_area * MIN_CONTOUR_AREA_RATIO * proc_area_scale);
    const double max_contour_area = std::max(
        min_contour_area * 2.0,
        frame_area * MAX_CONTOUR_AREA_RATIO * proc_area_scale
    );

    std::vector<cv::Rect> valid_rects;
    std::vector<cv::Point2f> valid_centers;
    valid_rects.reserve(contours.size());
    valid_centers.reserve(contours.size());

    for (const auto& contour : contours) {
        const double area = cv::contourArea(contour);
        if (area < min_contour_area || area > max_contour_area) {
            continue;
        }

        cv::Rect local_rect = cv::boundingRect(contour);
        if (local_rect.width <= 1 || local_rect.height <= 1) {
            continue;
        }

        // 单灯块可有一定透视形变，因此这里不过度限制宽高比。
        const float ar = static_cast<float>(local_rect.width) / static_cast<float>(local_rect.height);
        if (ar < 0.15f || ar > 6.0f) {
            continue;
        }

        // 用真实轮廓 mask 做颜色统计，避免仅凭 bbox 误判。
        std::vector<cv::Point> shifted_contour;
        shifted_contour.reserve(contour.size());
        for (const auto& p : contour) {
            shifted_contour.emplace_back(p.x - local_rect.x, p.y - local_rect.y);
        }

        cv::Mat contour_mask = cv::Mat::zeros(local_rect.height, local_rect.width, CV_8UC1);
        std::vector<std::vector<cv::Point>> contour_wrapper = {shifted_contour};
        cv::drawContours(contour_mask, contour_wrapper, 0, cv::Scalar(255), cv::FILLED);

        const int contour_pixels = std::max(1, cv::countNonZero(contour_mask));

        // 过滤“白高光重叠过多”的轮廓。
        if (ENABLE_WHITE_GLARE_SUPPRESS) {
            cv::Mat overlap_mask;
            cv::bitwise_and(white_glare_mask(local_rect), contour_mask, overlap_mask);
            const float white_overlap_ratio =
                static_cast<float>(cv::countNonZero(overlap_mask)) / static_cast<float>(contour_pixels);
            if (white_overlap_ratio > WHITE_OVERLAP_MAX_RATIO) {
                continue;
            }
        }

        // 轮廓颜色纯度：高光白点通常蓝红差小、饱和度低。
        const cv::Scalar mean_bgr = cv::mean(frame_proc(local_rect), contour_mask);
        const cv::Scalar mean_hsv = cv::mean(hsv(local_rect), contour_mask);
        const float mean_sat = static_cast<float>(mean_hsv[1]);

        const float mean_b = static_cast<float>(mean_bgr[0]);
        const float mean_g = static_cast<float>(mean_bgr[1]);
        const float mean_r = static_cast<float>(mean_bgr[2]);
        const float mean_maxbr_minus_g = std::max(mean_b, mean_r) - mean_g;

        // 白高光通常 sat 低、且 max(B,R) 与 G 差不大；蓝/紫灯通常 sat 高、且 G 相对更低。
        if (mean_sat < MIN_MEAN_SATURATION || mean_maxbr_minus_g < MIN_MEAN_MAXBR_MINUS_G) {
            continue;
        }

        const float inv_scale = 1.0f / std::max(1e-6f, proc_scale);
        cv::Rect rect(
            roi_rect.x + static_cast<int>(std::round(local_rect.x * inv_scale)),
            roi_rect.y + static_cast<int>(std::round(local_rect.y * inv_scale)),
            std::max(1, static_cast<int>(std::round(local_rect.width * inv_scale))),
            std::max(1, static_cast<int>(std::round(local_rect.height * inv_scale)))
        );
        rect &= cv::Rect(0, 0, frame.cols, frame.rows);
        if (rect.width <= 1 || rect.height <= 1) {
            continue;
        }

        valid_rects.push_back(rect);
        valid_centers.emplace_back(
            rect.x + rect.width * 0.5f,
            rect.y + rect.height * 0.5f
        );
    }

    if (valid_centers.empty()) {
        if (roi_track_valid) {
            roi_track_center += roi_track_vel;
            roi_track_vel *= ROI_VEL_DECAY_WHEN_LOST;
            ++roi_lost_frames;
            if (roi_lost_frames > ROI_LOST_KEEP_FRAMES) {
                roi_track_valid = false;
                roi_track_vel = cv::Point2f(0.0f, 0.0f);
            }
        }

        if (debug_update_this_frame) {
            cv::Mat debug_group_frame = frame.clone();
            const cv::Scalar roi_color = use_roi ? cv::Scalar(0, 170, 255) : cv::Scalar(80, 80, 80);
            cv::rectangle(debug_group_frame, roi_rect, roi_color, 2);
            cv::putText(
                debug_group_frame,
                use_roi
                    ? cv::format("ROI SEARCH (%dx%d) x%.2f", roi_rect.width, roi_rect.height, proc_scale)
                    : cv::format("FULL SEARCH x%.2f", proc_scale),
                cv::Point(roi_rect.x + 6, std::max(18, roi_rect.y + 18)),
                cv::FONT_HERSHEY_SIMPLEX,
                0.52,
                roi_color,
                1
            );

            cv::imshow("debug_module_1_hsv_mask", expandToFull(restoreToRoiSize(hsv_mask, cv::INTER_NEAREST)));
            cv::imshow("debug_module_1b_white_glare", expandToFull(restoreToRoiSize(white_glare_mask, cv::INTER_NEAREST)));
            cv::imshow("debug_module_1c_color_mask", expandToFull(restoreToRoiSize(color_mask, cv::INTER_NEAREST)));
            cv::imshow("debug_module_2_morph_mask", expandToFull(restoreToRoiSize(morph_mask, cv::INTER_NEAREST)));
            cv::imshow("debug_module_4_group_result", debug_group_frame);
            cv::waitKey(1);
        }
        return candidates;
    }

    // 5) 聚类/编组（核心）：用“中心点距离阈值”构图，连通域视为同一模块组。
    const float cluster_dist_thresh = CLUSTER_DIST_RATIO * static_cast<float>(std::min(frame.cols, frame.rows));
    const size_t n = valid_centers.size();

    std::vector<std::vector<int>> adjacency(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            const float dist = cv::norm(valid_centers[i] - valid_centers[j]);
            if (dist <= cluster_dist_thresh) {
                adjacency[i].push_back(static_cast<int>(j));
                adjacency[j].push_back(static_cast<int>(i));
            }
        }
    }

    std::vector<int> labels(n, -1);
    int group_id = 0;
    std::vector<std::vector<int>> groups;

    for (size_t i = 0; i < n; ++i) {
        if (labels[i] != -1) {
            continue;
        }

        std::vector<int> stack;
        stack.push_back(static_cast<int>(i));
        labels[i] = group_id;

        std::vector<int> group_indices;
        while (!stack.empty()) {
            const int u = stack.back();
            stack.pop_back();
            group_indices.push_back(u);

            for (const int v : adjacency[u]) {
                if (labels[v] == -1) {
                    labels[v] = group_id;
                    stack.push_back(v);
                }
            }
        }

        groups.push_back(group_indices);
        ++group_id;
    }

    // 6) 组合特征校验：组内灯块数、整体包围框长宽比、密度。
    cv::Mat debug_group_frame;
    if (debug_update_this_frame) {
        debug_group_frame = frame.clone();
        const cv::Scalar roi_color = use_roi ? cv::Scalar(0, 170, 255) : cv::Scalar(80, 80, 80);
        cv::rectangle(debug_group_frame, roi_rect, roi_color, 2);
        cv::putText(
            debug_group_frame,
            use_roi
                ? cv::format("ROI SEARCH (%dx%d) x%.2f", roi_rect.width, roi_rect.height, proc_scale)
                : cv::format("FULL SEARCH x%.2f", proc_scale),
            cv::Point(roi_rect.x + 6, std::max(18, roi_rect.y + 18)),
            cv::FONT_HERSHEY_SIMPLEX,
            0.52,
            roi_color,
            1
        );
    }

    for (const auto& group : groups) {
        std::vector<int> refined_group = group;

        // 6.1) 按灯块面积中位数去掉极端离群块，防止单个大反光块并入。
        if (refined_group.size() >= 3) {
            std::vector<float> area_samples;
            area_samples.reserve(refined_group.size());
            for (const int idx : refined_group) {
                area_samples.push_back(static_cast<float>(valid_rects[idx].area()));
            }

            std::nth_element(
                area_samples.begin(),
                area_samples.begin() + area_samples.size() / 2,
                area_samples.end()
            );
            const float median_area = std::max(1.0f, area_samples[area_samples.size() / 2]);

            std::vector<int> area_filtered;
            area_filtered.reserve(refined_group.size());
            for (const int idx : refined_group) {
                const float a = static_cast<float>(valid_rects[idx].area());
                if (a >= median_area * BLOCK_AREA_MIN_SCALE && a <= median_area * BLOCK_AREA_MAX_SCALE) {
                    area_filtered.push_back(idx);
                }
            }

            if (static_cast<int>(area_filtered.size()) >= MIN_LIGHTS_IN_GROUP) {
                refined_group.swap(area_filtered);
            }
        }

        // 6.2) 组中心距离离群点剔除，抑制远处反光点把框拉大。
        cv::Point2f center(0.0f, 0.0f);
        for (const int idx : refined_group) {
            center += valid_centers[idx];
        }
        center *= 1.0f / std::max(1, static_cast<int>(refined_group.size()));

        const float group_outlier_dist_thresh = std::max(12.0f, GROUP_OUTLIER_DIST_SCALE * cluster_dist_thresh);
        std::vector<int> dist_filtered;
        dist_filtered.reserve(refined_group.size());
        for (const int idx : refined_group) {
            if (cv::norm(valid_centers[idx] - center) <= group_outlier_dist_thresh) {
                dist_filtered.push_back(idx);
            }
        }

        if (static_cast<int>(dist_filtered.size()) >= MIN_LIGHTS_IN_GROUP) {
            refined_group.swap(dist_filtered);
        }

        // 6.3) 邻域密度过滤：剔除“只有自己、没有近邻”的杂点。
        if (refined_group.size() >= static_cast<size_t>(MIN_LIGHTS_IN_GROUP)) {
            const float neighbor_dist_thresh = std::max(8.0f, GROUP_NEIGHBOR_DIST_SCALE * cluster_dist_thresh);
            std::vector<int> dense_filtered;
            dense_filtered.reserve(refined_group.size());

            for (const int idx : refined_group) {
                int near_cnt = 0;
                for (const int jdx : refined_group) {
                    if (idx == jdx) continue;
                    if (cv::norm(valid_centers[idx] - valid_centers[jdx]) <= neighbor_dist_thresh) {
                        ++near_cnt;
                    }
                }
                if (near_cnt >= GROUP_MIN_NEIGHBORS) {
                    dense_filtered.push_back(idx);
                }
            }

            if (static_cast<int>(dense_filtered.size()) >= MIN_LIGHTS_IN_GROUP) {
                refined_group.swap(dense_filtered);
            }
        }

        // 6.4) 基于中位数 + MAD 的离群过滤，抑制少量远离主簇的杂点。
        if (refined_group.size() >= static_cast<size_t>(MIN_LIGHTS_IN_GROUP)) {
            std::vector<float> xs;
            std::vector<float> ys;
            xs.reserve(refined_group.size());
            ys.reserve(refined_group.size());
            for (const int idx : refined_group) {
                xs.push_back(valid_centers[idx].x);
                ys.push_back(valid_centers[idx].y);
            }

            const float med_x = medianValue(xs);
            const float med_y = medianValue(ys);

            std::vector<float> abs_dx;
            std::vector<float> abs_dy;
            abs_dx.reserve(refined_group.size());
            abs_dy.reserve(refined_group.size());
            for (const int idx : refined_group) {
                abs_dx.push_back(std::fabs(valid_centers[idx].x - med_x));
                abs_dy.push_back(std::fabs(valid_centers[idx].y - med_y));
            }

            const float mad_x = std::max(GROUP_MAD_MIN_PIX, 1.4826f * medianValue(abs_dx));
            const float mad_y = std::max(GROUP_MAD_MIN_PIX, 1.4826f * medianValue(abs_dy));

            std::vector<int> mad_filtered;
            mad_filtered.reserve(refined_group.size());
            for (const int idx : refined_group) {
                const float dx = std::fabs(valid_centers[idx].x - med_x);
                const float dy = std::fabs(valid_centers[idx].y - med_y);
                if (dx <= GROUP_MAD_SCALE * mad_x && dy <= GROUP_MAD_SCALE * mad_y) {
                    mad_filtered.push_back(idx);
                }
            }

            if (static_cast<int>(mad_filtered.size()) >= MIN_LIGHTS_IN_GROUP) {
                refined_group.swap(mad_filtered);
            }
        }

        int light_count = static_cast<int>(refined_group.size());
        if (light_count < MIN_LIGHTS_IN_GROUP || light_count > MAX_LIGHTS_IN_GROUP) {
            continue;
        }

        // 用中位中心作为初始鲁棒中心。
        std::vector<float> robust_xs;
        std::vector<float> robust_ys;
        robust_xs.reserve(refined_group.size());
        robust_ys.reserve(refined_group.size());
        for (const int idx : refined_group) {
            robust_xs.push_back(valid_centers[idx].x);
            robust_ys.push_back(valid_centers[idx].y);
        }
        const cv::Point2f robust_center(medianValue(robust_xs), medianValue(robust_ys));

        // 6.5) 核心点筛选：按相对中位半径去掉残余远离点，防止框体被拉大。
        std::vector<float> radial_samples;
        radial_samples.reserve(refined_group.size());
        for (const int idx : refined_group) {
            radial_samples.push_back(cv::norm(valid_centers[idx] - robust_center));
        }

        const float median_radius = std::max(1.0f, medianValue(radial_samples));
        const float core_radius_thresh = std::max(GROUP_CORE_RADIUS_MIN_PIX, GROUP_CORE_RADIUS_SCALE * median_radius);
        std::vector<int> core_group;
        core_group.reserve(refined_group.size());
        for (const int idx : refined_group) {
            if (cv::norm(valid_centers[idx] - robust_center) <= core_radius_thresh) {
                core_group.push_back(idx);
            }
        }
        if (static_cast<int>(core_group.size()) >= MIN_LIGHTS_IN_GROUP) {
            refined_group.swap(core_group);
        }

        light_count = static_cast<int>(refined_group.size());
        if (light_count < MIN_LIGHTS_IN_GROUP || light_count > MAX_LIGHTS_IN_GROUP) {
            continue;
        }

        // 核心筛选后再计算鲁棒中心和紧凑度。
        robust_xs.clear();
        robust_ys.clear();
        robust_xs.reserve(refined_group.size());
        robust_ys.reserve(refined_group.size());
        for (const int idx : refined_group) {
            robust_xs.push_back(valid_centers[idx].x);
            robust_ys.push_back(valid_centers[idx].y);
        }
        const cv::Point2f core_center(medianValue(robust_xs), medianValue(robust_ys));

        // 6.6) 紧凑度校验：过滤掉被少量杂点拉长的松散组。
        double mean_dist = 0.0;
        float max_dist = 0.0f;
        for (const int idx : refined_group) {
            const float d = cv::norm(valid_centers[idx] - core_center);
            mean_dist += d;
            if (d > max_dist) max_dist = d;
        }
        mean_dist /= std::max(1, light_count);

        const float mean_dist_max = GROUP_MAX_MEAN_DIST_SCALE * cluster_dist_thresh;
        const float radius_max = GROUP_MAX_RADIUS_SCALE * cluster_dist_thresh;
        if (mean_dist > mean_dist_max || max_dist > radius_max) {
            continue;
        }

        cv::Rect group_rect = valid_rects[refined_group[0]];
        double sum_rect_area = 0.0;
        for (const int idx : refined_group) {
            group_rect |= valid_rects[idx];
            sum_rect_area += static_cast<double>(valid_rects[idx].area());
        }

        if (group_rect.width <= 0 || group_rect.height <= 0) {
            continue;
        }

        const float group_ar = static_cast<float>(group_rect.width) / static_cast<float>(group_rect.height);
        if (group_ar < GROUP_AR_MIN || group_ar > GROUP_AR_MAX) {
            continue;
        }

        const double group_area = static_cast<double>(group_rect.area());
        const float density = static_cast<float>(sum_rect_area / std::max(1.0, group_area));
        if (density < GROUP_DENSITY_MIN || density > GROUP_DENSITY_MAX) {
            continue;
        }

        // 6.7) 组尺寸上限，直接抑制“module_4黄框瞬间放大”。
        const float group_area_ratio = static_cast<float>(group_area / std::max(1.0, frame_area));
        if (group_area_ratio > GROUP_MAX_FRAME_AREA_RATIO) {
            continue;
        }
        if (group_rect.width > frame.cols * GROUP_MAX_FRAME_W_RATIO ||
            group_rect.height > frame.rows * GROUP_MAX_FRAME_H_RATIO) {
            continue;
        }

        // 7) 计算中心点并输出。
        // 接口为 vector<Point2f>，因此最终存储的是点值本身。
        auto center_ptr = std::make_shared<cv::Point2f>(
            group_rect.x + group_rect.width * 0.5f,
            group_rect.y + group_rect.height * 0.5f
        );
        candidates.push_back(*center_ptr);

        if (debug_update_this_frame) {
            cv::rectangle(debug_group_frame, group_rect, cv::Scalar(0, 255, 255), 2);
            cv::circle(debug_group_frame, *center_ptr, 4, cv::Scalar(0, 0, 255), -1);
            cv::putText(
                debug_group_frame,
                cv::format("N:%d AR:%.2f D:%.2f A:%.3f", light_count, group_ar, density, group_area_ratio),
                cv::Point(group_rect.x, std::max(0, group_rect.y - 8)),
                cv::FONT_HERSHEY_SIMPLEX,
                0.45,
                cv::Scalar(0, 255, 255),
                1
            );
        }
    }

    // 7.1) 用检测结果更新 ROI 中心与速度。
    if (!candidates.empty()) {
        cv::Point2f selected_center = candidates[0];
        if (roi_track_valid) {
            cv::Point2f predicted = roi_track_center + roi_track_vel * ROI_PREDICT_LEAD;
            float best_dist = cv::norm(selected_center - predicted);
            for (const auto& c : candidates) {
                const float d = cv::norm(c - predicted);
                if (d < best_dist) {
                    best_dist = d;
                    selected_center = c;
                }
            }

            const cv::Point2f measured_vel = selected_center - roi_track_center;
            roi_track_vel = (1.0f - ROI_VEL_SMOOTH_ALPHA) * roi_track_vel + ROI_VEL_SMOOTH_ALPHA * measured_vel;
        } else {
            roi_track_vel = cv::Point2f(0.0f, 0.0f);
        }

        roi_track_center = selected_center;
        roi_track_valid = true;
        roi_lost_frames = 0;
    } else {
        if (roi_track_valid) {
            roi_track_center += roi_track_vel;
            roi_track_vel *= ROI_VEL_DECAY_WHEN_LOST;
            ++roi_lost_frames;
            if (roi_lost_frames > ROI_LOST_KEEP_FRAMES) {
                roi_track_valid = false;
                roi_track_vel = cv::Point2f(0.0f, 0.0f);
            }
        }
    }

    // 8) 可选调试窗口：按步骤展示中间结果。
    if (debug_update_this_frame) {
        cv::Mat debug_contours = frame.clone();
        for (const auto& rect : valid_rects) {
            cv::rectangle(debug_contours, rect, cv::Scalar(255, 0, 255), 1);
        }

        const cv::Scalar roi_color = use_roi ? cv::Scalar(0, 170, 255) : cv::Scalar(80, 80, 80);
        cv::rectangle(debug_contours, roi_rect, roi_color, 2);
        cv::putText(
            debug_contours,
            use_roi
                ? cv::format("ROI SEARCH (%dx%d) x%.2f", roi_rect.width, roi_rect.height, proc_scale)
                : cv::format("FULL SEARCH x%.2f", proc_scale),
            cv::Point(roi_rect.x + 6, std::max(18, roi_rect.y + 18)),
            cv::FONT_HERSHEY_SIMPLEX,
            0.52,
            roi_color,
            1
        );

        cv::imshow("debug_module_1_hsv_mask", expandToFull(restoreToRoiSize(hsv_mask, cv::INTER_NEAREST)));
        cv::imshow("debug_module_1b_white_glare", expandToFull(restoreToRoiSize(white_glare_mask, cv::INTER_NEAREST)));
        cv::imshow("debug_module_1c_color_mask", expandToFull(restoreToRoiSize(color_mask, cv::INTER_NEAREST)));
        cv::imshow("debug_module_2_morph_mask", expandToFull(restoreToRoiSize(morph_mask, cv::INTER_NEAREST)));
        cv::imshow("debug_module_3_valid_contours", debug_contours);
        cv::imshow("debug_module_4_group_result", debug_group_frame.empty() ? frame : debug_group_frame);
        cv::waitKey(1);
    }

    return candidates;
}