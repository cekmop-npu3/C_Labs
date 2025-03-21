cmake_minimum_required(VERSION 3.10)
project(main)

add_executable(main src/main.c src/utils.c handlers/inputHandler.c geometry/geometry.c geometry/array.c)

target_include_directories(main PRIVATE geometry handlers)
