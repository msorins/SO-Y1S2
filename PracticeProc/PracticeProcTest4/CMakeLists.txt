cmake_minimum_required(VERSION 3.6)
project(Test)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(Test ${SOURCE_FILES})