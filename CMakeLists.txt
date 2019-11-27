cmake_minimum_required(VERSION 2.8.3)

# Enable C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpic")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

add_subdirectory(libMultiRobotPlanning)

add_subdirectory(tools/map2octomap)
add_subdirectory(tools/octomap2openscad)
add_subdirectory(tools/octomapStats)
