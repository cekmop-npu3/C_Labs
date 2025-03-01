#ifndef FILE_HANDLER
#define FILE_HANDLER

#include "inputHandler.h"
#include <stdio.h>
#include <stdint.h>

typedef enum {
    shiftRight,
    shiftLeft
} ShiftType;

char *setFilename(int argc, char *argv[]);

void fileInput(char *filename);

void fileSwap(FILE *file, int index, int swapIndex);

#endif