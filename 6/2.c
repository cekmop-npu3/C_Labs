#include <stdio.h>
#include <stdlib.h>

#include "utils/array.h"


void selectionSort(Array *array){
    int index = 0;
    start:
    for (int i = index; i < array->size; i++)
        if (array->sequence[index] > array->sequence[i]){
            int temp = array->sequence[index];
            array->sequence[index] = array->sequence[i];
            array->sequence[i] = temp;
        }
    if (++index < array->size)
        goto start;
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    selectionSort(array);
    printArray(array);
}