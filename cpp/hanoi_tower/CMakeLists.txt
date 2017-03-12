cmake_minimum_required(VERSION 3.3)
project(hanoi_tower_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(hanoi_tower_test ${SOURCE_FILES})
