#include "rclcpp/rclcpp.hpp"
#include "config/config.h"
#include "camera_stream/msg/share_image.hpp"
#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "HKCamera.h"
//cv::Mat getFrame(void);
bool hk_init_locking=false;
class CameraStreamPublisher : public rclcpp::Node
{
public:
	CameraStreamPublisher(std::string name, int camera_select, enum camera_mode mode) : Node(name), camera_select_(camera_select), camera_mode_(mode)
	{
		RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
		command_publisher_ = this->create_publisher<camera_stream::msg::ShareImage>("share_image",10);
		timer_ = this->create_wall_timer(std::chrono::milliseconds(1),std::bind(&CameraStreamPublisher::timer_callback,this));
		cv::Mat testFrame_;

		if (camera_select_ == CAMERA_SELECT_CAR) {
			shm_key_ = CAMERA_CAR_SHMID;
		} else if (camera_select_ == CAMERA_SELECT_DRONE) {
			shm_key_ = CAMERA_DRONE_SHMID;
		} else {
			RCLCPP_ERROR(this->get_logger(), "无效的 camera_select");
			rclcpp::shutdown();
			return;
		}
	}
	
private:
	bool camera_init_success_=false;
	// 声明节点
	int shm_key_=0;
	void timer_callback(void);
	void initCamera(void);
	void createSharedMemory();
	int init_HKCamera(HKCamera* camera, const std::string& targetSerial, struct HIKCameraParams params);
	cv::VideoCapture cap_;
	cv::VideoCapture video_cap_; // 新增：视频模式播放器
	cv::Mat getFrame(rclcpp::Time *now);
	cv::Mat testFrame_;
	int camera_mode_;
	int camera_select_;
	rclcpp::Publisher<camera_stream::msg::ShareImage>::SharedPtr command_publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	unsigned int frame_id_=0;
	unsigned int width_,height_;
	int shm_id_;
	int empty_count_=0;
	HKCamera hkcamera_;
};
cv::Mat CameraStreamPublisher::getFrame(rclcpp::Time *now){
	if(!camera_init_success_){
		initCamera();
		camera_init_success_ = true;
	}
	cv::Mat frame;
	switch (camera_mode_)
	{
		case MODE_TEST:
			if(camera_select_ == CAMERA_SELECT_CAR){
				frame=cv::imread(IMAGE_CAR_PATH);
			}else if(camera_select_ == CAMERA_SELECT_DRONE){
				frame=cv::imread(IMAGE_DRONE_PATH);
			}
			*now = get_clock()->now(); //ns
			return frame;
			break;
		case MODE_CAMERA:
			cap_ >> frame;
			*now = get_clock()->now(); //ns
			return frame;
			break;
		case MODE_HIK:
			frame=hkcamera_.GetOneFrame();
			*now = get_clock()->now(); //ns
			cv::rotate(frame, frame, cv::ROTATE_180);
			
			return frame;
			break;
		case MODE_VIDEO:
			video_cap_ >> frame;
			if (frame.empty()) {
				// 到末尾后循环播放
				video_cap_.set(cv::CAP_PROP_POS_FRAMES, 0);
				video_cap_ >> frame;
			}
			*now = get_clock()->now(); //ns
			return frame;
			break;
		default:
			RCLCPP_WARN(this->get_logger(), "ERROR: Empty Frame");
			frame.release();
			return frame;
			break;
	}
}

void CameraStreamPublisher::timer_callback(void){
	camera_stream::msg::ShareImage message;
	rclcpp::Time now;
	cv::Mat frame = getFrame(&now);
	if(frame.empty()){
		RCLCPP_WARN(this->get_logger(),"Frame Empty!");
		empty_count_ ++;
		if(empty_count_ > 3){
			RCLCPP_ERROR(this->get_logger(),"连续10帧图像为空，检查相机连接!");
			camera_init_success_ = false;
			empty_count_ = 0;
			return;
		}
		message.enable=0;

	}else{
		empty_count_=0;
		message.enable=1;
		message.camera_select = this->camera_select_;
		message.width=frame.cols;
		message.height=frame.rows;
		message.frame_id=frame_id_;
		message.timestamp_us = (uint64_t)(now.nanoseconds() / 1000);
		frame_id_++;
	}

	void *shm_ptr = shmat(shm_id_, NULL, 0);
	if(shm_ptr == (void*)-1){
		RCLCPP_ERROR(this->get_logger(), "Failed to attach shared memory [%d]",shm_id_);
		message.enable=0;
		return;
	}
	message.shm_id = shm_id_;
	message.shm_size = sizeof(unsigned char)*message.width*message.height*3;
	// 复制数据到共享内存
	memcpy(shm_ptr, frame.data, sizeof(unsigned char)*message.width*message.height*3);
	RCLCPP_INFO(this->get_logger(),"Publishing message size:%lu %lu %lu EN: %d",sizeof(cv::Mat),sizeof(cv::Mat::data),sizeof(unsigned char)*message.width*message.height*3, message.enable);
	command_publisher_->publish(message);
	shmdt(shm_ptr);
}

