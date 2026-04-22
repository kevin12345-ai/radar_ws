// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "camera_stream/msg/share_image.hpp"


#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__TRAITS_HPP_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "camera_stream/msg/detail/share_image__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace camera_stream
{

namespace msg
{

inline void to_flow_style_yaml(
  const ShareImage & msg,
  std::ostream & out)
{
  out << "{";
  // member: camera_select
  {
    out << "camera_select: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_select, out);
    out << ", ";
  }

  // member: shm_id
  {
    out << "shm_id: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_id, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << ", ";
  }

  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: enable
  {
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
    out << ", ";
  }

  // member: shm_size
  {
    out << "shm_size: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_size, out);
    out << ", ";
  }

  // member: timestamp_us
  {
    out << "timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_us, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ShareImage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: camera_select
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "camera_select: ";
    rosidl_generator_traits::value_to_yaml(msg.camera_select, out);
    out << "\n";
  }

  // member: shm_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shm_id: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_id, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }

  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: enable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
    out << "\n";
  }

  // member: shm_size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shm_size: ";
    rosidl_generator_traits::value_to_yaml(msg.shm_size, out);
    out << "\n";
  }

  // member: timestamp_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp_us, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ShareImage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace camera_stream

namespace rosidl_generator_traits
{

[[deprecated("use camera_stream::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const camera_stream::msg::ShareImage & msg,
  std::ostream & out, size_t indentation = 0)
{
  camera_stream::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use camera_stream::msg::to_yaml() instead")]]
inline std::string to_yaml(const camera_stream::msg::ShareImage & msg)
{
  return camera_stream::msg::to_yaml(msg);
}

template<>
inline const char * data_type<camera_stream::msg::ShareImage>()
{
  return "camera_stream::msg::ShareImage";
}

template<>
inline const char * name<camera_stream::msg::ShareImage>()
{
  return "camera_stream/msg/ShareImage";
}

template<>
struct has_fixed_size<camera_stream::msg::ShareImage>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<camera_stream::msg::ShareImage>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<camera_stream::msg::ShareImage>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__TRAITS_HPP_
