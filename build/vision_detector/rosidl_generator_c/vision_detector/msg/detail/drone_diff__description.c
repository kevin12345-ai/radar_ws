// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vision_detector:msg/DroneDiff.idl
// generated code does not contain a copyright notice

#include "vision_detector/msg/detail/drone_diff__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_type_hash_t *
vision_detector__msg__DroneDiff__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xfa, 0xec, 0x91, 0x21, 0x2e, 0x73, 0x49, 0x29,
      0xda, 0x4c, 0x6f, 0xae, 0xe2, 0x41, 0x11, 0xf5,
      0x36, 0x2c, 0x4b, 0xc0, 0xc2, 0xb9, 0x6c, 0x7e,
      0xcf, 0xcb, 0x1e, 0xa6, 0x3b, 0x92, 0x39, 0x04,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vision_detector__msg__DroneDiff__TYPE_NAME[] = "vision_detector/msg/DroneDiff";

// Define type names, field names, and default values
static char vision_detector__msg__DroneDiff__FIELD_NAME__target_yaw[] = "target_yaw";
static char vision_detector__msg__DroneDiff__FIELD_NAME__target_pitch[] = "target_pitch";
static char vision_detector__msg__DroneDiff__FIELD_NAME__v_yaw[] = "v_yaw";
static char vision_detector__msg__DroneDiff__FIELD_NAME__v_pitch[] = "v_pitch";
static char vision_detector__msg__DroneDiff__FIELD_NAME__pc_timestamp_us[] = "pc_timestamp_us";

static rosidl_runtime_c__type_description__Field vision_detector__msg__DroneDiff__FIELDS[] = {
  {
    {vision_detector__msg__DroneDiff__FIELD_NAME__target_yaw, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__DroneDiff__FIELD_NAME__target_pitch, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__DroneDiff__FIELD_NAME__v_yaw, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__DroneDiff__FIELD_NAME__v_pitch, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vision_detector__msg__DroneDiff__FIELD_NAME__pc_timestamp_us, 15, 15},
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
vision_detector__msg__DroneDiff__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vision_detector__msg__DroneDiff__TYPE_NAME, 29, 29},
      {vision_detector__msg__DroneDiff__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 target_yaw\n"
  "float32 target_pitch\n"
  "float32 v_yaw\n"
  "float32 v_pitch\n"
  "uint32 pc_timestamp_us";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vision_detector__msg__DroneDiff__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vision_detector__msg__DroneDiff__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 92, 92},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vision_detector__msg__DroneDiff__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vision_detector__msg__DroneDiff__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
