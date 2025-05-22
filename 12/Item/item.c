#include <item.h>


Item *initItem(void *data, Print printFunc, Free freeFunc){
    Item *item = malloc(sizeof(Item));
    if (item == NULL){
        fprintf(stderr, "Cannot allocate memory for Item\n");
        return NULL;
    }
    item->data = data;
    item->freeFunc = freeFunc;
    item->printFunc = printFunc;
    return item;
}


void printItem(Item *item){
    item->printFunc != NULL ? item->printFunc(item->data) : printf("%p", item->data);
}


void freeItem(Item *item){
    if (item != NULL && item->freeFunc != NULL)
        item->freeFunc(item->data);
    free(item);
}