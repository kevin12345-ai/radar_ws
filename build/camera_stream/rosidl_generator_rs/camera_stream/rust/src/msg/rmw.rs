#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "camera_stream__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__camera_stream__msg__ShareImage() -> *const std::ffi::c_void;
}

#[link(name = "camera_stream__rosidl_generator_c")]
extern "C" {
    fn camera_stream__msg__ShareImage__init(msg: *mut ShareImage) -> bool;
    fn camera_stream__msg__ShareImage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ShareImage>, size: usize) -> bool;
    fn camera_stream__msg__ShareImage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ShareImage>);
    fn camera_stream__msg__ShareImage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ShareImage>, out_seq: *mut rosidl_runtime_rs::Sequence<ShareImage>) -> bool;
}

// Corresponds to camera_stream__msg__ShareImage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ShareImage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub camera_select: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub shm_id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub width: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub height: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enable: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub shm_size: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub timestamp_us: u64,

}



impl Default for ShareImage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !camera_stream__msg__ShareImage__init(&mut msg as *mut _) {
        panic!("Call to camera_stream__msg__ShareImage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ShareImage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { camera_stream__msg__ShareImage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { camera_stream__msg__ShareImage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { camera_stream__msg__ShareImage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ShareImage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ShareImage where Self: Sized {
  const TYPE_NAME: &'static str = "camera_stream/msg/ShareImage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__camera_stream__msg__ShareImage() }
  }
}


