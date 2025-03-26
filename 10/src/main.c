#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <geometry.h>
#include <inputHandler.h>
#include <array.h>

#define Mask 0b0001


typedef enum {
    print,
    add,
    find, 
    delete_,
    exit_
} Action;


typedef struct {
    unsigned int firstBit:1;
    int rest:31;
} Byte;


typedef union {
    int num;
    Byte byte;
} BitMask;


Elem *handle(float range[2], Type type, char *message, ...){
    Elem *elem;
    if (message != NULL){
        va_list args;
        va_start(args, message);
        vfprintf(NULL, message, args);
        va_end(args);
    }
    do {
        if ((elem = input(message)) != NULL && elem->type == type && (range == NULL || ((elem->type == typeInt ? elem->value.Int : elem->value.Double) >= range[0] && (elem->type == typeInt ? elem->value.Int : elem->value.Double) <= range[1])))
            return elem;
        printf("Wrong input, try again\n");
    } while (true);
}


unsigned int remnant(int num){
    BitMask bitmask = {.num=num};
    return bitmask.byte.firstBit;
}


Figure *create(){
    Elem *square = handle(NULL, typeInt, "Enter the square of a figure: ");
    Elem *name = handle(NULL, typeStr, "Enter the name of a figure: ");
    Elem *perimeter = handle(NULL, typeDouble, "Enter the perimeter of a figure: ");
    Elem *color = handle(NULL, typeStr, "Enter the color of a figure: ");
    Figure *figure = createFigure(
        square->value.Int, 
        name->value.Str, 
        perimeter->value.Double, 
        color->value.Str
    );
    freeElem(square);
    freeElem(name);
    freeElem(perimeter);
    freeElem(color);
    return figure;
}


bool findKey(Figure *figure, void *square){
    return figure->square < (*((int *) square));
}


bool deleteKey(Figure *figure, void *name){
    return !strcmp(figure->name, (char *) name);
}


int main(){
    float tasks[2] = {0, 1};
    Elem *task = handle(tasks, typeInt, "Enter the task name: ");
    if (task->value.Int){
        Array *array = initArray();
        Array *tmp;
        float choiceRange[2] = {0, 4}; 
        Elem *choice;
        Elem *data;
        Figure *figure;
        do {
            choice = handle(
                choiceRange, 
                typeInt, 
                "0 to print the figure array\n1 to add a figure\n2 to find a figure\n3 to delete a figure\n4 to exit\n"
            );
            switch (choice->value.Int){
                case print:
                    printArray(array);
                    break;
                case add:
                    figure = create();
                    addFigure(array, figure);
                    break;
                case find:
                    data = handle(NULL, typeInt, "Enter the square: ");
                    tmp = findFigures(array, findKey, (void *) &(data->value.Int));
                    printArray(tmp);
                    free(tmp->figures);
                    free(tmp);
                    freeElem(data);
                    break;
                case delete_:
                    data = handle(NULL, typeStr, "Enter the name: ");
                    removeFigures(array, deleteKey, (void *) data->value.Str);
                    freeElem(data);
                    break;
            }
        } while (choice->value.Int != exit_);
        freeFigure(figure);
        freeArray(array);
        freeElem(choice);
    }
    else {
        Elem *num = handle(NULL, typeInt, "Enter the number: ");
        printf("The remnant is: %d\n", remnant(num->value.Int));
        freeElem(num);
    }
    freeElem(task);
    return EXIT_SUCCESS;
}