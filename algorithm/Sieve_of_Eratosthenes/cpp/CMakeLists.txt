cmake_minimum_required(VERSION 3.5)
project(cpp)

set(CMAKE_CXX_STANDARD 23)

find_package(Catch2 3 REQUIRED)

add_executable(
        cpp
        main.cpp
        sieve_of_eratosthenes.h
        get_impl.cpp
        01_simple_get.cpp
)

target_link_libraries(cpp PRIVATE Catch2::Catch2WithMain)
