#ifndef Item_H
#define Item_H

#include <stdlib.h>
#include <stdio.h>

typedef void (*Print)(void *);

typedef void (*Free)(void *);


typedef struct {
    void *data;
    Print printFunc;
    Free freeFunc;
} Item;

Item *initItem(void *data, Print printFunc, Free freeFunc);

void printItem(Item *item);

void freeItem(Item *item);

#endif