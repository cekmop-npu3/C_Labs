cmake_minimum_required(VERSION 3.10)
project(main)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=address -g")
endif()

add_executable(main src/main.c Queue/queue.c Deque/deque.c Item/item.c Tasks/tasks.c Handlers/input.c)

target_include_directories(main PRIVATE Queue Deque Item Tasks Handlers)
