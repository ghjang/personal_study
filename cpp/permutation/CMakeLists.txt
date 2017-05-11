cmake_minimum_required(VERSION 3.0.0)
project(permutation_test VERSION 0.0.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES
        permutation_test.cpp
        main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
