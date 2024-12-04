#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "types.h"

#define MaxStrLen 1024
#define MaxArraySize 64

void handleIntInput(int *num, int range[2], char *message, ...);
