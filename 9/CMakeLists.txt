cmake_minimum_required(VERSION 3.10)
project(main)

add_executable(1 src/1.c utils/fileHandler.c)
target_include_directories(1 PRIVATE utils)

add_executable(2 src/2.c utils/fileHandler.c)
target_include_directories(2 PRIVATE utils)

add_executable(3 src/3.c utils/fileHandler.c)
target_include_directories(3 PRIVATE utils)

add_executable(main src/main.c utils/fileHandler.c)
target_include_directories(main PRIVATE utils)
