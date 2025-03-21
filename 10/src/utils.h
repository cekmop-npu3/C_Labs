#ifndef UTILS_H
#define UTILS_H

#include <geometry.h>
#include <inputHandler.h>
#include <array.h>

#define Mask 0b0001


typedef enum {
    print,
    add,
    find, 
    delete_,
    exit_
} Action;


typedef struct {
    unsigned int firstBit:1;
    int rest:31;
} Byte;


typedef union {
    int num;
    Byte byte;
} BitMask;


void figureMenu();

Elem *handle(float range[2], Type type, char *message, ...);

unsigned int remnant(int num);

Figure *create();

bool findKey(Figure *figure, void *square);

bool deleteKey(Figure *figure, void *name);

#endif