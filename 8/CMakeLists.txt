cmake_minimum_required(VERSION 3.10)
project(main)

add_executable(test src/main.c array/array.c utils/inputHandler.c)

target_include_directories(test PRIVATE array utils)

