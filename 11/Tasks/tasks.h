#ifndef TASKS_H
#define TASKS_H

#include <input.h>
#include <file.h>
#include <list.h>
#include <limits.h>
#include <eval.h>


typedef enum {
    INC,
    DEC,
} ListType;


List *inputList();

void task1();

void task2();

void task3();

#endif