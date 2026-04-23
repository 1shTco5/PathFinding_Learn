cmake_minimum_required(VERSION 3.10)

project(MyProject)

include_directories("./include/")

set(MY_EXECUTABLE_NAME "main")
set(
  SOURCE_FILES
  "./main.cpp"
  "./include/map_system.cpp"
  "./include/distance.cpp"
  "./include/A_star.cpp"
)
add_executable(${MY_EXECUTABLE_NAME} ${SOURCE_FILES})
