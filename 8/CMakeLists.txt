cmake_minimum_required(VERSION 3.10)
project(main)

add_library(array array/array.c)
target_include_directories(array PUBLIC array)

add_library(inputHandler utils/inputHandler.c)
target_include_directories(inputHandler PUBLIC utils)

add_executable(main src/main.c)
target_link_libraries(main array inputHandler)

