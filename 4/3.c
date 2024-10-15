#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
    UserInput = 1,
    Random = 2
} Option;


typedef struct {
    int **matrix;
    int rows;
    int columns;
} Matrix;


void throwException(char message[], size_t count, ...){
    if (count > 0){
        va_list args;
        va_start(args, count);
        for (int i = 0; i < count; i++){
            void *mem = va_arg(args, void*);
            free(mem);
        }
        va_end(args);
    }
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}


Matrix createMatrix(){
    int rows, columns;
    Matrix matrix;
    printf("Enter the number of rows: ");
    if (!scanf("%d", &rows) || rows <= 0)
        throwException("Invalid rows type", 0);
    printf("Enter the number of columns: ");
    if (!scanf("%d", &columns) || columns <= 0)
        throwException("Invalid columns type", 0);
    matrix.matrix = calloc(rows, sizeof(int *));
    if (matrix.matrix == NULL)
        throwException("Cannot allocate memory", 0);
    for (int i = 0; i < rows; i++) {
        matrix.matrix[i] = calloc(columns, sizeof(int));
        if (matrix.matrix[i] == NULL)
            throwException("Cannot allocate memory for matrix row", 1, matrix.matrix);
    }
    matrix.rows = rows;
    matrix.columns = columns;
    return matrix;
}


Matrix randomFill(){
    srand(time(NULL));
    Matrix matrix = createMatrix();
    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = rand();
    return matrix;
}


Matrix userInput(){
    Matrix matrix = createMatrix();
    for (int i = 0; i < matrix.rows; i++){
        printf("Enter the %d row: ", i);
        for (int j = 0; j < matrix.columns; j++)
            if (!scanf("%d", &matrix.matrix[i][j]))
                throwException("Invalid input type", 1, matrix.matrix);
    }
    return matrix;
}


Matrix getFilledMatrix(){
    int option;
    Matrix matrix;
    do {
        printf("Enter 1 to input your matrix\nEnter 2 to generate random matrix\n");
        if (!scanf("%d", &option)){
            while (getchar() != '\n');
            continue;
        }
        switch (option){
            case UserInput:
                matrix = userInput();
                break;
            case Random:
                matrix = randomFill();
                break;
        }
        return matrix;
    }
    while (true);
}


void freeMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
}


float getMax(Matrix *matrix){
    int padLeft = 0;
    int padRight = 0;
    float max = matrix->matrix[0][0];
    for (int i = 0; i < matrix->columns / 2; i++)
        for (int j = 0 + padLeft; j < matrix->columns - padRight; j++)
            if (matrix->matrix[i][j] > max)
                max = matrix->matrix[i][j];
    return max;
}


float maxElemInUpperTrig(Matrix *matrix){
    if (matrix->rows == matrix->columns && matrix->rows % 2 && matrix->columns % 2)
        return getMax(matrix);
    else {
        freeMatrix(matrix);
        throwException("Incorrect matrix size", 0);
    }
}


int main(){
    Matrix matrix = getFilledMatrix();
    printf("Max element is %.1f", maxElemInUpperTrig(&matrix));
    freeMatrix(&matrix);
    return EXIT_SUCCESS;
}
