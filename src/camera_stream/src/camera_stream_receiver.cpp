#include "rclcpp/rclcpp.hpp"
#include "config/config.h"
#include "camera_stream/msg/share_image.hpp"
#include <opencv2/opencv.hpp>
#include <sys/ipc.h>
#include <sys/shm.h>
class VisionDroneDetector : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    VisionDroneDetector(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
        command_subscribe_ = this->create_subscription<camera_stream::msg::ShareImage>("share_image",10,std::bind(&VisionDroneDetector::command_callback,this,std::placeholders::_1));
    }

private:
    // 声明节点
    rclcpp::Subscription<camera_stream::msg::ShareImage>::SharedPtr command_subscribe_;
    void command_callback(const camera_stream::msg::ShareImage::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(),"Rev: [id]%u [%u*%u] Ava:%u",msg->frame_id ,msg->width,msg->height,msg->enable);
        if(msg->enable==0) return;
        // int shm_id = shmget(IPC_PRIVATE, sizeof(unsigned char)*msg.width*msg.height*3, IPC_CREAT | 0666);
        // if(shm_id < 0){
        //     RCLCPP_ERROR(this->get_logger(), "Failed to create shared memory");
        //     return;
        // }
        void *shm_ptr = shmat(msg->shm_id, NULL, 0);
        if(shm_ptr == (void*)-1){
            RCLCPP_ERROR(this->get_logger(), "Failed to attach shared memory");
            return;
        }
        // 复制数据
        if(msg->camera_select == CAMERA_SELECT_DRONE | 1){
            cv::Mat frame(msg->height,msg->width,CV_8UC3);
            memcpy(frame.data, shm_ptr, msg->shm_size);
            if(msg->camera_select == CAMERA_SELECT_DRONE){
                cv::imshow("DRONE FRAME",frame);
            }else if(msg->camera_select == CAMERA_SELECT_CAR){
                cv::imshow("CAR FRAME",frame);
            }
        }
        shmdt(shm_ptr);
        cv::waitKey(1);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<VisionDroneDetector>("camera_stream_receiver");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}