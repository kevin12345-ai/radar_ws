// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vision_detector:msg/DroneDiff.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/drone_diff.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__BUILDER_HPP_
#define VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vision_detector/msg/detail/drone_diff__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vision_detector
{

namespace msg
{

namespace builder
{

class Init_DroneDiff_pc_timestamp_us
{
public:
  explicit Init_DroneDiff_pc_timestamp_us(::vision_detector::msg::DroneDiff & msg)
  : msg_(msg)
  {}
  ::vision_detector::msg::DroneDiff pc_timestamp_us(::vision_detector::msg::DroneDiff::_pc_timestamp_us_type arg)
  {
    msg_.pc_timestamp_us = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_detector::msg::DroneDiff msg_;
};

class Init_DroneDiff_v_pitch
{
public:
  explicit Init_DroneDiff_v_pitch(::vision_detector::msg::DroneDiff & msg)
  : msg_(msg)
  {}
  Init_DroneDiff_pc_timestamp_us v_pitch(::vision_detector::msg::DroneDiff::_v_pitch_type arg)
  {
    msg_.v_pitch = std::move(arg);
    return Init_DroneDiff_pc_timestamp_us(msg_);
  }

private:
  ::vision_detector::msg::DroneDiff msg_;
};

class Init_DroneDiff_v_yaw
{
public:
  explicit Init_DroneDiff_v_yaw(::vision_detector::msg::DroneDiff & msg)
  : msg_(msg)
  {}
  Init_DroneDiff_v_pitch v_yaw(::vision_detector::msg::DroneDiff::_v_yaw_type arg)
  {
    msg_.v_yaw = std::move(arg);
    return Init_DroneDiff_v_pitch(msg_);
  }

private:
  ::vision_detector::msg::DroneDiff msg_;
};

class Init_DroneDiff_target_pitch
{
public:
  explicit Init_DroneDiff_target_pitch(::vision_detector::msg::DroneDiff & msg)
  : msg_(msg)
  {}
  Init_DroneDiff_v_yaw target_pitch(::vision_detector::msg::DroneDiff::_target_pitch_type arg)
  {
    msg_.target_pitch = std::move(arg);
    return Init_DroneDiff_v_yaw(msg_);
  }

private:
  ::vision_detector::msg::DroneDiff msg_;
};

class Init_DroneDiff_target_yaw
{
public:
  Init_DroneDiff_target_yaw()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DroneDiff_target_pitch target_yaw(::vision_detector::msg::DroneDiff::_target_yaw_type arg)
  {
    msg_.target_yaw = std::move(arg);
    return Init_DroneDiff_target_pitch(msg_);
  }

private:
  ::vision_detector::msg::DroneDiff msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vision_detector::msg::DroneDiff>()
{
  return vision_detector::msg::builder::Init_DroneDiff_target_yaw();
}

}  // namespace vision_detector

#endif  // VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__BUILDER_HPP_
