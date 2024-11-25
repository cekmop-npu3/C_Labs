#pragma once
#include <time.h>
#include <stdlib.h>
#include "inputHandlers.h"
#include "types.h"


Array *initIntArray(int size);

void userInput(Array *array);

void randomInput(Array *array);

Array *getFilledIntArray();

void printArray(Array *array);

void freeArray(Array *array);

