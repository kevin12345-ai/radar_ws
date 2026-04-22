// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vision_detector:msg/DroneDiff.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/drone_diff.hpp"


#ifndef VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__TRAITS_HPP_
#define VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vision_detector/msg/detail/drone_diff__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vision_detector
{

namespace msg
{

inline void to_flow_style_yaml(
  const DroneDiff & msg,
  std::ostream & out)
{
  out << "{";
  // member: target_yaw
  {
    out << "target_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.target_yaw, out);
    out << ", ";
  }

  // member: target_pitch
  {
    out << "target_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.target_pitch, out);
    out << ", ";
  }

  // member: v_yaw
  {
    out << "v_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.v_yaw, out);
    out << ", ";
  }

  // member: v_pitch
  {
    out << "v_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.v_pitch, out);
    out << ", ";
  }

  // member: pc_timestamp_us
  {
    out << "pc_timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.pc_timestamp_us, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DroneDiff & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.target_yaw, out);
    out << "\n";
  }

  // member: target_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.target_pitch, out);
    out << "\n";
  }

  // member: v_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.v_yaw, out);
    out << "\n";
  }

  // member: v_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.v_pitch, out);
    out << "\n";
  }

  // member: pc_timestamp_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pc_timestamp_us: ";
    rosidl_generator_traits::value_to_yaml(msg.pc_timestamp_us, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DroneDiff & msg, bool use_flow_style = false)
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
  const vision_detector::msg::DroneDiff & msg,
  std::ostream & out, size_t indentation = 0)
{
  vision_detector::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vision_detector::msg::to_yaml() instead")]]
inline std::string to_yaml(const vision_detector::msg::DroneDiff & msg)
{
  return vision_detector::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vision_detector::msg::DroneDiff>()
{
  return "vision_detector::msg::DroneDiff";
}

template<>
inline const char * name<vision_detector::msg::DroneDiff>()
{
  return "vision_detector/msg/DroneDiff";
}

template<>
struct has_fixed_size<vision_detector::msg::DroneDiff>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vision_detector::msg::DroneDiff>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vision_detector::msg::DroneDiff>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VISION_DETECTOR__MSG__DETAIL__DRONE_DIFF__TRAITS_HPP_
