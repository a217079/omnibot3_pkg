cmake_minimum_required(VERSION 2.8.3)
project(omnibot3_driver)

find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  std_msgs
  roscpp
)

catkin_package(
  CATKIN_DEPENDS std_msgs
)

# Build
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(drive_test_node src/drive_test.cpp)
target_link_libraries(drive_test_node ${catkin_LIBRARIES})

add_executable(gyro_test_node src/gyro_test.cpp)
target_link_libraries(gyro_test_node ${catkin_LIBRARIES})
