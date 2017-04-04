cmake_minimum_required(VERSION 3.6)
project(1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES 1.c 2.cpp 2.c 3.c)
add_executable(1 ${SOURCE_FILES})