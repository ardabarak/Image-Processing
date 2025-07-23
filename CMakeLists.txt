cmake_minimum_required(VERSION 3.10.0)
project(cmkDNM VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED) #
include_directories(${OpenCV_INCLUDE_DIRS}) #

include(CTest)
enable_testing()

add_executable(cmkDNM main.cpp)
target_link_libraries(cmkDNM ${OpenCV_LIBS}) #