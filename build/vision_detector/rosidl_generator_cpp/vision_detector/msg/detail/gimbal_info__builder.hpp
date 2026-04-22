// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/gimbal_info.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__BUILDER_HPP_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vision_detector/msg/detail/gimbal_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vision_detector
{

namespace msg
{

namespace builder
{

class Init_GimbalInfo_last_pc_timestamp_us
{
public:
  explicit Init_GimbalInfo_last_pc_timestamp_us(::vision_detector::msg::GimbalInfo & msg)
  : msg_(msg)
  {}
  ::vision_detector::msg::GimbalInfo last_pc_timestamp_us(::vision_detector::msg::GimbalInfo::_last_pc_timestamp_us_type arg)
  {
    msg_.last_pc_timestamp_us = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_detector::msg::GimbalInfo msg_;
};

class Init_GimbalInfo_current_pitch
{
public:
  explicit Init_GimbalInfo_current_pitch(::vision_detector::msg::GimbalInfo & msg)
  : msg_(msg)
  {}
  Init_GimbalInfo_last_pc_timestamp_us current_pitch(::vision_detector::msg::GimbalInfo::_current_pitch_type arg)
  {
    msg_.current_pitch = std::move(arg);
    return Init_GimbalInfo_last_pc_timestamp_us(msg_);
  }

private:
  ::vision_detector::msg::GimbalInfo msg_;
};

class Init_GimbalInfo_current_yaw
{
public:
  Init_GimbalInfo_current_yaw()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GimbalInfo_current_pitch current_yaw(::vision_detector::msg::GimbalInfo::_current_yaw_type arg)
  {
    msg_.current_yaw = std::move(arg);
    return Init_GimbalInfo_current_pitch(msg_);
  }

private:
  ::vision_detector::msg::GimbalInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vision_detector::msg::GimbalInfo>()
{
  return vision_detector::msg::builder::Init_GimbalInfo_current_yaw();
}

}  // namespace vision_detector

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__BUILDER_HPP_
