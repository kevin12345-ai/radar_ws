#include "HKCamera.h"
HKCamera::HKCamera()
{
  // 在构造函数中初始化结构体
  memset(&stParam, 0, sizeof(MVCC_INTVALUE));
  memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
}
bool HKCamera::InitCamera(const std::string& targetSerial)
{
    if(handle!= nullptr)
      MV_CC_StopGrabbing(handle);  // 确保之前的图像缓冲区被释放
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // 枚举设备（不限制厂商）
    int nRet = MV_CC_EnumDevicesEx(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList, "");
    if (MV_OK != nRet)
    {
        std::cout << "枚举设备失败! nRet [" << nRet << "]" << std::endl;
        return false;
    }

    if (stDeviceList.nDeviceNum == 0)
    {
        std::cout << "未找到任何设备!" << std::endl;
        return false;
    }

    // 遍历设备列表，寻找序列号匹配的设备
    bool bFound = false;
    for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDevInfo = stDeviceList.pDeviceInfo[i];
        if (nullptr == pDevInfo) continue;

        std::string serialNumber;
        // 根据设备类型提取序列号
        if (pDevInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            serialNumber = reinterpret_cast<char*>(pDevInfo->SpecialInfo.stGigEInfo.chSerialNumber);
        }
        else if (pDevInfo->nTLayerType == MV_USB_DEVICE)
        {
            serialNumber = reinterpret_cast<char*>(pDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        }
        else
        {
            // 其他类型设备（如CameraLink）暂不处理
            continue;
        }

        // 比较序列号（忽略大小写或精确匹配）
        if (serialNumber == targetSerial)
        {
            std::cout << "找到目标相机，序列号: " << serialNumber << std::endl;
            // 创建设备句柄
            nRet = MV_CC_CreateHandle(&handle, pDevInfo);
            if (MV_OK != nRet)
            {
                std::cout << "创建句柄失败! nRet [" << nRet << "]" << std::endl;
                return false;
            }
            // 打开设备
            nRet = MV_CC_OpenDevice(handle);
            if (MV_OK != nRet)
            {
                std::cout << "打开设备失败! nRet [" << std::showbase << std::hex << nRet << "]" << std::endl;
                MV_CC_DestroyHandle(handle);
                handle = nullptr;
                return false;
            }
            bFound = true;
            break;
        }
    }

    if (!bFound)
    {
        std::cout << "未找到序列号为 " << targetSerial << " 的相机!" << std::endl;
        return false;
    }

    return true;
}
// 设置相机参数
bool HKCamera::SetParameters()
{
  int nRet;
  // 设置触发模式为off
  nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
  if (MV_OK != nRet)
  {
    std::cout << "设置触发模式失败! nRet [" << nRet << "]" << std::endl;
    return false;
  }
  // 设置像素格式为BGR8
  nRet = MV_CC_SetEnumValue(handle, "PixelFormat", PixelType_Gvsp_BGR8_Packed);
  if (MV_OK != nRet)
  {
    std::cout << "设置像素格式失败! nRet [" << nRet << "]" << std::endl;
    return false;
  }
  std::cout << "设置像素格式为BGR8_Packed" << std::endl;
  // 获取和设置曝光时间
  MVCC_FLOATVALUE stExposureTime = {};
  nRet = MV_CC_GetFloatValue(handle, "ExposureTime", &stExposureTime);
  if (MV_OK == nRet)
  {
    float exposureTime = this->params.exposureTime;  // 默认
    if (exposureTime < stExposureTime.fMin)
      exposureTime = stExposureTime.fMin;
    if (exposureTime > stExposureTime.fMax)
      exposureTime = stExposureTime.fMax;

    std::cout << "曝光时间范围: [" << stExposureTime.fMin << ", "
              << stExposureTime.fMax << "], 当前设置: " << exposureTime
              << std::endl;

    nRet = MV_CC_SetFloatValue(handle, "ExposureTime", exposureTime);
    if (MV_OK != nRet)
    {
      std::cout << "设置曝光时间失败! nRet [" << nRet << "]" << std::endl;
      return false;
    }
  }
  // 获取和设置增益
  MVCC_FLOATVALUE stGain = {};
  nRet                   = MV_CC_GetFloatValue(handle, "Gain", &stGain);
  if (MV_OK == nRet)
  {
    float gain = this->params.gain;  // 默认
    nRet       = MV_CC_SetFloatValue(handle, "Gain", gain);
    if (MV_OK != nRet)
    {
      std::cout << "设置增益失败! nRet [" << nRet << "]" << std::endl;
      return false;
    }
    std::cout << "增益范围: [" << stGain.fMin << ", " << stGain.fMax
              << "], 当前值: " << stGain.fCurValue << std::endl;

    if (stGain.fCurValue < stGain.fMin || stGain.fCurValue > stGain.fMax)
    {
      float gain = stGain.fMin;  // 使用最小值
      nRet       = MV_CC_SetFloatValue(handle, "Gain", gain);
      if (MV_OK != nRet)
      {
        std::cout << "设置增益失败! nRet [" << nRet << "]" << std::endl;
        return false;
      }
    }
  }
  // 获取和设置帧率
  MVCC_FLOATVALUE stFrameRate = {};
  nRet = MV_CC_GetFloatValue(handle, "AcquisitionFrameRate", &stFrameRate);
  if (MV_OK == nRet)
  {
    float frameRate = this->params.frameRate;  // 默认30fps
    if (frameRate < stFrameRate.fMin)
      frameRate = stFrameRate.fMin;
    if (frameRate > stFrameRate.fMax)
      frameRate = stFrameRate.fMax;

    std::cout << "帧率范围: [" << stFrameRate.fMin << ", " << stFrameRate.fMax
              << "], 当前设置: " << frameRate << std::endl;
    nRet = MV_CC_SetFloatValue(handle, "AcquisitionFrameRate", frameRate);
    if (MV_OK != nRet)
    {
      std::cout << "设置帧率失败! nRet [" << nRet << "]" << std::endl;
      // 这个错误不影响主要功能，可以继续
    }
  }
  return true;
}
// 开始取图
bool HKCamera::StartGrabbing()
{
  // 开始取流
  int nRet = MV_CC_StartGrabbing(handle);
  if (MV_OK != nRet)
  {
    std::cout << "开始取流失败! nRet [" << nRet << "]" << std::endl;
    return false;
  }
  // 获取数据包大小
  MVCC_INTVALUE stParam;
  nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
  if (MV_OK != nRet)
  {
    std::cout << "获取数据包大小失败! nRet [" << nRet << "]" << std::endl;
    return false;
  }
  // 分配资源
  nDataSize = stParam.nCurValue;
  pData     = (unsigned char*)malloc(nDataSize);
  if (pData == nullptr)
  {
    std::cout << "内存分配失败!" << std::endl;
    return false;
  }
  return true;
}
// 获取一帧图像并显示
cv::Mat HKCamera::GetOneFrame()
{
  if (handle == nullptr || pData == nullptr)
  {
    return cv::Mat();
  }
  int nRet =
    MV_CC_GetOneFrameTimeout(handle, pData, nDataSize, &stImageInfo, 1000);
  if (MV_OK != nRet)
  {
    std::cout << "获取一帧图像失败! nRet [" << nRet << "]" << std::endl;
    return cv::Mat();
  }
  // std::cout << "获取一帧图像成功: Width[" << stImageInfo.nWidth << "] Height["
  //           << stImageInfo.nHeight << "] PixelType[0x" << std::hex
  //           << stImageInfo.enPixelType << std::dec << "] FrameNum["
  //           << stImageInfo.nFrameNum << "]" << std::endl;
  // 转换为OpenCV格式并显示
  if (stImageInfo.enPixelType == PixelType_Gvsp_BGR8_Packed)
  {
    // 直接使用BGR数据创建Mat
    frame = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC3, pData);
    // 简单的图像增强
    //cv::Mat temp;
    // 轻微提升对比度
    //frame.convertTo(temp, -1, 1.1, 0);
    //frame = temp;
  }
  else
  {
    std::cout << "不支持的像素格式: 0x" << std::hex << stImageInfo.enPixelType
              << std::dec << std::endl;
    return cv::Mat();
  }
  return frame;
}
// 停止采集
void HKCamera::StopGrabbing()
{
  if (handle != nullptr)
  {
    MV_CC_StopGrabbing(handle);
    MV_CC_CloseDevice(handle);
    MV_CC_DestroyHandle(handle);
    handle = nullptr;
  }
  if (pData != nullptr)
  {
    free(pData);
    pData = nullptr;
  }
}
HKCamera::~HKCamera()
{
  StopGrabbing();
}