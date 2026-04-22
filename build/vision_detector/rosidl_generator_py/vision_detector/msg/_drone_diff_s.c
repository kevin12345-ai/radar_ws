// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vision_detector:msg/DroneDiff.idl
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
#include "vision_detector/msg/detail/drone_diff__struct.h"
#include "vision_detector/msg/detail/drone_diff__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vision_detector__msg__drone_diff__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("vision_detector.msg._drone_diff.DroneDiff", full_classname_dest, 41) == 0);
  }
  vision_detector__msg__DroneDiff * ros_message = _ros_message;
  {  // target_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "target_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->target_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // target_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "target_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->target_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // v_yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "v_yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->v_yaw = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // v_pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "v_pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->v_pitch = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pc_timestamp_us
    PyObject * field = PyObject_GetAttrString(_pymsg, "pc_timestamp_us");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pc_timestamp_us = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vision_detector__msg__drone_diff__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DroneDiff */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vision_detector.msg._drone_diff");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DroneDiff");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vision_detector__msg__DroneDiff * ros_message = (vision_detector__msg__DroneDiff *)raw_ros_message;
  {  // target_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->target_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "target_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // target_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->target_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "target_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // v_yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->v_yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "v_yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // v_pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->v_pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "v_pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pc_timestamp_us
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->pc_timestamp_us);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pc_timestamp_us", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
