#include <stdio.h>
#include <stdlib.h>

#include "utils/inputHandlers.h"
#include "utils/array.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MaxArraySize 64


Matrix *initIntMatrix(int size){
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix != NULL){
        matrix->matrix = malloc(sizeof(Array *) * size);
        matrix->size = 0;
    }
    return matrix;
}


void matrixUserInput(Matrix *matrix, int size){
    int arraySizeRange[2] = {1, MaxArraySize};
    for (int i = 0; i < matrix->size; i++){
        Array *array = initIntArray(size);
        array->size = size;
        printf("You are entering the array of index %d\n", i);
        userInput(array);
        matrix->matrix[i] = array;
    }
}


void matrixRandomInput(Matrix *matrix, int size){
    for (int i = 0; i < matrix->size; i++){
        Array *array = initIntArray(size);
        array->size = size;
        randomInput(array);
        matrix->matrix[i] = array;
    }
}


Matrix *getFilledIntMatrix(){
    Input choice;
    int size;
    int arraySize;
    int matrixSizeRange[2] = {1, MaxArraySize};
    int choiceRange[2] = {0, 1};
    handleIntInput(&size, matrixSizeRange, "Enter the number of rows: ");
    handleIntInput(&arraySize, matrixSizeRange, "Enter the number of columns: ");
    Matrix *matrix = initIntMatrix(size);
    matrix->size = size;
    start:
    handleIntInput((int *) &choice, choiceRange, "Enter 0 to fill the matrix manually, 1 to fill it randomly: ");
    switch ((Input) choice){
        case UserInput:
            matrixUserInput(matrix, arraySize);
            break;
        case RandomInput:
            matrixRandomInput(matrix, arraySize);
            break;
        default:
            goto start;
    }
    return matrix;
}


void freeMatrix(Matrix *matrix){
    for (int i = 0; i < matrix->size; i++)
        freeArray(matrix->matrix[i]);
    free(matrix);
}


void printMatrix(Matrix *matrix){
    for (int i = 0; i < matrix->size; i++)
        printArray(matrix->matrix[i]);
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


int getMax(Counter *counter){
    int max = 0;
    for (int i = 0; i < counter->size; i++)
        if (counter->counters[i].count > 1)
            max++;
    return max;
}


void selectionSort(Matrix *matrix, Array *array){
    int index = 0;
    start:
    for (int i = index; i < array->size; i++)
        if (array->sequence[index] > array->sequence[i]){
            int temp = array->sequence[index];
            array->sequence[index] = array->sequence[i];
            array->sequence[i] = temp;

            for (int j = 0; j < matrix->size; j++){
                int tempElem = matrix->matrix[j]->sequence[index];
                matrix->matrix[j]->sequence[index] = matrix->matrix[j]->sequence[i];
                matrix->matrix[j]->sequence[i] = tempElem;
            }
        }
    if (++index < array->size)
        goto start;
}


void selectionSortCols(Matrix *matrix){
    Array *colsSettedArray = initIntArray(matrix->matrix[0]->size);
    for (int cols = 0; cols < matrix->matrix[0]->size; cols++){
        Array *colArray = initIntArray(matrix->size);
        for (int rows = 0; rows < matrix->size; rows++){
            colArray->sequence[colArray->size++] = matrix->matrix[rows]->sequence[cols];
        }
        Counter *counter = count(colArray);
        colsSettedArray->sequence[colsSettedArray->size++] = getMax(counter);
        freeArray(colArray);
        freeCounter(counter);
    }
    selectionSort(matrix, colsSettedArray);
    freeArray(colsSettedArray);
}


int main(){
    Matrix *matrix = getFilledIntMatrix();
    printMatrix(matrix);
    selectionSortCols(matrix);
    printf("\n");
    printMatrix(matrix);
    freeMatrix(matrix);
    return EXIT_SUCCESS;
}