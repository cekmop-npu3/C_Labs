#include <stdlib.h>
#include <stdio.h>

#include "utils/array.h"


void swap(int *num1, int *num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}


void recursiveCall(Array *array, int start, int stop){
    if (stop - start){
        int pivot = array->sequence[stop - 1];
        int j = start - 1;
        for (int i = start; i < stop - 1; i++)
            if (array->sequence[i] < pivot)
                swap(&array->sequence[i], &array->sequence[++j]);
        swap(&array->sequence[stop - 1], &array->sequence[++j]);
        recursiveCall(array, start, j);
        recursiveCall(array, ++j, stop);
    }
}


void quickSort(Array *array){
    recursiveCall(array, 0, array->size);
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    quickSort(array);
    printArray(array);
    freeArray(array);
}
