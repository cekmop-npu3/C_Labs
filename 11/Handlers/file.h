#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MaxStrSize 1024


typedef struct {
    char **lines;
    int len;
} Lines;


void freeLines(Lines *lines);

void printLines(Lines *lines);

Lines *readLines(const char *filename);


#endif