int CameraStreamPublisher::init_HKCamera(HKCamera* camera, const std::string& targetSerial, struct HIKCameraParams params)
{
	if(hk_init_locking){
		RCLCPP_WARN(this->get_logger(), "HKCamera正在初始化中，等待完成...");
		while(hk_init_locking && rclcpp::ok()){
			rclcpp::sleep_for(std::chrono::milliseconds(100));
		}
	}
	hk_init_locking = true;
	
  // 初始化相机
  if (!camera->InitCamera(targetSerial))
  {
	RCLCPP_ERROR(this->get_logger(), "HKCamera初始化失败");
	hk_init_locking = false;
	return -1;
  }
  RCLCPP_INFO(this->get_logger(), "HKCamera初始化成功");
  // 设置参数
  camera->params.exposureTime = params.exposureTime;
  camera->params.gain = params.gain;
  camera->params.frameRate = params.frameRate;

  if (!camera->SetParameters())
  {
	RCLCPP_ERROR(this->get_logger(), "设置HK相机参数失败!");
	hk_init_locking = false;
	return -1;
  }
  RCLCPP_INFO(this->get_logger(), "设置HK相机参数成功!");
  // 开始取图
  if (!camera->StartGrabbing())
  {
	RCLCPP_ERROR(this->get_logger(), "开始HK取图失败!");
	hk_init_locking = false;
	return -1;
  }
  RCLCPP_INFO(this->get_logger(), "开始HK取图成功!");
  // 持续获取并显示图像
  hk_init_locking = false;
  return 0;
}

