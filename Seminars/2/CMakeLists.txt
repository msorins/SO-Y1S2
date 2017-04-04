cmake_minimum_required(VERSION 3.6)
project(Seminar2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES library.c library.h)
add_library(Seminar2 ${SOURCE_FILES})