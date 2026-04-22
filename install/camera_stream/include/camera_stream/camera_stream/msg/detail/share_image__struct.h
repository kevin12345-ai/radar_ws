// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "camera_stream/msg/share_image.h"


#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_H_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ShareImage in the package camera_stream.
typedef struct camera_stream__msg__ShareImage
{
  uint32_t camera_select;
  uint32_t shm_id;
  uint32_t width;
  uint32_t height;
  uint32_t frame_id;
  bool enable;
  uint32_t shm_size;
  uint64_t timestamp_us;
} camera_stream__msg__ShareImage;

// Struct for a sequence of camera_stream__msg__ShareImage.
typedef struct camera_stream__msg__ShareImage__Sequence
{
  camera_stream__msg__ShareImage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} camera_stream__msg__ShareImage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__STRUCT_H_
