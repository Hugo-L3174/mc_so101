cmake_minimum_required(VERSION 3.22)

project(mc_so101 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(mc_rtc REQUIRED)
find_description_package(so101_description)

message("-- SO101_DESCRIPTION_PATH: ${SO101_DESCRIPTION_PATH}")
configure_file(src/config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/config.h")

add_robot(so101 src/so101.cpp src/so101.h)
target_include_directories(so101 PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
