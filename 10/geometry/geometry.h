#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MaxStrSize 100


typedef struct {
    float num;
} Perimeter;


typedef struct {
    int square;
    char *name;
    Perimeter perimeter;
    char color[MaxStrSize];
} Figure;


Figure *createFigure(
    int square,
    const char *name,
    float perimeter,
    const char *color
);

void printFigure(Figure *figure);

void freeFigure(Figure *figure);


#endif
