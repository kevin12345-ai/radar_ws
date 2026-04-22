// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "camera_stream/msg/share_image.hpp"


#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__BUILDER_HPP_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "camera_stream/msg/detail/share_image__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace camera_stream
{

namespace msg
{

namespace builder
{

class Init_ShareImage_timestamp_us
{
public:
  explicit Init_ShareImage_timestamp_us(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  ::camera_stream::msg::ShareImage timestamp_us(::camera_stream::msg::ShareImage::_timestamp_us_type arg)
  {
    msg_.timestamp_us = std::move(arg);
    return std::move(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_shm_size
{
public:
  explicit Init_ShareImage_shm_size(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_timestamp_us shm_size(::camera_stream::msg::ShareImage::_shm_size_type arg)
  {
    msg_.shm_size = std::move(arg);
    return Init_ShareImage_timestamp_us(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_enable
{
public:
  explicit Init_ShareImage_enable(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_shm_size enable(::camera_stream::msg::ShareImage::_enable_type arg)
  {
    msg_.enable = std::move(arg);
    return Init_ShareImage_shm_size(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_frame_id
{
public:
  explicit Init_ShareImage_frame_id(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_enable frame_id(::camera_stream::msg::ShareImage::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_ShareImage_enable(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_height
{
public:
  explicit Init_ShareImage_height(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_frame_id height(::camera_stream::msg::ShareImage::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_ShareImage_frame_id(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_width
{
public:
  explicit Init_ShareImage_width(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_height width(::camera_stream::msg::ShareImage::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_ShareImage_height(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_shm_id
{
public:
  explicit Init_ShareImage_shm_id(::camera_stream::msg::ShareImage & msg)
  : msg_(msg)
  {}
  Init_ShareImage_width shm_id(::camera_stream::msg::ShareImage::_shm_id_type arg)
  {
    msg_.shm_id = std::move(arg);
    return Init_ShareImage_width(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

class Init_ShareImage_camera_select
{
public:
  Init_ShareImage_camera_select()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ShareImage_shm_id camera_select(::camera_stream::msg::ShareImage::_camera_select_type arg)
  {
    msg_.camera_select = std::move(arg);
    return Init_ShareImage_shm_id(msg_);
  }

private:
  ::camera_stream::msg::ShareImage msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::camera_stream::msg::ShareImage>()
{
  return camera_stream::msg::builder::Init_ShareImage_camera_select();
}

}  // namespace camera_stream

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__BUILDER_HPP_
