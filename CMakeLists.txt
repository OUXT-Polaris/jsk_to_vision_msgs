cmake_minimum_required(VERSION 2.8.3)
project(jsk_to_vision_msgs)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  jsk_recognition_msgs
  roscpp
  vision_msgs
)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES jsk_to_vision_msgs
  CATKIN_DEPENDS jsk_recognition_msgs roscpp vision_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(jsk_to_vision_msgs_node src/jsk_to_vision_msgs_node.cpp src/jsk_to_vision_msgs.cpp)
target_link_libraries(jsk_to_vision_msgs_node ${catkin_LIBRARIES})
add_dependencies(jsk_to_vision_msgs_node ${catkin_EXPORTED_TARGETS})