#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to camera_stream__msg__ShareImage

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ShareImage::default())
  }
}

impl rosidl_runtime_rs::Message for ShareImage {
  type RmwMsg = super::msg::rmw::ShareImage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        camera_select: msg.camera_select,
        shm_id: msg.shm_id,
        width: msg.width,
        height: msg.height,
        frame_id: msg.frame_id,
        enable: msg.enable,
        shm_size: msg.shm_size,
        timestamp_us: msg.timestamp_us,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      camera_select: msg.camera_select,
      shm_id: msg.shm_id,
      width: msg.width,
      height: msg.height,
      frame_id: msg.frame_id,
      enable: msg.enable,
      shm_size: msg.shm_size,
      timestamp_us: msg.timestamp_us,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      camera_select: msg.camera_select,
      shm_id: msg.shm_id,
      width: msg.width,
      height: msg.height,
      frame_id: msg.frame_id,
      enable: msg.enable,
      shm_size: msg.shm_size,
      timestamp_us: msg.timestamp_us,
    }
  }
}


