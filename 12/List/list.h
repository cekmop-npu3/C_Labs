#ifndef List_H
#define List_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef void (*Print)(void *);

typedef void (*Free)(void *);


typedef struct {
    void *data;
    Print printFunc;
    Free freeFunc;
} Item;

typedef bool (*Equal)(Item *, Item *);


typedef struct {
    int len;
    int maxSize;
    Item **sequence;
} List;


Item *initItem(void *data, Print printFunc, Free freeFunc);

void printItem(Item *item);

void freeItem(Item *item);

List *initList(int maxSize);

void printList(void *listRaw);

void freeList(void *listRaw);

void append(List *list, Item *item);

Item *pop(List *list, int index);

bool hasItem(List *list, Item *item, Equal equal);

void removeItem(List *list, Item *item, Equal equal);

void insert(List *list, Item *item, int index);


#endif
