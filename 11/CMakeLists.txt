cmake_minimum_required(VERSION 3.10)
project(main)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=address -g")
endif()

add_executable(main src/main.c List/list.c Eval/eval.c Handlers/input.c Tasks/tasks.c)

target_include_directories(main PRIVATE List Eval Handlers Tasks)
