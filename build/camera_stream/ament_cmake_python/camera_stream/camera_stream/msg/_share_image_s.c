// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from camera_stream:msg/ShareImage.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "camera_stream/msg/detail/share_image__struct.h"
#include "camera_stream/msg/detail/share_image__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool camera_stream__msg__share_image__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[42];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("camera_stream.msg._share_image.ShareImage", full_classname_dest, 41) == 0);
  }
  camera_stream__msg__ShareImage * ros_message = _ros_message;
  {  // camera_select
    PyObject * field = PyObject_GetAttrString(_pymsg, "camera_select");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->camera_select = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // shm_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "shm_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->shm_id = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // width
    PyObject * field = PyObject_GetAttrString(_pymsg, "width");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->width = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // height
    PyObject * field = PyObject_GetAttrString(_pymsg, "height");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->height = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // frame_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "frame_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->frame_id = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // enable
    PyObject * field = PyObject_GetAttrString(_pymsg, "enable");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->enable = (Py_True == field);
    Py_DECREF(field);
  }
  {  // shm_size
    PyObject * field = PyObject_GetAttrString(_pymsg, "shm_size");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->shm_size = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timestamp_us
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp_us");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp_us = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * camera_stream__msg__share_image__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ShareImage */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("camera_stream.msg._share_image");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ShareImage");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  camera_stream__msg__ShareImage * ros_message = (camera_stream__msg__ShareImage *)raw_ros_message;
  {  // camera_select
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->camera_select);
    {
      int rc = PyObject_SetAttrString(_pymessage, "camera_select", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // shm_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->shm_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "shm_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // width
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->width);
    {
      int rc = PyObject_SetAttrString(_pymessage, "width", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // height
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->height);
    {
      int rc = PyObject_SetAttrString(_pymessage, "height", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // frame_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->frame_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "frame_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // enable
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->enable ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enable", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // shm_size
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->shm_size);
    {
      int rc = PyObject_SetAttrString(_pymessage, "shm_size", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestamp_us
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timestamp_us);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp_us", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
