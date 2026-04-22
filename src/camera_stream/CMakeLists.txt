cmake_minimum_required(VERSION 3.8)
project(camera_stream)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 设置海康威视库路径
set(HIKVISION_LIB 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/64/libMvCameraControl.so
)

# 生成消息接口
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ShareImage.msg"
  DEPENDENCIES std_msgs
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# 创建发布方可执行文件
add_executable(camera_stream_publisher
  src/camera_stream_publisher.cpp
  src/HKCamera.cpp
)

# 创建接收方可执行文件
add_executable(camera_stream_receiver
  src/camera_stream_receiver.cpp
)

# 设置包含目录
target_include_directories(camera_stream_publisher PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_include_directories(camera_stream_receiver PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# 设置依赖
ament_target_dependencies(camera_stream_publisher
  rclcpp
  std_msgs
  OpenCV
)

ament_target_dependencies(camera_stream_receiver
  rclcpp
  std_msgs
  OpenCV
)

# 获取消息类型支持目标（修复弃用警告）
rosidl_get_typesupport_target(cpp_typesupport_target_publisher 
  "${PROJECT_NAME}" "rosidl_typesupport_cpp")
  
rosidl_get_typesupport_target(cpp_typesupport_target_receiver 
  "${PROJECT_NAME}" "rosidl_typesupport_cpp")

# 链接消息类型支持
target_link_libraries(camera_stream_publisher 
  "${cpp_typesupport_target_publisher}"
)

target_link_libraries(camera_stream_receiver 
  "${cpp_typesupport_target_receiver}"
)

# 链接海康威视库（仅发布方需要）
target_link_libraries(camera_stream_publisher
  ${HIKVISION_LIB}
  ${OpenCV_LIBS}
)

# 链接OpenCV库（接收方也需要）
target_link_libraries(camera_stream_receiver
  ${OpenCV_LIBS}
)

# 安装可执行文件
install(TARGETS
  camera_stream_publisher
  camera_stream_receiver
  DESTINATION lib/${PROJECT_NAME}
)

# 安装接口文件
install(
  DIRECTORY include/
  DESTINATION include/
)

# 安装库文件
install(
  FILES ${HIKVISION_LIB}
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()