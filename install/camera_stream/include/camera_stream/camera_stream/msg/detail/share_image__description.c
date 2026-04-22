// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

#include "camera_stream/msg/detail/share_image__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_camera_stream
const rosidl_type_hash_t *
camera_stream__msg__ShareImage__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xba, 0x2c, 0x02, 0x76, 0x7d, 0x40, 0x11, 0xa3,
      0x13, 0x7d, 0x06, 0x0b, 0xab, 0x0b, 0xbe, 0x88,
      0x8b, 0x23, 0x5d, 0x96, 0x19, 0x9b, 0xd0, 0x52,
      0xb4, 0x68, 0x1b, 0x8f, 0xb0, 0x57, 0x1c, 0x45,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char camera_stream__msg__ShareImage__TYPE_NAME[] = "camera_stream/msg/ShareImage";

// Define type names, field names, and default values
static char camera_stream__msg__ShareImage__FIELD_NAME__camera_select[] = "camera_select";
static char camera_stream__msg__ShareImage__FIELD_NAME__shm_id[] = "shm_id";
static char camera_stream__msg__ShareImage__FIELD_NAME__width[] = "width";
static char camera_stream__msg__ShareImage__FIELD_NAME__height[] = "height";
static char camera_stream__msg__ShareImage__FIELD_NAME__frame_id[] = "frame_id";
static char camera_stream__msg__ShareImage__FIELD_NAME__enable[] = "enable";
static char camera_stream__msg__ShareImage__FIELD_NAME__shm_size[] = "shm_size";
static char camera_stream__msg__ShareImage__FIELD_NAME__timestamp_us[] = "timestamp_us";

static rosidl_runtime_c__type_description__Field camera_stream__msg__ShareImage__FIELDS[] = {
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__camera_select, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__shm_id, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__height, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__frame_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__enable, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__shm_size, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {camera_stream__msg__ShareImage__FIELD_NAME__timestamp_us, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
camera_stream__msg__ShareImage__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {camera_stream__msg__ShareImage__TYPE_NAME, 28, 28},
      {camera_stream__msg__ShareImage__FIELDS, 8, 8},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint32 camera_select\n"
  "uint32 shm_id\n"
  "uint32 width\n"
  "uint32 height\n"
  "uint32 frame_id\n"
  "bool enable\n"
  "uint32 shm_size\n"
  "uint64 timestamp_us";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
camera_stream__msg__ShareImage__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {camera_stream__msg__ShareImage__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 125, 125},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
camera_stream__msg__ShareImage__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *camera_stream__msg__ShareImage__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
