cmake_minimum_required(VERSION 3.10)
project(main)

add_executable(1 src/1.c utils/inputHandler.c utils/fileHandler.c)
target_include_directories(1 PRIVATE utils)

add_executable(2 src/2.c utils/inputHandler.c utils/fileHandler.c)
target_include_directories(2 PRIVATE utils)

add_executable(3 src/3.c utils/inputHandler.c utils/fileHandler.c)
target_include_directories(3 PRIVATE utils)

add_executable(4 src/4.c utils/inputHandler.c utils/fileHandler.c)
target_include_directories(4 PRIVATE utils)

