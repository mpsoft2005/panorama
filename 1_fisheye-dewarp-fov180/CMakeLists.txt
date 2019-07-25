cmake_minimum_required (VERSION 2.6)

add_definitions(-D_USE_MATH_DEFINES)

project (fisheye-dewarp)

add_executable(dewarp-fov180 src/fisheye-dewarp-fov180.cpp)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( dewarp-fov180 ${OpenCV_LIBS} )
