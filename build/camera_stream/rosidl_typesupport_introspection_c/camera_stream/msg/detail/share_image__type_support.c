// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "camera_stream/msg/detail/share_image__rosidl_typesupport_introspection_c.h"
#include "camera_stream/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "camera_stream/msg/detail/share_image__functions.h"
#include "camera_stream/msg/detail/share_image__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  camera_stream__msg__ShareImage__init(message_memory);
}

void camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_fini_function(void * message_memory)
{
  camera_stream__msg__ShareImage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_member_array[8] = {
  {
    "camera_select",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, camera_select),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "shm_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, shm_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "height",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, height),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "enable",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, enable),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "shm_size",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, shm_size),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp_us",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(camera_stream__msg__ShareImage, timestamp_us),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_members = {
  "camera_stream__msg",  // message namespace
  "ShareImage",  // message name
  8,  // number of fields
  sizeof(camera_stream__msg__ShareImage),
  false,  // has_any_key_member_
  camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_member_array,  // message members
  camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_init_function,  // function to initialize message memory (memory has to be allocated)
  camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_type_support_handle = {
  0,
  &camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_members,
  get_message_typesupport_handle_function,
  &camera_stream__msg__ShareImage__get_type_hash,
  &camera_stream__msg__ShareImage__get_type_description,
  &camera_stream__msg__ShareImage__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_camera_stream
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, camera_stream, msg, ShareImage)() {
  if (!camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_type_support_handle.typesupport_identifier) {
    camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &camera_stream__msg__ShareImage__rosidl_typesupport_introspection_c__ShareImage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
