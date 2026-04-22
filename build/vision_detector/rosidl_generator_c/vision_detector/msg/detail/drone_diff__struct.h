// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vision_detector:msg/DroneDiff.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/drone_diff.h"


#ifndef VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_H_
#define VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DroneDiff in the package vision_detector.
typedef struct vision_detector__msg__DroneDiff
{
  float target_yaw;
  float target_pitch;
  float v_yaw;
  float v_pitch;
  uint32_t pc_timestamp_us;
} vision_detector__msg__DroneDiff;

// Struct for a sequence of vision_detector__msg__DroneDiff.
typedef struct vision_detector__msg__DroneDiff__Sequence
{
  vision_detector__msg__DroneDiff * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vision_detector__msg__DroneDiff__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__STRUCT_H_
