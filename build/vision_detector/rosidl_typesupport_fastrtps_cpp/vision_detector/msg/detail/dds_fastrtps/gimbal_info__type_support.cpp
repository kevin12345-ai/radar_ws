// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice
#include "vision_detector/msg/detail/gimbal_info__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vision_detector/msg/detail/gimbal_info__functions.h"
#include "vision_detector/msg/detail/gimbal_info__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace vision_detector
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
cdr_serialize(
  const vision_detector::msg::GimbalInfo & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: current_yaw
  cdr << ros_message.current_yaw;

  // Member: current_pitch
  cdr << ros_message.current_pitch;

  // Member: last_pc_timestamp_us
  cdr << ros_message.last_pc_timestamp_us;

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vision_detector::msg::GimbalInfo & ros_message)
{
  // Member: current_yaw
  cdr >> ros_message.current_yaw;

  // Member: current_pitch
  cdr >> ros_message.current_pitch;

  // Member: last_pc_timestamp_us
  cdr >> ros_message.last_pc_timestamp_us;

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
get_serialized_size(
  const vision_detector::msg::GimbalInfo & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: current_yaw
  {
    size_t item_size = sizeof(ros_message.current_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: current_pitch
  {
    size_t item_size = sizeof(ros_message.current_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: last_pc_timestamp_us
  {
    size_t item_size = sizeof(ros_message.last_pc_timestamp_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
max_serialized_size_GimbalInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: current_yaw
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: current_pitch
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: last_pc_timestamp_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vision_detector::msg::GimbalInfo;
    is_plain =
      (
      offsetof(DataType, last_pc_timestamp_us) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
cdr_serialize_key(
  const vision_detector::msg::GimbalInfo & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: current_yaw
  cdr << ros_message.current_yaw;

  // Member: current_pitch
  cdr << ros_message.current_pitch;

  // Member: last_pc_timestamp_us
  cdr << ros_message.last_pc_timestamp_us;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
get_serialized_size_key(
  const vision_detector::msg::GimbalInfo & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: current_yaw
  {
    size_t item_size = sizeof(ros_message.current_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: current_pitch
  {
    size_t item_size = sizeof(ros_message.current_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: last_pc_timestamp_us
  {
    size_t item_size = sizeof(ros_message.last_pc_timestamp_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vision_detector
max_serialized_size_key_GimbalInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: current_yaw
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: current_pitch
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: last_pc_timestamp_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vision_detector::msg::GimbalInfo;
    is_plain =
      (
      offsetof(DataType, last_pc_timestamp_us) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _GimbalInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vision_detector::msg::GimbalInfo *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _GimbalInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vision_detector::msg::GimbalInfo *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _GimbalInfo__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vision_detector::msg::GimbalInfo *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _GimbalInfo__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_GimbalInfo(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _GimbalInfo__callbacks = {
  "vision_detector::msg",
  "GimbalInfo",
  _GimbalInfo__cdr_serialize,
  _GimbalInfo__cdr_deserialize,
  _GimbalInfo__get_serialized_size,
  _GimbalInfo__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _GimbalInfo__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GimbalInfo__callbacks,
  get_message_typesupport_handle_function,
  &vision_detector__msg__GimbalInfo__get_type_hash,
  &vision_detector__msg__GimbalInfo__get_type_description,
  &vision_detector__msg__GimbalInfo__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vision_detector

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vision_detector
const rosidl_message_type_support_t *
get_message_type_support_handle<vision_detector::msg::GimbalInfo>()
{
  return &vision_detector::msg::typesupport_fastrtps_cpp::_GimbalInfo__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vision_detector, msg, GimbalInfo)() {
  return &vision_detector::msg::typesupport_fastrtps_cpp::_GimbalInfo__handle;
}

#ifdef __cplusplus
}
#endif
