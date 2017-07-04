#[[
    Steps to build a CMake project:
        1. Make a minimum CMakeList.txt project file.
        2. Open a command line and move to the directory where you made the CMakeList.txt file.
        3. Make a sub-directory like 'build' not to make CMake-related files in the current directory.
        4. Move to the sub-directory where you made at the step-3.
        5. Run the cmake command:
            ex.> cmake ..
                    ; This will create CMake-related files in the current directory by using the ../CMakeList.txt.
                 cmake .. -DCMAKE_BUILD_TYPE=Debug
                    ; You can define some CMake variables by using the '-D' option.
        6. Run the 'make' command.
        7. If the project is for an executable, then you can find your executable in the current directory.
        8. You can use a command like following to remove all the CMake-related files in the current directory:
            ex.> rm -rf ./*
                    ; NOTE: Use this with caution.
]]

cmake_minimum_required(VERSION 3.0.0)
project(catch_test VERSION 0.0.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")


set(SOURCE_FILES
        test_case.cpp
        main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})