cmake_minimum_required(VERSION 2.8.3)
project(keyboard)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sound_play
  base_controller 
  message_generation
)



include_directories(
  ${catkin_INCLUDE_DIRS}
)


catkin_package(CATKIN_DEPENDS)


add_executable(keyboard src/keyboard.cpp)
target_link_libraries(keyboard ${catkin_LIBRARIES})

