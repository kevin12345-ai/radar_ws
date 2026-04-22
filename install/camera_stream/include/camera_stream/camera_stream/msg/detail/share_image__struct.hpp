// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "camera_stream/msg/share_image.hpp"


#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_HPP_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__camera_stream__msg__ShareImage __attribute__((deprecated))
#else
# define DEPRECATED__camera_stream__msg__ShareImage __declspec(deprecated)
#endif

namespace camera_stream
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ShareImage_
{
  using Type = ShareImage_<ContainerAllocator>;

  explicit ShareImage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->camera_select = 0ul;
      this->shm_id = 0ul;
      this->width = 0ul;
      this->height = 0ul;
      this->frame_id = 0ul;
      this->enable = false;
      this->shm_size = 0ul;
      this->timestamp_us = 0ull;
    }
  }

  explicit ShareImage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->camera_select = 0ul;
      this->shm_id = 0ul;
      this->width = 0ul;
      this->height = 0ul;
      this->frame_id = 0ul;
      this->enable = false;
      this->shm_size = 0ul;
      this->timestamp_us = 0ull;
    }
  }

  // field types and members
  using _camera_select_type =
    uint32_t;
  _camera_select_type camera_select;
  using _shm_id_type =
    uint32_t;
  _shm_id_type shm_id;
  using _width_type =
    uint32_t;
  _width_type width;
  using _height_type =
    uint32_t;
  _height_type height;
  using _frame_id_type =
    uint32_t;
  _frame_id_type frame_id;
  using _enable_type =
    bool;
  _enable_type enable;
  using _shm_size_type =
    uint32_t;
  _shm_size_type shm_size;
  using _timestamp_us_type =
    uint64_t;
  _timestamp_us_type timestamp_us;

  // setters for named parameter idiom
  Type & set__camera_select(
    const uint32_t & _arg)
  {
    this->camera_select = _arg;
    return *this;
  }
  Type & set__shm_id(
    const uint32_t & _arg)
  {
    this->shm_id = _arg;
    return *this;
  }
  Type & set__width(
    const uint32_t & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__height(
    const uint32_t & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__frame_id(
    const uint32_t & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__enable(
    const bool & _arg)
  {
    this->enable = _arg;
    return *this;
  }
  Type & set__shm_size(
    const uint32_t & _arg)
  {
    this->shm_size = _arg;
    return *this;
  }
  Type & set__timestamp_us(
    const uint64_t & _arg)
  {
    this->timestamp_us = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    camera_stream::msg::ShareImage_<ContainerAllocator> *;
  using ConstRawPtr =
    const camera_stream::msg::ShareImage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<camera_stream::msg::ShareImage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<camera_stream::msg::ShareImage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      camera_stream::msg::ShareImage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<camera_stream::msg::ShareImage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      camera_stream::msg::ShareImage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<camera_stream::msg::ShareImage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<camera_stream::msg::ShareImage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<camera_stream::msg::ShareImage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__camera_stream__msg__ShareImage
    std::shared_ptr<camera_stream::msg::ShareImage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__camera_stream__msg__ShareImage
    std::shared_ptr<camera_stream::msg::ShareImage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ShareImage_ & other) const
  {
    if (this->camera_select != other.camera_select) {
      return false;
    }
    if (this->shm_id != other.shm_id) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->enable != other.enable) {
      return false;
    }
    if (this->shm_size != other.shm_size) {
      return false;
    }
    if (this->timestamp_us != other.timestamp_us) {
      return false;
    }
    return true;
  }
  bool operator!=(const ShareImage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ShareImage_

// alias to use template instance with default allocator
using ShareImage =
  camera_stream::msg::ShareImage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace camera_stream

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_HPP_
