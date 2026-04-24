cmake_minimum_required(VERSION 3.10)

project(PathFinding_Learn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INC       "./include")
set(MAP_SYS   "./include/map_system")
set(PATH_FIND "./include/path_finding")
set(UTILS     "./include/utils")

include_directories(${INC})
include_directories(${MAP_SYS})
include_directories(${PATH_FIND})
include_directories(${UTILS})

set(MY_EXECUTABLE_NAME "main")
set(
  SOURCE_FILES
  # main
  "./main.cpp"

  # ./include/map_system/
  "${MAP_SYS}/grid_map.cpp"
  "${MAP_SYS}/grid_map_generator.cpp"

  # ./include/path_finding/
  "${PATH_FIND}/A_star.cpp"

  # ./include/utils/
  "${UTILS}/distance.cpp"
  "${UTILS}/timer.cpp"

  # ./include/
  "${INC}/get_grid_map.cpp"
  )
add_executable(${MY_EXECUTABLE_NAME} ${SOURCE_FILES})
