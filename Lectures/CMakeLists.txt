cmake_minimum_required(VERSION 3.6)
project(Lectures)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Lecture7Ex/main.c)
add_executable(Lectures ${SOURCE_FILES})