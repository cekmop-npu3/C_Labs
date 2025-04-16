#include "tasks.h"
#include <input.h>


typedef enum {
    T1,
    T2,
    T3
} Tasks;
  

int main(){
    double range[2] = {0, 2};
    Elem *elem = handle(typeInt, range, "Enter task: ");
    switch (elem->value.Int){
        case T1:
            task1();
            break;
        case T2:
            task2();
            break;
        case T3:
            task3();
            break;
    }
    freeElem(elem);
    return EXIT_SUCCESS;
}
