#include <array.h>


Array *initArray(){
    Array *array = malloc(sizeof(Array));
    if (array != NULL){
        array->sequence = NULL;
        array->size = 0;
    }
    return array;
}


void freeArray(Array *array){
    free(array->sequence);
    free(array);
}


void printArray(Array *array){
    if (array != NULL && array->sequence != NULL && array->size > 0)
        for (int i = 0; i < array->size; i++)
            printf("%d ", array->sequence[i]);
    printf("\n");
}


static int inputArraySize(Array *array){
    Elem *len;
    int lenRange[2] = {0, INT_MAX};
    do {
        len = input("Enter the number of elements: ");
        if (len != NULL && len->type == typeInt && (lenRange == NULL || (len->value.Int > lenRange[0] && len->value.Int < lenRange[1])))
            break;
        printf("Wrong input, try again\n");
    } while (true);
    array->sequence = malloc(sizeof(int) * len->value.Int);
    if (array->sequence == NULL)
        return 0;
    return len->value.Int;
}


void userInput(Array *array){
    Elem *elem;
    int len = inputArraySize(array);
    for (array->size; array->size < len; array->size++){
        do {
            elem = input("Enter the element [%d]: ", array->size);
            if (elem != NULL && elem->type == typeInt){
                array->sequence[array->size] = elem->value.Int;
                break;
            }
            printf("Wrong input, try again\n");
        } while (true);
    }
}


void randomInput(Array *array){
    int len = inputArraySize(array);
    srand(time(NULL));
    for (array->size; array->size < len; array->size++)
        array->sequence[array->size] = rand() % 100;
}


void switchInput(Array *array){
    Elem *choice;
    do {
        choice = input("Enter 0 to fill an array manually, 1 to fill it randomly: ");
        if (choice != NULL && choice->type == typeInt)
            break;
        printf("Wrong input, try again\n");
    } while (true);
    choice ? randomInput(array) : userInput(array);
}

