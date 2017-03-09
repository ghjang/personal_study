cmake_minimum_required(VERSION 3.3)
project(integral_constant)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(GSLDIR ../../../GSL/include)
include_directories(${GSLDIR})

set(SOURCE_FILES main.cpp)

add_executable(
        integral_constant
        ${SOURCE_FILES}
)
