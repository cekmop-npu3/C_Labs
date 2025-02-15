#include "array.h"


Array *initArray(){
    Array *array = malloc(sizeof(Array));
    if (array != NULL){
        array->sequence = NULL;
        array->size = 0;
    }
    return array;
}


void userInput(Array *array){
    Elem *len;
    Elem *elem;
    int lenRange[2] = {0, INT_MAX};
    do {
        len = input("Enter the number of elements: ");
        if (len != NULL && len->type == typeInt && (lenRange == NULL || (len->value.Int > lenRange[0] && len->value.Int < lenRange[1])))
            break;
        printf("Wrong input, try again\n");
    } while (true);
    for (int i = 0; i < len; i++){
        do {
            elem = input("Enter the element [%d]: ", i);
            if (elem != NULL && elem->type == typeInt){
                array->sequence[i] = elem->value.Int;
                break;
            }
            printf("Wrong input, try again\n");
        } while (true);
    }
}


void randomInput(Array *array){
    srand(time(NULL));
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = rand() % 100;
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

