cmake_minimum_required(VERSION 3.0.2)
project(robot_to_server_comm)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs nav_msgs)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  include 
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(robot_to_server_node src/robot_to_server_node.cpp 
				     include/robot_to_server_comm/robot_to_server_comm_node.h)
target_link_libraries(robot_to_server_node ${catkin_LIBRARIES})