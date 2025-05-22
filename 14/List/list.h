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

typedef Equal Compare;

typedef struct {
    int len;
    int maxSize;
    Item **sequence;
} List;


typedef struct {
    int index;
    Item *item;
} Match;


static inline void printItem(Item *item){
    item->printFunc != NULL ? item->printFunc(item->data) : printf("%p", item->data);
}

static inline bool equalBase(Item *item1, Item *item2){
    return item1->data == item2->data;
}

static inline bool cmpBase(Item *item1, Item *item2){
    return item1->data < item2->data;
}

static inline void printInt(void *data){
    printf("%d", *(int *) data);
}

Item *initItem(void *data, Print printFunc, Free freeFunc);

void printItem(Item *item);

void freeItem(Item *item);

List *initList(int maxSize);

void printList(void *listRaw);

void freeList(void *listRaw);

void append(List *list, Item *item);

Item *pop(List *list, int index);

bool hasItem(List *list, Item *item, Equal equal);

List *removeItem(List *list, Item *item, Equal equal, bool rmAll);

void insert(List *list, Item *item, int index);

void sort(List *list, Compare cmp);

List *find(List *list, Item *item, Compare cmp, bool all);


#endif
