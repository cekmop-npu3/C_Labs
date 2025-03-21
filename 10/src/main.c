#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"


int main(){
    float tasks[2] = {0, 1};
    Elem *task = handle(tasks, typeInt, "Enter the task name: ");
    if (task->value->Int)
        figureMenu();
    else {
        Elem *num = handle(NULL, typeInt, "Enter the number: ");
        printf("The remnant is: %d\n", remnant(num->value->Int));
        freeElem(num);
    }
    freeElem(task);
    return EXIT_SUCCESS;
}