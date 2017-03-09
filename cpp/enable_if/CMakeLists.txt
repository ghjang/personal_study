cmake_minimum_required(VERSION 3.3)
project(enable_if)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(enable_if ${SOURCE_FILES})