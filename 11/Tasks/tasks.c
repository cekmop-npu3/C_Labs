#include "tasks.h"


static void printInt(void *data){
    printf("%ld", ((Elem *) data)->value.Int);
}


static bool equal(Item *item1, Item *item2){
    return ((Elem *) item1->data)->value.Int == ((Elem *) item2->data)->value.Int;
}


List *inputList(){
    double listTypeRange[2] = {0, 2};
    double maxLenRange[2] = {1, 10};
    double range[2] = {INT_MIN, INT_MAX};
    Elem *prev = NULL;
    Elem *listType = handle(typeInt, listTypeRange, "List type:\n0 - increasing\n1 - decreasing\n2 - default\n$ ");
    Elem *maxLen = handle(typeInt, maxLenRange, "Enter max size: ");
    List *list = initList(maxLen->value.Int);
    for (int i = 0; i < maxLen->value.Int; i++){
        if (prev != NULL && listType->value.Int == 1)
            range[1] = prev->value.Int - 1;
        else if (prev != NULL && !listType->value.Int)
            range[0] = prev->value.Int + 1;
        append(list, initItem((prev = handle(typeInt, range, "Enter elem [%d]: ", i)), printInt, freeElem));
    }
    printList(list);
    printf("\n");
    freeElem(listType);
    freeElem(maxLen);
    return list;
}


void task1(){
    List *list1 = inputList();
    List *list2 = inputList();
    List *result = initList(list1->len);
    for (int i = 0; i < list1->len; i++)
        if (hasItem(list2, list1->sequence[i], equal))
            append(result, pop(list1, i--));
    freeList(list1);
    freeList(list2);
    printList(result);
    printf("\n");
    freeList(result);
}


void task2(){
    List *list1 = inputList();
    List *list2 = inputList();
    List *result = initList(list1->len + list2->len);
    while (list1->len && list2->len)
        append(result, (((Elem *) list1->sequence[0]->data)->value.Int < ((Elem *) list2->sequence[0]->data)->value.Int ? pop(list1, 0): pop(list2, 0)));
    while (list1->len)
        append(result, pop(list1, 0));
    while (list2->len)
        append(result, pop(list2, 0));
    printList(result);
    printf("\n");
    freeList(result);
    freeList(list1);
    freeList(list2);
}