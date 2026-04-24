cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(MyProject)

include_directories("./include/")
include_directories("./include/path_finding")

set(MY_EXECUTABLE_NAME "main")
set(
  SOURCE_FILES
  "./main.cpp"
  "./include/map_system.cpp"
  "./include/distance.cpp"
  "./include/path_finding/A_star.cpp"
)
add_executable(${MY_EXECUTABLE_NAME} ${SOURCE_FILES})
