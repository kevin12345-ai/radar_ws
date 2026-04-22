// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/gimbal_info.h"


#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_H_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/GimbalInfo in the package vision_detector.
typedef struct vision_detector__msg__GimbalInfo
{
  float current_yaw;
  float current_pitch;
  uint32_t last_pc_timestamp_us;
} vision_detector__msg__GimbalInfo;

// Struct for a sequence of vision_detector__msg__GimbalInfo.
typedef struct vision_detector__msg__GimbalInfo__Sequence
{
  vision_detector__msg__GimbalInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vision_detector__msg__GimbalInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__STRUCT_H_
