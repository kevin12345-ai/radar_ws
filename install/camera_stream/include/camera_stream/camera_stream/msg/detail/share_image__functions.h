// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "camera_stream/msg/share_image.h"


#ifndef CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__FUNCTIONS_H_
#define CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__FUNCTIONS_H_

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
#include "camera_stream/msg/rosidl_generator_c__visibility_control.h"

#include "camera_stream/msg/detail/share_image__struct.h"

/// Initialize msg/ShareImage message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * camera_stream__msg__ShareImage
 * )) before or use
 * camera_stream__msg__ShareImage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__init(camera_stream__msg__ShareImage * msg);

/// Finalize msg/ShareImage message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
void
camera_stream__msg__ShareImage__fini(camera_stream__msg__ShareImage * msg);

/// Create msg/ShareImage message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * camera_stream__msg__ShareImage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
camera_stream__msg__ShareImage *
camera_stream__msg__ShareImage__create(void);

/// Destroy msg/ShareImage message.
/**
 * It calls
 * camera_stream__msg__ShareImage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
void
camera_stream__msg__ShareImage__destroy(camera_stream__msg__ShareImage * msg);

/// Check for msg/ShareImage message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__are_equal(const camera_stream__msg__ShareImage * lhs, const camera_stream__msg__ShareImage * rhs);

/// Copy a msg/ShareImage message.
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
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__copy(
  const camera_stream__msg__ShareImage * input,
  camera_stream__msg__ShareImage * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
const rosidl_type_hash_t *
camera_stream__msg__ShareImage__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
const rosidl_runtime_c__type_description__TypeDescription *
camera_stream__msg__ShareImage__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
const rosidl_runtime_c__type_description__TypeSource *
camera_stream__msg__ShareImage__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
const rosidl_runtime_c__type_description__TypeSource__Sequence *
camera_stream__msg__ShareImage__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/ShareImage messages.
/**
 * It allocates the memory for the number of elements and calls
 * camera_stream__msg__ShareImage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__Sequence__init(camera_stream__msg__ShareImage__Sequence * array, size_t size);

/// Finalize array of msg/ShareImage messages.
/**
 * It calls
 * camera_stream__msg__ShareImage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
void
camera_stream__msg__ShareImage__Sequence__fini(camera_stream__msg__ShareImage__Sequence * array);

/// Create array of msg/ShareImage messages.
/**
 * It allocates the memory for the array and calls
 * camera_stream__msg__ShareImage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
camera_stream__msg__ShareImage__Sequence *
camera_stream__msg__ShareImage__Sequence__create(size_t size);

/// Destroy array of msg/ShareImage messages.
/**
 * It calls
 * camera_stream__msg__ShareImage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
void
camera_stream__msg__ShareImage__Sequence__destroy(camera_stream__msg__ShareImage__Sequence * array);

/// Check for msg/ShareImage message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__Sequence__are_equal(const camera_stream__msg__ShareImage__Sequence * lhs, const camera_stream__msg__ShareImage__Sequence * rhs);

/// Copy an array of msg/ShareImage messages.
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
ROSIDL_GENERATOR_C_PUBLIC_camera_stream
bool
camera_stream__msg__ShareImage__Sequence__copy(
  const camera_stream__msg__ShareImage__Sequence * input,
  camera_stream__msg__ShareImage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CAMERA_STREAM__MSG__DETAIL__SHARE_IMAGE__FUNCTIONS_H_
