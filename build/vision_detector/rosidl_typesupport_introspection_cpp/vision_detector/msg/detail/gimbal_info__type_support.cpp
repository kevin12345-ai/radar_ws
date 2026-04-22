// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vision_detector/msg/detail/gimbal_info__functions.h"
#include "vision_detector/msg/detail/gimbal_info__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vision_detector
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void GimbalInfo_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vision_detector::msg::GimbalInfo(_init);
}

void GimbalInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vision_detector::msg::GimbalInfo *>(message_memory);
  typed_message->~GimbalInfo();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GimbalInfo_message_member_array[3] = {
  {
    "current_yaw",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_detector::msg::GimbalInfo, current_yaw),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "current_pitch",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_detector::msg::GimbalInfo, current_pitch),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "last_pc_timestamp_us",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_detector::msg::GimbalInfo, last_pc_timestamp_us),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GimbalInfo_message_members = {
  "vision_detector::msg",  // message namespace
  "GimbalInfo",  // message name
  3,  // number of fields
  sizeof(vision_detector::msg::GimbalInfo),
  false,  // has_any_key_member_
  GimbalInfo_message_member_array,  // message members
  GimbalInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  GimbalInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GimbalInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GimbalInfo_message_members,
  get_message_typesupport_handle_function,
  &vision_detector__msg__GimbalInfo__get_type_hash,
  &vision_detector__msg__GimbalInfo__get_type_description,
  &vision_detector__msg__GimbalInfo__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vision_detector


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vision_detector::msg::GimbalInfo>()
{
  return &::vision_detector::msg::rosidl_typesupport_introspection_cpp::GimbalInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vision_detector, msg, GimbalInfo)() {
  return &::vision_detector::msg::rosidl_typesupport_introspection_cpp::GimbalInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