void CameraStreamPublisher::initCamera(void){
	//createSharedMemory();
	if(camera_mode_==MODE_CAMERA){
		while(rclcpp::ok()){
			cap_=cv::VideoCapture(CAMERA_USB_ID,cv::CAP_V4L2);
			if(!cap_.isOpened()){
				RCLCPP_ERROR(this->get_logger(), "Cannot open USB camera");
				rclcpp::sleep_for(std::chrono::milliseconds(500));
			}else{
				cap_.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
				cap_.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
				cap_.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
				cap_ >> testFrame_;
				break;
			}
		}
		RCLCPP_INFO(this->get_logger(), "初始化USB相机成功");
	}else if(camera_mode_==MODE_HIK){
		while(rclcpp::ok()){
			int success;
			if(camera_select_ == CAMERA_SELECT_CAR){
				success = init_HKCamera(&hkcamera_, CAMERA_CAR_DEVID, (struct HIKCameraParams){CAR_CAMERA_HIK_EXPOSURE_TIME, CAR_CAMERA_HIK_GAIN, CAR_CAMERA_HIK_FRAME_RATE});
			}else if(camera_select_ == CAMERA_SELECT_DRONE){
				success = init_HKCamera(&hkcamera_, CAMERA_DRONE_DEVID, (struct HIKCameraParams){DRONE_CAMERA_HIK_EXPOSURE_TIME, DRONE_CAMERA_HIK_GAIN, DRONE_CAMERA_HIK_FRAME_RATE});
			}
			if (success != 0)
				RCLCPP_ERROR(this->get_logger(), "初始化HIK相机失败");
			else
				break;
		}
		RCLCPP_INFO(this->get_logger(), "初始化HIK相机成功");
		testFrame_ = hkcamera_.GetOneFrame();
	}else if(camera_mode_==MODE_VIDEO){
		while(rclcpp::ok()){
			std::string video_path;
			if (camera_select_ == CAMERA_SELECT_CAR) {
				video_path = VIDEO_CAR_PATH;   // 修复：用视频宏
			} else if (camera_select_ == CAMERA_SELECT_DRONE) {
				video_path = VIDEO_DRONE_PATH; // 修复：用视频宏
			} else {
				RCLCPP_ERROR(this->get_logger(), "MODE_VIDEO: 无效 camera_select");
				break;
			}

			video_cap_.open(video_path);
			if(!video_cap_.isOpened()){
				RCLCPP_ERROR(this->get_logger(), "Cannot open video: %s", video_path.c_str());
				rclcpp::sleep_for(std::chrono::milliseconds(500));
				continue;
			}
			video_cap_ >> testFrame_;
			if(testFrame_.empty()){
				RCLCPP_ERROR(this->get_logger(), "视频首帧为空: %s", video_path.c_str());
				video_cap_.release();
				rclcpp::sleep_for(std::chrono::milliseconds(500));
				continue;
			}
			break;
		}
		RCLCPP_INFO(this->get_logger(), "初始化VIDEO模式成功");
	}else if(camera_mode_==MODE_TEST){
		while(rclcpp::ok()){
			if(camera_select_ == CAMERA_SELECT_CAR){
				testFrame_=cv::imread(IMAGE_CAR_PATH);
			}else if(camera_select_ == CAMERA_SELECT_DRONE){
				testFrame_=cv::imread(IMAGE_DRONE_PATH);
			}else{
				RCLCPP_ERROR(this->get_logger(), "camera_mode_==MODE_TEST未知模式");
			}
			if(testFrame_.empty()) RCLCPP_ERROR(this->get_logger(), "初始化TEST IMAGE失败");
			else break;
		}
		RCLCPP_INFO(this->get_logger(), "初始化TEST IMAGE成功");
	}else{
		RCLCPP_ERROR(this->get_logger(), "camera_mode_未知模式");
		rclcpp::shutdown();
	}

	width_=testFrame_.cols;
	height_=testFrame_.rows;
	while(rclcpp::ok()){
		shm_id_ = shmget((key_t)shm_key_, 0, 0);
		if(shm_id_ != -1){
			RCLCPP_INFO(this->get_logger(), "共享内存存在，准备删除");
			void *shm = shmat(shm_id_, (void*)0, 0);
			if(shm != (void*)-1)
			{
				shmdt(shm);
				while(1){
						if(shmctl(shm_id_, IPC_RMID, NULL) == -1)
						{
							RCLCPP_ERROR(this->get_logger(), "共享内存删除失败");
						}
						else
						{
							RCLCPP_INFO(this->get_logger(), "共享内存删除成功");
							break;
						}
					}
			}
		}
		shm_id_ = shmget((key_t)shm_key_, sizeof(unsigned char)*width_*height_*3, IPC_CREAT | 0666);
		if(shm_id_ < 0)
			RCLCPP_ERROR(this->get_logger(), "共享内存创建失败");
		else
			return;
	}
	RCLCPP_INFO(this->get_logger(), "共享内存创建成功");
}

class CarStreamPublisher : public CameraStreamPublisher
{
public:
	CarStreamPublisher(std::string name)
		: CameraStreamPublisher(name, CAMERA_SELECT_CAR, CAMERA_CAR_MODE) // 假设车用普通摄像头
	{
		// 可以添加车特有的初始化
	}
};
class DroneStreamPublisher : public CameraStreamPublisher
{
public:
	DroneStreamPublisher(std::string name)
		: CameraStreamPublisher(name, CAMERA_SELECT_DRONE, CAMERA_DRONE_MODE) // 假设无人机用海康相机
	{
		// 可以添加无人机特有的初始化
	}
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	/*创建对应节点的共享指针对象*/
	auto car_node = std::make_shared<CarStreamPublisher>("car_camera_publisher");
	auto drone_node = std::make_shared<DroneStreamPublisher>("drone_camera_publisher");

	// 使用多线程执行器同时运行两个节点
	rclcpp::executors::MultiThreadedExecutor executor;
	executor.add_node(car_node);
	executor.add_node(drone_node);

	executor.spin();

	rclcpp::shutdown();
	return 0;
}

