cmake_minimum_required(VERSION 3.5)
project(tuple_cat_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES main.cpp)
add_executable(tuple_cat_test ${SOURCE_FILES})