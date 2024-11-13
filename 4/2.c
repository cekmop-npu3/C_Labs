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


void throwException(char message[], int count, ...){
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
    do {
        printf("Enter the number of rows: ");
        if (!scanf("%d", &rows) || rows <= 0){
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    while (true);
    do {
        printf("Enter the number of columns: ");
        if (!scanf("%d", &columns) || columns <= 0){
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    while (true);
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
        start:
        printf("Enter the %d row: ", i);
        for (int j = 0; j < matrix.columns; j++)
            if (!scanf("%d", &matrix.matrix[i][j])){
                while (getchar() != '\n');
                goto start;
            }
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
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
}


void invertRow(int *row, int *size){
    for (int i = 0; i < *size; i++){
        row[i] *= -1;
    }
}


void rowHasPosNum(Matrix *matrix){
    for (int i = 1; i < matrix->rows; i++){
        for (int j = 0; j < matrix->columns; j++){
            if (matrix->matrix[i][j] > 0){
                printf("Row number %d has positive number\n", i);
                invertRow(matrix->matrix[i - 1], &(matrix->columns));
                printf("Inverted row number %d: ", i - 1);
                for (int g = 0; g < matrix->columns; g++)
                    printf("%d ", matrix->matrix[i - 1][g]);
                printf("\n");
                break;
            }
        }
    }
}


void printMatrix(Matrix *matrix){
    for (int i = 0; i < matrix->rows; i++){
        for (int j = 0; j < matrix->columns; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
}


int main(){
    Matrix matrix = getFilledMatrix();
    printMatrix(&matrix);
    rowHasPosNum(&matrix);
    freeMatrix(&matrix);
    return EXIT_SUCCESS;
}
