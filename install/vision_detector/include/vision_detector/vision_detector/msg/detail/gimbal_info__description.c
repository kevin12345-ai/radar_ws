// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

#include "vision_detector/msg/detail/gimbal_info__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_type_hash_t *
vision_detector__msg__GimbalInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0e, 0x28, 0xfc, 0xc4, 0x76, 0xbc, 0x52, 0x5e,
      0x3f, 0x5c, 0x27, 0x7e, 0xbc, 0x9e, 0xc9, 0x5f,
      0xf5, 0x18, 0x8f, 0x74, 0x60, 0xca, 0x4d, 0x11,
      0x4a, 0x29, 0x63, 0xe1, 0x0e, 0xa4, 0x47, 0xb1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vision_detector__msg__GimbalInfo__TYPE_NAME[] = "vision_detector/msg/GimbalInfo";

// Define type names, field names, and default values
static char vision_detector__msg__GimbalInfo__FIELD_NAME__current_yaw[] = "current_yaw";
static char vision_detector__msg__GimbalInfo__FIELD_NAME__current_pitch[] = "current_pitch";
static char vision_detector__msg__GimbalInfo__FIELD_NAME__last_pc_timestamp_us[] = "last_pc_timestamp_us";

static rosidl_runtime_c__type_description__Field vision_detector__msg__GimbalInfo__FIELDS[] = {
  {
    {vision_detector__msg__GimbalInfo__FIELD_NAME__current_yaw, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__GimbalInfo__FIELD_NAME__current_pitch, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__GimbalInfo__FIELD_NAME__last_pc_timestamp_us, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vision_detector__msg__GimbalInfo__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vision_detector__msg__GimbalInfo__TYPE_NAME, 30, 30},
      {vision_detector__msg__GimbalInfo__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 current_yaw\n"
  "float32 current_pitch\n"
  "uint32 last_pc_timestamp_us";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vision_detector__msg__GimbalInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vision_detector__msg__GimbalInfo__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 69, 69},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vision_detector__msg__GimbalInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vision_detector__msg__GimbalInfo__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
