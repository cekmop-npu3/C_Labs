#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#include "utils/inputHandlers.h"


Array *initIntArray(int size){
    Array *array = malloc(sizeof(Array));
    if (array != NULL){
        array->sequence = malloc(sizeof(int) * size);
        array->size = 0;
    }
    return array;
}


void userInput(Array *array){
    for (int i = 0; i < array->size; i++)
        handleIntInput(&array->sequence[i], NULL, "Enter the element [%d]: ", i);
}

void randomInput(Array *array){
    srand(time(NULL));
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = rand() % 100;
}


Array *getFilledIntArray(){
    Input choice;
    int size;
    int arraySizeRange[2] = {1, MaxArraySize};
    int choiceRange[2] = {0, 1};
    handleIntInput(&size, arraySizeRange, "Enter the size of an array: ");
    Array *array = initIntArray(size);
    array->size = size;
    start:
    handleIntInput((int *) &choice, choiceRange, "Enter 0 to fill the array manually, 1 to fill it randomly: ");
    switch ((Input) choice){
        case UserInput:
            userInput(array);
            break;
        case RandomInput:
            randomInput(array);
            break;
        default:
            goto start;
    }
    return array;
}


void printArray(Array *array){
    if (array != NULL && array->sequence != NULL && array->size > 0)
        for (int i = 0; i < array->size; i++)
            printf("%d ", array->sequence[i]);
    printf("\n");
}


void freeArray(Array *array){
    if (array != NULL){
        if (array->sequence != NULL)
            free(array->sequence);
        free(array);
    }
}


bool inArray(Array *array, int elem){
    for (int i = 0; i < array->size; i++)
        if (elem == array->sequence[i])
            return true;
    return false;
}


Array *set(Array *array){
    Array *tempArray = initIntArray(array->size);
    for (int i = 0; i < array->size; i++){
        if (!inArray(tempArray, array->sequence[i])){
            tempArray->sequence[tempArray->size] = array->sequence[i];
            tempArray->size++;
        }
    }
    freeArray(array);
    return tempArray;
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    Array *setArray = set(array);
    printArray(setArray);
    return EXIT_SUCCESS;
}

