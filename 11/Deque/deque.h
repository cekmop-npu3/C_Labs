#ifndef DEQUE_H
#define DEQUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef void (*Print)(void *);

typedef void (*Free)(void *);


typedef struct {
    void *data;
    Print printFunc;
    Free freeFunc;
} Item;


typedef struct {
    int len;
    int maxSize;
    Item **sequence;
} Deque;


Item *initItem(void *data, Print printFunc, Free freeFunc);

void printItem(Item *item);

void freeItem(Item *item);

Deque *initDeque(int maxSize);

void printDeque(void *dequeRaw);

void freeDeque(void *dequeRaw);

void append(Deque *deque, Item *item);

Item *pop(Deque *deque, int index);


#endif
