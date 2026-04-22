#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "vision_detector__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vision_detector__msg__DroneDiff() -> *const std::ffi::c_void;
}

#[link(name = "vision_detector__rosidl_generator_c")]
extern "C" {
    fn vision_detector__msg__DroneDiff__init(msg: *mut DroneDiff) -> bool;
    fn vision_detector__msg__DroneDiff__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DroneDiff>, size: usize) -> bool;
    fn vision_detector__msg__DroneDiff__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DroneDiff>);
    fn vision_detector__msg__DroneDiff__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DroneDiff>, out_seq: *mut rosidl_runtime_rs::Sequence<DroneDiff>) -> bool;
}

// Corresponds to vision_detector__msg__DroneDiff
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneDiff {

    // This member is not documented.
    #[allow(missing_docs)]
    pub target_yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub v_yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub v_pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pc_timestamp_us: u32,

}



impl Default for DroneDiff {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vision_detector__msg__DroneDiff__init(&mut msg as *mut _) {
        panic!("Call to vision_detector__msg__DroneDiff__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DroneDiff {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__DroneDiff__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__DroneDiff__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__DroneDiff__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DroneDiff {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DroneDiff where Self: Sized {
  const TYPE_NAME: &'static str = "vision_detector/msg/DroneDiff";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vision_detector__msg__DroneDiff() }
  }
}


#[link(name = "vision_detector__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vision_detector__msg__GimbalInfo() -> *const std::ffi::c_void;
}

#[link(name = "vision_detector__rosidl_generator_c")]
extern "C" {
    fn vision_detector__msg__GimbalInfo__init(msg: *mut GimbalInfo) -> bool;
    fn vision_detector__msg__GimbalInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GimbalInfo>, size: usize) -> bool;
    fn vision_detector__msg__GimbalInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GimbalInfo>);
    fn vision_detector__msg__GimbalInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GimbalInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<GimbalInfo>) -> bool;
}

// Corresponds to vision_detector__msg__GimbalInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GimbalInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub last_pc_timestamp_us: u32,

}



impl Default for GimbalInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vision_detector__msg__GimbalInfo__init(&mut msg as *mut _) {
        panic!("Call to vision_detector__msg__GimbalInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GimbalInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__GimbalInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__GimbalInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vision_detector__msg__GimbalInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GimbalInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GimbalInfo where Self: Sized {
  const TYPE_NAME: &'static str = "vision_detector/msg/GimbalInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vision_detector__msg__GimbalInfo() }
  }
}


