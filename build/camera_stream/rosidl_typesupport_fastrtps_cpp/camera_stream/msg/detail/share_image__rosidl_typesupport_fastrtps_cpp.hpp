// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "camera_stream/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "camera_stream/msg/detail/share_image__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace camera_stream
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
cdr_serialize(
  const camera_stream::msg::ShareImage & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  camera_stream::msg::ShareImage & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
get_serialized_size(
  const camera_stream::msg::ShareImage & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
max_serialized_size_ShareImage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
cdr_serialize_key(
  const camera_stream::msg::ShareImage & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
get_serialized_size_key(
  const camera_stream::msg::ShareImage & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
max_serialized_size_key_ShareImage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace camera_stream

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_camera_stream
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, camera_stream, msg, ShareImage)();

#ifdef __cplusplus
}
#endif

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
