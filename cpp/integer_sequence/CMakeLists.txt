cmake_minimum_required(VERSION 3.3)
project(integer_sequence_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(integer_sequence_test ${SOURCE_FILES})
