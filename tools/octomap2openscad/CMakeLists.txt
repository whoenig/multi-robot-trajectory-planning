cmake_minimum_required(VERSION 2.8)

project(octomap2openscad)

# set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(Boost 1.58 COMPONENTS program_options REQUIRED)
# FIND_PACKAGE( Eigen3 )
FIND_PACKAGE(yaml-cpp REQUIRED)
FIND_PACKAGE(octomap REQUIRED)
# set (GUROBI_DIR /home/whoenig/sw/gurobi701/linux64)


# Additional include folders
include_directories(
  ${OCTOMAP_INCLUDE_DIRS}
  # ../libCommon/include
  # ../libAnonMapf/include
  # ${EIGEN3_INCLUDE_DIR}
)

add_executable(octomap2openscad
  src/main.cpp
)

target_link_libraries(octomap2openscad
  ${Boost_LIBRARIES}
  ${YAML_CPP_LIBRARIES}
  ${OCTOMAP_LIBRARIES}
  # libCommon
  # libAnonMapf
  # ${GUROBI_DIR}/lib/libgurobi_g++5.2.a
  # ${GUROBI_DIR}/lib/libgurobi70.so
)

target_compile_options(octomap2openscad PUBLIC -std=c++11 -Wall)
