cmake_minimum_required(VERSION 3.3)
project(MyConsoleGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp includes/colorLinux.cpp)
add_executable(MyConsoleGame ${SOURCE_FILES})