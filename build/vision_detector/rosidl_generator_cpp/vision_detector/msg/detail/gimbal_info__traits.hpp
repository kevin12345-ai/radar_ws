// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/gimbal_info.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__TRAITS_HPP_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vision_detector/msg/detail/gimbal_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vision_detector
{

namespace msg
{

inline void to_flow_style_yaml(
  const GimbalInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_yaw
  {
    out << "current_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.current_yaw, out);
    out << ", ";
  }

  // member: current_pitch
  {
    out << "current_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.current_pitch, out);
    out << ", ";
  }

  // member: last_pc_timestamp_us
  {
    out << "last_pc_timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.last_pc_timestamp_us, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GimbalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.current_yaw, out);
    out << "\n";
  }

  // member: current_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.current_pitch, out);
    out << "\n";
  }

  // member: last_pc_timestamp_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_pc_timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.last_pc_timestamp_us, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GimbalInfo & msg, bool use_flow_style = false)
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

}  // namespace vision_detector

namespace rosidl_generator_traits
{

[[deprecated("use vision_detector::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vision_detector::msg::GimbalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  vision_detector::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vision_detector::msg::to_yaml() instead")]]
inline std::string to_yaml(const vision_detector::msg::GimbalInfo & msg)
{
  return vision_detector::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vision_detector::msg::GimbalInfo>()
{
  return "vision_detector::msg::GimbalInfo";
}

template<>
inline const char * name<vision_detector::msg::GimbalInfo>()
{
  return "vision_detector/msg/GimbalInfo";
}

template<>
struct has_fixed_size<vision_detector::msg::GimbalInfo>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vision_detector::msg::GimbalInfo>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vision_detector::msg::GimbalInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__TRAITS_HPP_
