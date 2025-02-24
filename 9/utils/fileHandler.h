#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MaxStrSize 100

typedef enum {
    shiftRight,
    shiftLeft
} ShiftType;

char *setFilename(int argc, char *argv[]);

void fileInput(char *filename);

#endif