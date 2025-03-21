#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>


typedef union {
    int Int;
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
    Value *value;
} Elem;


void freeElem(Elem *elem);

static int onIntType(char *literal, int size);

static int addChar(char **dest, int size, char c);

Elem *input(char *message, ...);
