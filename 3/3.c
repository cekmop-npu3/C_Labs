#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "utils/inputHandlers.h"


Array *initIntArray(int size){
    Array *array = malloc(sizeof(Array));
    if (array != NULL){
        array->sequence = malloc(sizeof(int) * size);
        array->size = 0;
    }
    return array;
}


Counter *initIntCounter(int size){
    Counter *counter = malloc(sizeof(Counter));
    if (counter != NULL){
        counter->counters = malloc(sizeof(Count) * size);
        counter->size = 0;
    }
    return counter;
}

void printCounter(Counter *counter){
    for (int i = 0; i < counter->size; i++){
        printf("elem: %d, count: %d\n", counter->counters[i].elem, counter->counters[i].count);
    }
}


void freeCounter(Counter *counter){
    if (counter != NULL){
        if (counter->counters != NULL)
            free(counter->counters);
        free(counter);
    }
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


bool inArray(Counter *counter, int elem){
    for (int i = 0; i < counter->size; i++)
        if (elem == counter->counters[i].elem){
            counter->counters[i].count++;
            return true;    
        }
    return false;
}


Counter *count(Array *array){
    Count count;
    Counter *counter = initIntCounter(array->size);
    for (int i = 0; i < array->size; i++)
        if (!inArray(counter, array->sequence[i])){
            count.count = 1;
            count.elem = array->sequence[i];
            counter->counters[counter->size] = count;
            counter->size++;
        }
    return counter;
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    Counter *counter = count(array);
    printCounter(counter);
    freeArray(array);
    freeCounter(counter);
    return EXIT_SUCCESS;
}

