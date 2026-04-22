// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vision_detector:msg/DroneDiff.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/drone_diff.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_HPP_
#define VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vision_detector__msg__DroneDiff __attribute__((deprecated))
#else
# define DEPRECATED__vision_detector__msg__DroneDiff __declspec(deprecated)
#endif

namespace vision_detector
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DroneDiff_
{
  using Type = DroneDiff_<ContainerAllocator>;

  explicit DroneDiff_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_yaw = 0.0f;
      this->target_pitch = 0.0f;
      this->v_yaw = 0.0f;
      this->v_pitch = 0.0f;
      this->pc_timestamp_us = 0ul;
    }
  }

  explicit DroneDiff_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_yaw = 0.0f;
      this->target_pitch = 0.0f;
      this->v_yaw = 0.0f;
      this->v_pitch = 0.0f;
      this->pc_timestamp_us = 0ul;
    }
  }

  // field types and members
  using _target_yaw_type =
    float;
  _target_yaw_type target_yaw;
  using _target_pitch_type =
    float;
  _target_pitch_type target_pitch;
  using _v_yaw_type =
    float;
  _v_yaw_type v_yaw;
  using _v_pitch_type =
    float;
  _v_pitch_type v_pitch;
  using _pc_timestamp_us_type =
    uint32_t;
  _pc_timestamp_us_type pc_timestamp_us;

  // setters for named parameter idiom
  Type & set__target_yaw(
    const float & _arg)
  {
    this->target_yaw = _arg;
    return *this;
  }
  Type & set__target_pitch(
    const float & _arg)
  {
    this->target_pitch = _arg;
    return *this;
  }
  Type & set__v_yaw(
    const float & _arg)
  {
    this->v_yaw = _arg;
    return *this;
  }
  Type & set__v_pitch(
    const float & _arg)
  {
    this->v_pitch = _arg;
    return *this;
  }
  Type & set__pc_timestamp_us(
    const uint32_t & _arg)
  {
    this->pc_timestamp_us = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vision_detector::msg::DroneDiff_<ContainerAllocator> *;
  using ConstRawPtr =
    const vision_detector::msg::DroneDiff_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vision_detector::msg::DroneDiff_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vision_detector::msg::DroneDiff_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vision_detector__msg__DroneDiff
    std::shared_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vision_detector__msg__DroneDiff
    std::shared_ptr<vision_detector::msg::DroneDiff_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DroneDiff_ & other) const
  {
    if (this->target_yaw != other.target_yaw) {
      return false;
    }
    if (this->target_pitch != other.target_pitch) {
      return false;
    }
    if (this->v_yaw != other.v_yaw) {
      return false;
    }
    if (this->v_pitch != other.v_pitch) {
      return false;
    }
    if (this->pc_timestamp_us != other.pc_timestamp_us) {
      return false;
    }
    return true;
  }
  bool operator!=(const DroneDiff_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DroneDiff_

// alias to use template instance with default allocator
using DroneDiff =
  vision_detector::msg::DroneDiff_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vision_detector

#endif  // VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_HPP_
