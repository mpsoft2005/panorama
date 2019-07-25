cmake_minimum_required (VERSION 2.6)

add_definitions(-D_USE_MATH_DEFINES)

project (fisheye-dewarp)

add_executable(dewarp-fov220 src/fisheye-dewarp-fov220.cpp)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( dewarp-fov220 ${OpenCV_LIBS} )
