#pragma once

typedef struct {
    int *sequence;
    int size;
} Array;


typedef enum {
    UserInput,
    RandomInput
} Input;


typedef struct {
    int elem;
    int count;
} Count;


typedef struct {
    Count *counters;
    int size;
} Counter;


typedef struct {
    Array **matrix;
    int size;
} Matrix;
