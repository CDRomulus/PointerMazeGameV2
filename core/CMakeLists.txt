cmake_minimum_required (VERSION 3.5)
project (pointerMazeGameV2)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")
add_executable (pointerMazeGameV2 ${source_files})
