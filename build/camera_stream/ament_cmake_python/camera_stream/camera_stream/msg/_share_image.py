# generated from rosidl_generator_py/resource/_idl.py.em
# with input from camera_stream:msg/ShareImage.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ShareImage(type):
    """Metaclass of message 'ShareImage'."""

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
            module = import_type_support('camera_stream')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'camera_stream.msg.ShareImage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__share_image
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__share_image
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__share_image
            cls._TYPE_SUPPORT = module.type_support_msg__msg__share_image
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__share_image

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ShareImage(metaclass=Metaclass_ShareImage):
    """Message class 'ShareImage'."""

    __slots__ = [
        '_camera_select',
        '_shm_id',
        '_width',
        '_height',
        '_frame_id',
        '_enable',
        '_shm_size',
        '_timestamp_us',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'camera_select': 'uint32',
        'shm_id': 'uint32',
        'width': 'uint32',
        'height': 'uint32',
        'frame_id': 'uint32',
        'enable': 'boolean',
        'shm_size': 'uint32',
        'timestamp_us': 'uint64',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
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
        self.camera_select = kwargs.get('camera_select', int())
        self.shm_id = kwargs.get('shm_id', int())
        self.width = kwargs.get('width', int())
        self.height = kwargs.get('height', int())
        self.frame_id = kwargs.get('frame_id', int())
        self.enable = kwargs.get('enable', bool())
        self.shm_size = kwargs.get('shm_size', int())
        self.timestamp_us = kwargs.get('timestamp_us', int())

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
        if self.camera_select != other.camera_select:
            return False
        if self.shm_id != other.shm_id:
            return False
        if self.width != other.width:
            return False
        if self.height != other.height:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.enable != other.enable:
            return False
        if self.shm_size != other.shm_size:
            return False
        if self.timestamp_us != other.timestamp_us:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def camera_select(self):
        """Message field 'camera_select'."""
        return self._camera_select

    @camera_select.setter
    def camera_select(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'camera_select' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'camera_select' field must be an unsigned integer in [0, 4294967295]"
        self._camera_select = value

    @builtins.property
    def shm_id(self):
        """Message field 'shm_id'."""
        return self._shm_id

    @shm_id.setter
    def shm_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'shm_id' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'shm_id' field must be an unsigned integer in [0, 4294967295]"
        self._shm_id = value

    @builtins.property
    def width(self):
        """Message field 'width'."""
        return self._width

    @width.setter
    def width(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'width' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'width' field must be an unsigned integer in [0, 4294967295]"
        self._width = value

    @builtins.property
    def height(self):
        """Message field 'height'."""
        return self._height

    @height.setter
    def height(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'height' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'height' field must be an unsigned integer in [0, 4294967295]"
        self._height = value

    @builtins.property
    def frame_id(self):
        """Message field 'frame_id'."""
        return self._frame_id

    @frame_id.setter
    def frame_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'frame_id' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'frame_id' field must be an unsigned integer in [0, 4294967295]"
        self._frame_id = value

    @builtins.property
    def enable(self):
        """Message field 'enable'."""
        return self._enable

    @enable.setter
    def enable(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'enable' field must be of type 'bool'"
        self._enable = value

    @builtins.property
    def shm_size(self):
        """Message field 'shm_size'."""
        return self._shm_size

    @shm_size.setter
    def shm_size(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'shm_size' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'shm_size' field must be an unsigned integer in [0, 4294967295]"
        self._shm_size = value

    @builtins.property
    def timestamp_us(self):
        """Message field 'timestamp_us'."""
        return self._timestamp_us

    @timestamp_us.setter
    def timestamp_us(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'timestamp_us' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp_us' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp_us = value
