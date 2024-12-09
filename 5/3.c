#include <stdio.h>
#include <stdlib.h>

#include "utils/inputHandlers.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

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
    srand(time(NULL));
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


Array *getLongestPositiveSeq(Matrix *matrix){
    Array *main = initIntArray(0);
    Array *temp = initIntArray(0);
    for (int i = 0; i < matrix->size; i++)
        for (int j = 0; j < matrix->matrix[i]->size; j++){
            if (matrix->matrix[i]->sequence[j] >= 0){
                //printf("Adding to temp array: %d\n", matrix->matrix[i]->sequence[j]);
                temp->sequence = realloc(temp->sequence, (temp->size + 1) * sizeof(int));
                temp->sequence[temp->size++] = matrix->matrix[i]->sequence[j];
            }
            else {
                if (temp->sequence != NULL && temp->size > main->size){
                    main->sequence = realloc(temp->sequence, sizeof(int) * temp->size);
                    main->size = temp->size;
                }
                temp->sequence = NULL;
                temp->size = 0;
            }
        }
    if (temp->sequence != NULL && temp->size > main->size){
        main->sequence = realloc(temp->sequence, sizeof(int) * temp->size);
        main->size = temp->size;
    }
    free(temp);
    return main;
}


int main(){
    Matrix *matrix = getFilledIntMatrix();
    printMatrix(matrix);
    printf("\n");
    Array *array = getLongestPositiveSeq(matrix);
    printArray(array);
    freeArray(array);
    freeMatrix(matrix);
    return EXIT_SUCCESS;
}