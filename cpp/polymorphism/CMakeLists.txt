cmake_minimum_required(VERSION 3.3)
project(polymorphism)

set(BOOST_ROOT "../../../boost_1_63_0")
find_package(Boost 1.63.0)
if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
else()
    message(FATAL_ERROR "Could not find boost!")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        dynamic_polymorphism.cpp
        dynamic_polymorphism.h
        static_polymorphism.cpp
        static_polymorphism.h
        dynamic_polymorphism.h)

add_executable(polymorphism ${SOURCE_FILES})
