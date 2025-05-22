#ifndef Queue_H
#define Queue_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <item.h>


typedef struct {
    int len;
    int maxSize;
    Item **sequence;
} Queue;


Queue *initQueue(int maxSize);

void printQueue(void *queueRaw);

void freeQueue(void *queueRaw);

void add(Queue *queue, Item *item);

Item *delete(Queue *queue);


#endif
