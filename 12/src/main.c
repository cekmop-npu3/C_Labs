#include "tasks.h"
#include <input.h>


typedef enum {
    EXIT,
    TASK1,
    TASK2,
    TASK3
} Tasks;
  

int main(){
    double range[2] = {0, 4};
    Elem *elem;
    while ((elem = handle(typeInt, range, "Enter task 1-3 or 0 to exit: "))->value.Int != EXIT){
        switch (elem->value.Int){
            case TASK1:
                task1();
                break;
            case TASK2:
                task2();
                break;
            case TASK3:
                task3();
                break;
        }
        freeElem(elem);
    }
    freeElem(elem);
    return EXIT_SUCCESS;
}

