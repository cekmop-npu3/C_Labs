#include <stdio.h>
#include <stdlib.h>

#include "utils/array.h"


void merge(Array *array, Array *leftArray, Array *rightArray) {
    int leftIndex = 0;
    int rightIndex = 0;
    array->size = 0;
    while (leftIndex < leftArray->size && rightIndex < rightArray->size)
        array->sequence[array->size++] = (leftArray->sequence[leftIndex] < rightArray->sequence[rightIndex] ? leftArray->sequence[leftIndex++] : rightArray->sequence[rightIndex++]);
    while (leftIndex < leftArray->size)
        array->sequence[array->size++] = leftArray->sequence[leftIndex++];
    while (rightIndex < rightArray->size)
        array->sequence[array->size++] = rightArray->sequence[rightIndex++];
    freeArray(leftArray);
    freeArray(rightArray);
}


void mergeSort(Array *array) {
    if (array->size > 1) {
        int leftSize = array->size / 2;
        int rightSize = array->size - leftSize;
        Array *leftArray = initIntArray(leftSize);
        for (int i = 0; i < leftSize; i++) {
            leftArray->sequence[i] = array->sequence[i];
        }
        leftArray->size = leftSize;
        Array *rightArray = initIntArray(rightSize);
        for (int j = 0; j < rightSize; j++) {
            rightArray->sequence[j] = array->sequence[leftSize + j];
        }
        rightArray->size = rightSize;
        mergeSort(leftArray);
        mergeSort(rightArray);
        merge(array, leftArray, rightArray);
    }
}

int main() {
    Array *array = getFilledIntArray();
    printArray(array);  
    mergeSort(array);   
    printArray(array); 
    freeArray(array);
    return EXIT_SUCCESS;
}
