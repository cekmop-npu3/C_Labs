#include <stdio.h>
#include <stdlib.h>

#include "utils/inputHandlers.h"
#include <time.h>
#include <stdlib.h>

#define MaxArraySize 64


Array *initIntArray(int size){
    Array *array = malloc(sizeof(Array));
    if (array != NULL){
        array->sequence = malloc(sizeof(int) * size);
        array->size = 0;
    }
    return array;
}


void randomInput(Array *array){
    srand(time(NULL));
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = rand() % 100;
}


Array *getFilledIntArray(){
    int size;
    int arraySizeRange[2] = {1, MaxArraySize};
    int choiceRange[2] = {0, 1};
    handleIntInput(&size, arraySizeRange, "Enter the size of an array: ");
    Array *array = initIntArray(size);
    array->size = size;
    randomInput(array);
    return array;
}


void printArray(Array *array){
    if (array != NULL && array->sequence != NULL && array->size > 0)
        for (int i = 0; i < array->size; i++)
            printf("%d ", array->sequence[i]);
    printf("\n");
}


void freeArray(Array *array){
    free(array->sequence);
    free(array);
}


void popEven(Array *array){
    int index = 0;
    for (int i = 0; i < array->size; i++)
        if (array->sequence[i] % 2)
            array->sequence[index++] = array->sequence[i];
    int *temp = realloc(array->sequence, sizeof(int) * index);
    if (temp != NULL){
        array->sequence = temp;
        array->size = index;
    }
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    popEven(array);
    printArray(array);
    freeArray(array);
    return EXIT_SUCCESS;
}