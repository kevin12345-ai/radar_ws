// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/gimbal_info.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_HPP_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vision_detector__msg__GimbalInfo __attribute__((deprecated))
#else
# define DEPRECATED__vision_detector__msg__GimbalInfo __declspec(deprecated)
#endif

namespace vision_detector
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GimbalInfo_
{
  using Type = GimbalInfo_<ContainerAllocator>;

  explicit GimbalInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_yaw = 0.0f;
      this->current_pitch = 0.0f;
      this->last_pc_timestamp_us = 0ul;
    }
  }

  explicit GimbalInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_yaw = 0.0f;
      this->current_pitch = 0.0f;
      this->last_pc_timestamp_us = 0ul;
    }
  }

  // field types and members
  using _current_yaw_type =
    float;
  _current_yaw_type current_yaw;
  using _current_pitch_type =
    float;
  _current_pitch_type current_pitch;
  using _last_pc_timestamp_us_type =
    uint32_t;
  _last_pc_timestamp_us_type last_pc_timestamp_us;

  // setters for named parameter idiom
  Type & set__current_yaw(
    const float & _arg)
  {
    this->current_yaw = _arg;
    return *this;
  }
  Type & set__current_pitch(
    const float & _arg)
  {
    this->current_pitch = _arg;
    return *this;
  }
  Type & set__last_pc_timestamp_us(
    const uint32_t & _arg)
  {
    this->last_pc_timestamp_us = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vision_detector::msg::GimbalInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const vision_detector::msg::GimbalInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vision_detector::msg::GimbalInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vision_detector::msg::GimbalInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vision_detector__msg__GimbalInfo
    std::shared_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vision_detector__msg__GimbalInfo
    std::shared_ptr<vision_detector::msg::GimbalInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GimbalInfo_ & other) const
  {
    if (this->current_yaw != other.current_yaw) {
      return false;
    }
    if (this->current_pitch != other.current_pitch) {
      return false;
    }
    if (this->last_pc_timestamp_us != other.last_pc_timestamp_us) {
      return false;
    }
    return true;
  }
  bool operator!=(const GimbalInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GimbalInfo_

// alias to use template instance with default allocator
using GimbalInfo =
  vision_detector::msg::GimbalInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vision_detector

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_HPP_
