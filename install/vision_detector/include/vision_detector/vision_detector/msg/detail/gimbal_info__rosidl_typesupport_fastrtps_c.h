// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice
#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vision_detector/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vision_detector/msg/detail/gimbal_info__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
bool cdr_serialize_vision_detector__msg__GimbalInfo(
  const vision_detector__msg__GimbalInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
bool cdr_deserialize_vision_detector__msg__GimbalInfo(
  eprosima::fastcdr::Cdr &,
  vision_detector__msg__GimbalInfo * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
size_t get_serialized_size_vision_detector__msg__GimbalInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
size_t max_serialized_size_vision_detector__msg__GimbalInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
bool cdr_serialize_key_vision_detector__msg__GimbalInfo(
  const vision_detector__msg__GimbalInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
size_t get_serialized_size_key_vision_detector__msg__GimbalInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
size_t max_serialized_size_key_vision_detector__msg__GimbalInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vision_detector
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vision_detector, msg, GimbalInfo)();

#ifdef __cplusplus
}
#endif

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
