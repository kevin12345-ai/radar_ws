// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice
#include "camera_stream/msg/detail/share_image__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
camera_stream__msg__ShareImage__init(camera_stream__msg__ShareImage * msg)
{
  if (!msg) {
    return false;
  }
  // camera_select
  // shm_id
  // width
  // height
  // frame_id
  // enable
  // shm_size
  // timestamp_us
  return true;
}

void
camera_stream__msg__ShareImage__fini(camera_stream__msg__ShareImage * msg)
{
  if (!msg) {
    return;
  }
  // camera_select
  // shm_id
  // width
  // height
  // frame_id
  // enable
  // shm_size
  // timestamp_us
}

bool
camera_stream__msg__ShareImage__are_equal(const camera_stream__msg__ShareImage * lhs, const camera_stream__msg__ShareImage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // camera_select
  if (lhs->camera_select != rhs->camera_select) {
    return false;
  }
  // shm_id
  if (lhs->shm_id != rhs->shm_id) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // frame_id
  if (lhs->frame_id != rhs->frame_id) {
    return false;
  }
  // enable
  if (lhs->enable != rhs->enable) {
    return false;
  }
  // shm_size
  if (lhs->shm_size != rhs->shm_size) {
    return false;
  }
  // timestamp_us
  if (lhs->timestamp_us != rhs->timestamp_us) {
    return false;
  }
  return true;
}

bool
camera_stream__msg__ShareImage__copy(
  const camera_stream__msg__ShareImage * input,
  camera_stream__msg__ShareImage * output)
{
  if (!input || !output) {
    return false;
  }
  // camera_select
  output->camera_select = input->camera_select;
  // shm_id
  output->shm_id = input->shm_id;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // frame_id
  output->frame_id = input->frame_id;
  // enable
  output->enable = input->enable;
  // shm_size
  output->shm_size = input->shm_size;
  // timestamp_us
  output->timestamp_us = input->timestamp_us;
  return true;
}

camera_stream__msg__ShareImage *
camera_stream__msg__ShareImage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_stream__msg__ShareImage * msg = (camera_stream__msg__ShareImage *)allocator.allocate(sizeof(camera_stream__msg__ShareImage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(camera_stream__msg__ShareImage));
  bool success = camera_stream__msg__ShareImage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
camera_stream__msg__ShareImage__destroy(camera_stream__msg__ShareImage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    camera_stream__msg__ShareImage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
camera_stream__msg__ShareImage__Sequence__init(camera_stream__msg__ShareImage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_stream__msg__ShareImage * data = NULL;

  if (size) {
    data = (camera_stream__msg__ShareImage *)allocator.zero_allocate(size, sizeof(camera_stream__msg__ShareImage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = camera_stream__msg__ShareImage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        camera_stream__msg__ShareImage__fini(&data[i - 1]);
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
camera_stream__msg__ShareImage__Sequence__fini(camera_stream__msg__ShareImage__Sequence * array)
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
      camera_stream__msg__ShareImage__fini(&array->data[i]);
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

camera_stream__msg__ShareImage__Sequence *
camera_stream__msg__ShareImage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_stream__msg__ShareImage__Sequence * array = (camera_stream__msg__ShareImage__Sequence *)allocator.allocate(sizeof(camera_stream__msg__ShareImage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = camera_stream__msg__ShareImage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
camera_stream__msg__ShareImage__Sequence__destroy(camera_stream__msg__ShareImage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    camera_stream__msg__ShareImage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
camera_stream__msg__ShareImage__Sequence__are_equal(const camera_stream__msg__ShareImage__Sequence * lhs, const camera_stream__msg__ShareImage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!camera_stream__msg__ShareImage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
camera_stream__msg__ShareImage__Sequence__copy(
  const camera_stream__msg__ShareImage__Sequence * input,
  camera_stream__msg__ShareImage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(camera_stream__msg__ShareImage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    camera_stream__msg__ShareImage * data =
      (camera_stream__msg__ShareImage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!camera_stream__msg__ShareImage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          camera_stream__msg__ShareImage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!camera_stream__msg__ShareImage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
