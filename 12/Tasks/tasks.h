#ifndef TASKS_H
#define TASKS_H

#include <input.h>
#include <queue.h>
#include <deque.h>
#include <limits.h>
#include <stdarg.h>
#include <regex.h>


typedef enum {
    ADD,
    DELETE,
    PRINT_QUEUE
} QueueAction;


typedef enum {
    APPEND,
    POP_LEFT,
    POP,
    PRINT_DEQUE
} DequeAction;


void task1();

void task2();

void task3();

#endif