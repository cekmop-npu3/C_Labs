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


void userInput(Array *array){
    for (int i = 0; i < array->size; i++)
        handleIntInput(&array->sequence[i], NULL, "Enter the element [%d]: ", i);
}

void randomInput(Array *array){
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = rand() % 100;
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


Matrix *initIntMatrix(int size){
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix != NULL){
        matrix->matrix = malloc(sizeof(Array *) * size);
        matrix->size = 0;
    }
    return matrix;
}


void matrixUserInput(Matrix *matrix){
    int arraySizeRange[2] = {1, MaxArraySize};
    for (int i = 0; i < matrix->size; i++){
        int size;
        handleIntInput(&size, arraySizeRange, "Enter the size of an array [%d]: ", i);
        Array *array = initIntArray(size);
        array->size = size;
        userInput(array);
        int *temp = realloc(array->sequence, (array->size + 1) * sizeof(int));
        if (temp != NULL){
            array->sequence = temp;
            array->sequence[array->size++] = 0;
        }
        matrix->matrix[i] = array;
    }
}


void matrixRandomInput(Matrix *matrix){
    srand(time(NULL));
    for (int i = 0; i < matrix->size; i++){
        int size = rand() % 9 + 1;
        Array *array = initIntArray(size);
        array->size = size;
        randomInput(array);
        int *temp = realloc(array->sequence, (array->size + 1) * sizeof(int));
        if (temp != NULL){
            array->sequence = temp;
            array->sequence[array->size++] = 0;
        }
        matrix->matrix[i] = array;
    }
}


Matrix *getFilledIntMatrix(){
    Input choice;
    int size;
    int matrixSizeRange[2] = {1, MaxArraySize};
    int choiceRange[2] = {0, 1};
    handleIntInput(&size, matrixSizeRange, "Enter the number of rows: ");
    Matrix *matrix = initIntMatrix(size);
    matrix->size = size;
    start:
    handleIntInput((int *) &choice, choiceRange, "Enter 0 to fill the matrix manually, 1 to fill it randomly: ");
    switch ((Input) choice){
        case UserInput:
            matrixUserInput(matrix);
            break;
        case RandomInput:
            matrixRandomInput(matrix);
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


int sum(Array *array){
    int _sum = 0;
    for (int i = 0; i< array->size; i++)
        _sum += array->sequence[i];
    return _sum;
}


void delMinSumRow(Matrix *matrix){
    int index = 0;
    for (int i = 1; i < matrix->size; i++)
        if (sum(matrix->matrix[i]) < sum(matrix->matrix[index]))
            index = i;
    for (int j = index; j < matrix->size - 1; j++)
        matrix->matrix[j] = matrix->matrix[j + 1];
    Array **temp = realloc(matrix->matrix, (matrix->size - 1) * sizeof(Array *));
    if (temp != NULL)
        matrix->matrix = temp;
        matrix->size--;
}


int main(){
    Matrix *matrix = getFilledIntMatrix();
    printMatrix(matrix);
    delMinSumRow(matrix);
    printf("\n");
    printMatrix(matrix);
    freeMatrix(matrix);
    return EXIT_SUCCESS;
}