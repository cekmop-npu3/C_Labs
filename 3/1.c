#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct {
    int *sequence;
    int size;
} Array;


typedef enum {
    UserInput,
    RandomInput
} Input;


void handleIntInput(int *num, char *msg, bool isUnsigned){
    do {
        if (msg != NULL)
            printf("%s", msg);
        if (scanf("%d", num)){
            while (getchar() != '\n');
            if (isUnsigned && !(*num >= 0))
                continue;
            break;
        }
        while (getchar() != '\n');
    }
    while (true);
}


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
        handleIntInput(&array->sequence[i], "Enter the element: ", false);
}

void randomInput(Array *array){
    srand(time(NULL));
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = rand() % 100;
}


Array *getFilledIntArray(){
    Input choice;
    int size;
    handleIntInput(&size, "Enter the size of an array: ", true);
    Array *array = initIntArray(size);
    array->size = size;
    start:
    handleIntInput((int *) &choice, "Enter 0 to fill the array manually, 1 to fill it randomly: ", false);
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


int max(Array *array){
    int maxElem = array->sequence[0];
    for (int i = 1; i < array->size; i++)
        if (array->sequence[i] > maxElem)
            maxElem = array->sequence[i];
    return maxElem;
}


int sumBetween2Positive(Array *array){
    int positive[4] = {1};
    for (int i = 0; i < array->size; i++)
        if (array->sequence[i] > 0){
            positive[positive[0]] = i;
            positive[0]++;
            if (positive[0] == 3)
                break;
        }
        else if (positive[0] == 2)
            positive[3] += array->sequence[i];
    return positive[0] == 3 ? positive[3] : 0;
}


int main(){
    Array *array = getFilledIntArray();
    printArray(array);
    printf("Max elem is %d\n", max(array));
    printf("Sum between first two positive elements: %d", sumBetween2Positive(array));
    freeArray(array);
    return EXIT_SUCCESS;
}

