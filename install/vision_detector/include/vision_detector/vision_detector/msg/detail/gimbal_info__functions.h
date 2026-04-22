// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vision_detector/msg/gimbal_info.h"


#ifndef VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__FUNCTIONS_H_
#define VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "vision_detector/msg/rosidl_generator_c__visibility_control.h"

#include "vision_detector/msg/detail/gimbal_info__struct.h"

/// Initialize msg/GimbalInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vision_detector__msg__GimbalInfo
 * )) before or use
 * vision_detector__msg__GimbalInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__init(vision_detector__msg__GimbalInfo * msg);

/// Finalize msg/GimbalInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
void
vision_detector__msg__GimbalInfo__fini(vision_detector__msg__GimbalInfo * msg);

/// Create msg/GimbalInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vision_detector__msg__GimbalInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
vision_detector__msg__GimbalInfo *
vision_detector__msg__GimbalInfo__create(void);

/// Destroy msg/GimbalInfo message.
/**
 * It calls
 * vision_detector__msg__GimbalInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
void
vision_detector__msg__GimbalInfo__destroy(vision_detector__msg__GimbalInfo * msg);

/// Check for msg/GimbalInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__are_equal(const vision_detector__msg__GimbalInfo * lhs, const vision_detector__msg__GimbalInfo * rhs);

/// Copy a msg/GimbalInfo message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__copy(
  const vision_detector__msg__GimbalInfo * input,
  vision_detector__msg__GimbalInfo * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_type_hash_t *
vision_detector__msg__GimbalInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_runtime_c__type_description__TypeDescription *
vision_detector__msg__GimbalInfo__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_runtime_c__type_description__TypeSource *
vision_detector__msg__GimbalInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
const rosidl_runtime_c__type_description__TypeSource__Sequence *
vision_detector__msg__GimbalInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/GimbalInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * vision_detector__msg__GimbalInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__Sequence__init(vision_detector__msg__GimbalInfo__Sequence * array, size_t size);

/// Finalize array of msg/GimbalInfo messages.
/**
 * It calls
 * vision_detector__msg__GimbalInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
void
vision_detector__msg__GimbalInfo__Sequence__fini(vision_detector__msg__GimbalInfo__Sequence * array);

/// Create array of msg/GimbalInfo messages.
/**
 * It allocates the memory for the array and calls
 * vision_detector__msg__GimbalInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
vision_detector__msg__GimbalInfo__Sequence *
vision_detector__msg__GimbalInfo__Sequence__create(size_t size);

/// Destroy array of msg/GimbalInfo messages.
/**
 * It calls
 * vision_detector__msg__GimbalInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
void
vision_detector__msg__GimbalInfo__Sequence__destroy(vision_detector__msg__GimbalInfo__Sequence * array);

/// Check for msg/GimbalInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__Sequence__are_equal(const vision_detector__msg__GimbalInfo__Sequence * lhs, const vision_detector__msg__GimbalInfo__Sequence * rhs);

/// Copy an array of msg/GimbalInfo messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_detector
bool
vision_detector__msg__GimbalInfo__Sequence__copy(
  const vision_detector__msg__GimbalInfo__Sequence * input,
  vision_detector__msg__GimbalInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VISION_DETECTOR__MSG__DETAIL__GIMBAL_INFO__FUNCTIONS_H_
