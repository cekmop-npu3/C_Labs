#pragma once

#include "../utils/inputHandler.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int *sequence;
    int size;
} Array;


Array *initArray();

void freeArray(Array *array);

void printArray(Array *array);

static int inputArraySize(Array *array);

void userInput(Array *array);

void randomInput(Array *array);

void switchInput(Array *array);
