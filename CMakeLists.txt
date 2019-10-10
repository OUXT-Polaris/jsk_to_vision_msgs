cmake_minimum_required(VERSION 2.8.3)
project(jsk_to_vision_msgs)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  jsk_recognition_msgs
  roscpp
  vision_msgs
  pluginlib
  nodelet
  vision_info_server
  message_filters
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES jsk_to_vision_msgs
  CATKIN_DEPENDS jsk_recognition_msgs roscpp vision_msgs message_filters
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(jsk_to_vision_msgs src/jsk_to_vision_msgs)
target_link_libraries(jsk_to_vision_msgs ${catkin_LIBRARIES})
class_loader_hide_library_symbols(jsk_to_vision_msgs)
add_dependencies(jsk_to_vision_msgs ${catkin_EXPORTED_TARGETS})

add_executable(jsk_to_vision_msgs_node src/jsk_to_vision_msgs_node.cpp)
target_link_libraries(jsk_to_vision_msgs_node ${catkin_LIBRARIES})
add_dependencies(jsk_to_vision_msgs_node ${catkin_EXPORTED_TARGETS})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(
  TARGETS jsk_to_vision_msgs jsk_to_vision_msgs_node
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

foreach(dir launch)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)