#include "rclcpp/rclcpp.hpp"
#include "camera_stream/msg/share_image.hpp"
#include "config/config.h"
#include "ui.h"
#include "calibration.h"
#include <opencv2/opencv.hpp>
#include <sys/ipc.h>
#include <sys/shm.h>

class PnpCalibration : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    PnpCalibration(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
        while(1){
            map=cv::imread(MAP_PATH);
            if(map.empty())
                RCLCPP_ERROR(this->get_logger(), "地图打开失败");
            else
                break;
        }
        RCLCPP_INFO(this->get_logger(), "地图打开成功");
        cv::resize(map,map,cv::Size(map.cols * MAP_SCALE_FACTOR, map.rows * MAP_SCALE_FACTOR));
        cv::rotate(map, map, cv::ROTATE_90_COUNTERCLOCKWISE);
        ui.map_image = map.clone();
        command_subscribe_ = this->create_subscription<camera_stream::msg::ShareImage>("share_image",10,std::bind(&PnpCalibration::command_callback,this,std::placeholders::_1));
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&PnpCalibration::main_loop, this));
    }

private:
    // 声明节点
    cv::Mat map;
    cv::Mat cameraframe;
    rclcpp::TimerBase::SharedPtr timer_;
    UI ui;
    void main_loop(void);
    rclcpp::Subscription<camera_stream::msg::ShareImage>::SharedPtr command_subscribe_;
    void command_callback(const camera_stream::msg::ShareImage::SharedPtr msg){
        //RCLCPP_INFO(this->get_logger(),"Rev: [id]%u [%u*%u] Ava:%u",msg->frame_id ,msg->width,msg->height,msg->enable);
        if(msg->enable==0 || msg->camera_select != CAMERA_SELECT_CAR) return;
        void *shm_ptr = shmat(msg->shm_id, NULL, 0);
        if(shm_ptr == (void*)-1){
            RCLCPP_ERROR(this->get_logger(), "Failed to attach shared memory");
            return;
        }
        cv::Mat frame(msg->height,msg->width,CV_8UC3);
        memcpy(frame.data, shm_ptr, msg->shm_size);
        cameraframe=frame.clone();
        shmdt(shm_ptr);
    }
};

int main(int argc, char **argv){

    rclcpp::init(argc,argv);
    auto node = std::make_shared<PnpCalibration>("node_pnp_calibration");
    RCLCPP_INFO(node->get_logger(),"STARTED.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

void PnpCalibration::main_loop(void){
    if(cameraframe.empty()) return;

    // 检查ESC键是否按下
    char key = cv::waitKey(1);
    if (key == 27)
    {  // ESC键的ASCII码
      return;
    }
    else if (key == 13)
    {  //回车键
      if (ui.calibration.pts.camera_id == 12 && ui.calibration.pts.map_id == 12)
      {
        std::cout << "已选择12个点，开始标定..." << std::endl;
        //标定操作
        ui.calibration.getTransformationMatrix();
        cv::Mat dst_image;
        cv::Mat cam_image;
        cv::resize(ui.camera_image,
                   cam_image,
                   cv::Size(ui.camera_image.cols / CAR_CAMERA_SCALE_FACTOR,
                            ui.camera_image.rows / CAR_CAMERA_SCALE_FACTOR));

        warpPerspective(
          cam_image,
          dst_image,
          ui.calibration.L,
          cv::Size(map.cols / MAP_SCALE_FACTOR, map.rows / MAP_SCALE_FACTOR));
        cv::resize(dst_image, dst_image, cv::Size(map.cols, map.rows));
        cv::imshow("DstL", dst_image);

        warpPerspective(
          cam_image,
          dst_image,
          ui.calibration.M,
          cv::Size(map.cols / MAP_SCALE_FACTOR, map.rows / MAP_SCALE_FACTOR));
        cv::resize(dst_image, dst_image, cv::Size(map.cols, map.rows));
        cv::imshow("DstM", dst_image);

        warpPerspective(
          cam_image,
          dst_image,
          ui.calibration.H,
          cv::Size(map.cols / MAP_SCALE_FACTOR, map.rows / MAP_SCALE_FACTOR));
        cv::resize(dst_image, dst_image, cv::Size(map.cols, map.rows));
        cv::imshow("DstH", dst_image);

        
      }
      else
      {
        cv::Mat dst_image;
        cv::Mat cam_image;
        cv::resize(ui.camera_image,
                   cam_image,
                   cv::Size(ui.camera_image.cols / CAR_CAMERA_SCALE_FACTOR,
                            ui.camera_image.rows / CAR_CAMERA_SCALE_FACTOR));
        switch (CAMERA_CAR_MODE)
        {
          case MODE_TEST:
            ui.calibration.loadMatrices(
              "calibration_matrices_test.yaml");
            break;

          case MODE_VIDEO:
            ui.calibration.loadMatrices(
              "calibration_matrices_video.yaml");
            break;

          case MODE_HIK:
            ui.calibration.loadMatrices(
              "calibration_matrices_hik.yaml");
            break;
          case MODE_CAMERA:
            ui.calibration.loadMatrices(
              "calibration_matrices_camera.yaml");
            break;
          default:
            break;
        }
        warpPerspective(
          cam_image,
          dst_image,
          ui.calibration.H,
          cv::Size(map.cols / MAP_SCALE_FACTOR, map.rows / MAP_SCALE_FACTOR));
        cv::resize(dst_image, dst_image, cv::Size(map.cols, map.rows));
        cv::imshow("HH", dst_image);
      }
    }
    cv::resize(cameraframe,
                 ui.camera_image,
                 cv::Size(cameraframe.cols * CAR_CAMERA_SCALE_FACTOR,
                          cameraframe.rows * CAR_CAMERA_SCALE_FACTOR));
    ui.show_image();
}