#include "MvCameraControl.h"
#include <cstring>  // for memset
#include <iostream>
#include <opencv2/opencv.hpp>
struct HIKCameraParams {
    float exposureTime = 1600.0f;   // 曝光时间（微秒），默认 1600
    float gain = 10.0f;             // 增益（dB），默认 10
    float frameRate = 100.0f;       // 采集帧率（fps），默认 100
};
class HKCamera
{
private:
  void*                handle = nullptr;
  MVCC_INTVALUE        stParam;
  MV_FRAME_OUT_INFO_EX stImageInfo = {};
  unsigned char*       pData       = nullptr;
  unsigned int         nDataSize   = 0;
  cv::Mat              frame;  // OpenCV图像
  

public:
  struct HIKCameraParams params;
  HKCamera();
  bool    InitCamera(const std::string& targetSerial);
  bool    SetParameters();
  bool    StartGrabbing();
  cv::Mat GetOneFrame();
  void    StopGrabbing();
  ~HKCamera();
};