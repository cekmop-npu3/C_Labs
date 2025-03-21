#ifndef ARRAY_H
#define ARRAY_H

#include <geometry.h>
#include <stdbool.h>


typedef bool (*Key)(Figure *, void *);


typedef struct {
    int size;
    Figure **figures;
} Array;


Array *initArray();

bool addFigure(Array *array, Figure *figure);

bool removeFigures(Array *array, Key key, void *data);

Array *findFigures(Array *array, Key key, void *data);

void freeArray(Array *array);

void printArray(Array *array);


#endif