#ifndef CONFIG_H
#define CONFIG_H


// struct CameraParams {
//     int triggerMode = 0;        // 触发模式，0 = off
//     //int pixelFormat = PixelType_Gvsp_BGR8_Packed;  // 像素格式，默认 BGR8
//     float exposureTime = 1600.0f;   // 曝光时间（微秒），默认 1600
//     float gain = 10.0f;             // 增益（dB），默认 10
//     float frameRate = 100.0f;       // 采集帧率（fps），默认 100
// };

enum camera_select{
    CAMERA_SELECT_CAR=1,
    CAMERA_SELECT_DRONE=2
};
enum camera_mode{
    MODE_TEST=0,
    MODE_VIDEO=1,
    MODE_HIK=2,
    MODE_CAMERA=3
};
enum detect_color{
     COLOR_RED=0,
     COLOR_BLUE=1
};
#define DETECT_COLOR COLOR_BLUE

#define CAMERA_DRONE_MODE MODE_HIK
#define CAMERA_CAR_MODE MODE_TEST

#define CAMERA_CAR_SHMID 6686
#define CAMERA_DRONE_SHMID 6687
#define CAMERA_CAR_DEVID "DA6214885"
#define CAMERA_USB_ID 2
#define CAMERA_DRONE_DEVID "DA5686129"

#define CAR_CAMERA_HIK_EXPOSURE_TIME 40000.0f
#define CAR_CAMERA_HIK_GAIN 20.0f
#define CAR_CAMERA_HIK_FRAME_RATE 20.0f
#define DRONE_CAMERA_HIK_EXPOSURE_TIME 5000.0f
#define DRONE_CAMERA_HIK_GAIN 0.0f
#define DRONE_CAMERA_HIK_FRAME_RATE 160.0f


#define STM_SERIAL_DEVICE "/dev/ttyACM0"
#define STM_SERIAL_BAUDRATE 921600


#define FPS                 30
#define CAR_CAMERA_SCALE_FACTOR 0.5f
#define DRONE_CAMERA_SCALE_FACTOR 1.0f
#define MAP_SCALE_FACTOR    1.0f

#define LASER_DRONE_CENTER_X 726
#define LASER_DRONE_CENTER_Y 519

#define IMAGE_CAR_PATH       "./image/test_image_c.jpg"
#define IMAGE_DRONE_PATH     "./image/test_image_drone.jpg"
#define VIDEO_CAR_PATH       "/media/seaber/ZHITAI/video_save/5.22.mp4"
#define VIDEO_DRONE_PATH     "./video/test_drone.mp4"
//#define MAP_PATH     "./image/map.jpg"
#define MAP_PATH     "/media/seaber/ZHITAI/RMUC2026/maptest.jpg"

#define CAMERA_DRONE_WIDTH 1280
#define CAMERA_DRONE_HEIGHT 720
#define CAMERA_DRONE_HFOV 5.7705f
#define CAMERA_DRONE_PIXEL_SIZE (CAMERA_DRONE_HFOV / (float) CAMERA_DRONE_WIDTH)
#define deg_to_rad(x) ((x)*3.14159265f/180.0f)
#define rad_to_deg(x) ((x)*180.0f/3.14159265f)

/*
# 重投影误差: 0.0880px
camera_matrix: [15046.322468634253, 0, 789.45664780763741, 0, 15021.055878552308, 705.9853512482531, 0, 0, 1]
distort_coeffs: [0.31481718253550561, -2.4332069356128074, 0.0071414875726982371, 0.0021426463226761733, 0]

*/
#define CAMERA_MATRIX (cv::Mat_<double>(3, 3) << 15046.322468634253, 0, 789.45664780763741, 0, 15021.055878552308, 705.9853512482531, 0, 0, 1)
#define DISTORT_COEFFS (cv::Mat_<double>(1, 5) << 0.31481718253550561, -2.4332069356128074, 0.0071414875726982371, 0.0021426463226761733, 0)


#endif  // CONFIG_H