cmake_minimum_required(VERSION 3.3)
project(ratio_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(ratio_test ${SOURCE_FILES})