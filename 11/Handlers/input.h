#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define MaxStrSize 1024


typedef union {
    long Int;
    char *Str;
    double Double;
} Value;

typedef enum {
    typeInt,
    typeStr,
    typeDouble
} Type;

typedef struct {
    Type type;
    Value value;
} Elem;


void freeElem(Elem *elem);

Elem *input(const char *message, ...);

Elem *handle(Type type, double range[2], const char *message, ...);


#endif
