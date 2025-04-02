#include <deque.h>


void printInt(void *data){
    printf("%d", *(int *) data);
}

void printString(void *data){
    printf("%s", (char *) data);
}
  

int main(){
    Deque *deque = initDeque(1);
    Deque *inner = initDeque(3);
    append(inner, initItem("const char *", printString, NULL));
    int nums[] = {1, 2};
    for (int i = 0; i < 2; i++)
        append(inner, initItem(&nums[i], printInt, NULL));
    printDeque(inner);
    printf("\n");
    append(deque, initItem(inner, printDeque, freeDeque));
    append(deque, initItem(&nums[0], printInt, NULL));
    printDeque(deque);
    printf("\n");
    freeDeque(deque);
}