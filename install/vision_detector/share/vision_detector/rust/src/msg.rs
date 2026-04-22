#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to vision_detector__msg__DroneDiff

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DroneDiff::default())
  }
}

impl rosidl_runtime_rs::Message for DroneDiff {
  type RmwMsg = super::msg::rmw::DroneDiff;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        target_yaw: msg.target_yaw,
        target_pitch: msg.target_pitch,
        v_yaw: msg.v_yaw,
        v_pitch: msg.v_pitch,
        pc_timestamp_us: msg.pc_timestamp_us,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      target_yaw: msg.target_yaw,
      target_pitch: msg.target_pitch,
      v_yaw: msg.v_yaw,
      v_pitch: msg.v_pitch,
      pc_timestamp_us: msg.pc_timestamp_us,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      target_yaw: msg.target_yaw,
      target_pitch: msg.target_pitch,
      v_yaw: msg.v_yaw,
      v_pitch: msg.v_pitch,
      pc_timestamp_us: msg.pc_timestamp_us,
    }
  }
}


// Corresponds to vision_detector__msg__GimbalInfo

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GimbalInfo::default())
  }
}

impl rosidl_runtime_rs::Message for GimbalInfo {
  type RmwMsg = super::msg::rmw::GimbalInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        current_yaw: msg.current_yaw,
        current_pitch: msg.current_pitch,
        last_pc_timestamp_us: msg.last_pc_timestamp_us,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      current_yaw: msg.current_yaw,
      current_pitch: msg.current_pitch,
      last_pc_timestamp_us: msg.last_pc_timestamp_us,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      current_yaw: msg.current_yaw,
      current_pitch: msg.current_pitch,
      last_pc_timestamp_us: msg.last_pc_timestamp_us,
    }
  }
}


