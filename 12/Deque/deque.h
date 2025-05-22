#ifndef Deque_H
#define Deque_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <item.h>


typedef struct {
    int len;
    int maxSize;
    Item **sequence;
} Deque;


Deque *initDeque(int maxSize);

void printDeque(void *dequeRaw);

void freeDeque(void *dequeRaw);

void append(Deque *deque, Item *item);

void appendLeft(Deque *deque, Item *item);

Item *pop(Deque *deque);

Item *popLeft(Deque *deque);


#endif
