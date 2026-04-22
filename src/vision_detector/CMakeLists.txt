cmake_minimum_required(VERSION 3.8)
project(vision_detector)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(camera_stream REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DroneDiff.msg"
  "msg/GimbalInfo.msg"
  DEPENDENCIES std_msgs
)


add_executable(node_vision_drone_detector
  src/node_vision_drone_detector.cpp
  src/target_detector.cpp
  src/ekf_tracker.cpp
)

target_include_directories(node_vision_drone_detector PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(node_vision_drone_detector
  ${OpenCV_LIBS}
)

ament_target_dependencies(node_vision_drone_detector
  rclcpp
  std_msgs
  OpenCV
  camera_stream
)
rosidl_target_interfaces(node_vision_drone_detector ${PROJECT_NAME} "rosidl_typesupport_cpp")
install(TARGETS
  node_vision_drone_detector
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()

