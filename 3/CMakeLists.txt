cmake_minimum_required(VERSION 3.10)

project(main)

add_library(lib utils/inputHandlers.c)

add_executable(1 1.c)
target_link_libraries(1 lib)

add_executable(2 2.c)
target_link_libraries(2 lib)

add_executable(3 3.c)
target_link_libraries(3 lib)