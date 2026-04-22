// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vision_detector:msg/GimbalInfo.idl
// generated code does not contain a copyright notice
#include "vision_detector/msg/detail/gimbal_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vision_detector__msg__GimbalInfo__init(vision_detector__msg__GimbalInfo * msg)
{
  if (!msg) {
    return false;
  }
  // current_yaw
  // current_pitch
  // last_pc_timestamp_us
  return true;
}

void
vision_detector__msg__GimbalInfo__fini(vision_detector__msg__GimbalInfo * msg)
{
  if (!msg) {
    return;
  }
  // current_yaw
  // current_pitch
  // last_pc_timestamp_us
}

bool
vision_detector__msg__GimbalInfo__are_equal(const vision_detector__msg__GimbalInfo * lhs, const vision_detector__msg__GimbalInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // current_yaw
  if (lhs->current_yaw != rhs->current_yaw) {
    return false;
  }
  // current_pitch
  if (lhs->current_pitch != rhs->current_pitch) {
    return false;
  }
  // last_pc_timestamp_us
  if (lhs->last_pc_timestamp_us != rhs->last_pc_timestamp_us) {
    return false;
  }
  return true;
}

bool
vision_detector__msg__GimbalInfo__copy(
  const vision_detector__msg__GimbalInfo * input,
  vision_detector__msg__GimbalInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // current_yaw
  output->current_yaw = input->current_yaw;
  // current_pitch
  output->current_pitch = input->current_pitch;
  // last_pc_timestamp_us
  output->last_pc_timestamp_us = input->last_pc_timestamp_us;
  return true;
}

vision_detector__msg__GimbalInfo *
vision_detector__msg__GimbalInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_detector__msg__GimbalInfo * msg = (vision_detector__msg__GimbalInfo *)allocator.allocate(sizeof(vision_detector__msg__GimbalInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vision_detector__msg__GimbalInfo));
  bool success = vision_detector__msg__GimbalInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vision_detector__msg__GimbalInfo__destroy(vision_detector__msg__GimbalInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vision_detector__msg__GimbalInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vision_detector__msg__GimbalInfo__Sequence__init(vision_detector__msg__GimbalInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_detector__msg__GimbalInfo * data = NULL;

  if (size) {
    data = (vision_detector__msg__GimbalInfo *)allocator.zero_allocate(size, sizeof(vision_detector__msg__GimbalInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vision_detector__msg__GimbalInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vision_detector__msg__GimbalInfo__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vision_detector__msg__GimbalInfo__Sequence__fini(vision_detector__msg__GimbalInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vision_detector__msg__GimbalInfo__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vision_detector__msg__GimbalInfo__Sequence *
vision_detector__msg__GimbalInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_detector__msg__GimbalInfo__Sequence * array = (vision_detector__msg__GimbalInfo__Sequence *)allocator.allocate(sizeof(vision_detector__msg__GimbalInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vision_detector__msg__GimbalInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vision_detector__msg__GimbalInfo__Sequence__destroy(vision_detector__msg__GimbalInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vision_detector__msg__GimbalInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vision_detector__msg__GimbalInfo__Sequence__are_equal(const vision_detector__msg__GimbalInfo__Sequence * lhs, const vision_detector__msg__GimbalInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vision_detector__msg__GimbalInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vision_detector__msg__GimbalInfo__Sequence__copy(
  const vision_detector__msg__GimbalInfo__Sequence * input,
  vision_detector__msg__GimbalInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vision_detector__msg__GimbalInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vision_detector__msg__GimbalInfo * data =
      (vision_detector__msg__GimbalInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vision_detector__msg__GimbalInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vision_detector__msg__GimbalInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vision_detector__msg__GimbalInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
