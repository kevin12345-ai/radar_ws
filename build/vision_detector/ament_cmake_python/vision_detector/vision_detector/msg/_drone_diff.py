# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vision_detector:msg/DroneDiff.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DroneDiff(type):
    """Metaclass of message 'DroneDiff'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vision_detector')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vision_detector.msg.DroneDiff')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__drone_diff
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__drone_diff
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__drone_diff
            cls._TYPE_SUPPORT = module.type_support_msg__msg__drone_diff
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__drone_diff

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DroneDiff(metaclass=Metaclass_DroneDiff):
    """Message class 'DroneDiff'."""

    __slots__ = [
        '_target_yaw',
        '_target_pitch',
        '_v_yaw',
        '_v_pitch',
        '_pc_timestamp_us',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'target_yaw': 'float',
        'target_pitch': 'float',
        'v_yaw': 'float',
        'v_pitch': 'float',
        'pc_timestamp_us': 'uint32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.target_yaw = kwargs.get('target_yaw', float())
        self.target_pitch = kwargs.get('target_pitch', float())
        self.v_yaw = kwargs.get('v_yaw', float())
        self.v_pitch = kwargs.get('v_pitch', float())
        self.pc_timestamp_us = kwargs.get('pc_timestamp_us', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.target_yaw != other.target_yaw:
            return False
        if self.target_pitch != other.target_pitch:
            return False
        if self.v_yaw != other.v_yaw:
            return False
        if self.v_pitch != other.v_pitch:
            return False
        if self.pc_timestamp_us != other.pc_timestamp_us:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def target_yaw(self):
        """Message field 'target_yaw'."""
        return self._target_yaw

    @target_yaw.setter
    def target_yaw(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'target_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_yaw = value

    @builtins.property
    def target_pitch(self):
        """Message field 'target_pitch'."""
        return self._target_pitch

    @target_pitch.setter
    def target_pitch(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'target_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_pitch = value

    @builtins.property
    def v_yaw(self):
        """Message field 'v_yaw'."""
        return self._v_yaw

    @v_yaw.setter
    def v_yaw(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'v_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'v_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._v_yaw = value

    @builtins.property
    def v_pitch(self):
        """Message field 'v_pitch'."""
        return self._v_pitch

    @v_pitch.setter
    def v_pitch(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'v_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'v_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._v_pitch = value

    @builtins.property
    def pc_timestamp_us(self):
        """Message field 'pc_timestamp_us'."""
        return self._pc_timestamp_us

    @pc_timestamp_us.setter
    def pc_timestamp_us(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'pc_timestamp_us' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'pc_timestamp_us' field must be an unsigned integer in [0, 4294967295]"
        self._pc_timestamp_us = value
