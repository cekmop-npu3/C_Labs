#include <list.h>


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
    if (item->freeFunc != NULL)
        item->freeFunc(item->data);
    free(item);
}


List *initList(int maxSize){
    List *list = malloc(sizeof(List));
    if (list == NULL){
        fprintf(stderr, "Cannot allocate memory for List\n");
        return NULL;
    }
    list->sequence = NULL;
    list->len = 0;
    list->maxSize = maxSize;
    return list;
}


void printList(void *listRaw){
    List *list = (List *) listRaw;
    printf("[");
    for (int i = 0; i < list->len; i++){
        printItem(list->sequence[i]);
        if (i != list->len - 1)
            printf(", ");
    }
    printf("]");
}


void freeList(void *listRaw){
    List *list = (List *) listRaw;
    for (int i = 0; i < list->len; i++)
        freeItem(list->sequence[i]);
    free(list->sequence);
    free(list);
}


void append(List *list, Item *item){
    if ((list->len + 1) > list->maxSize){
        printf("[WARNING] List max size exceeded, items will be shifted\n");
        freeItem(list->sequence[0]);
        memmove(list->sequence, list->sequence + 1, sizeof(Item *) * --list->len);
    }
    Item **tmpSequence = realloc(list->sequence, sizeof(Item *) * (list->len + 1));
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at List.append\n");
        return;
    }
    list->sequence = tmpSequence;
    list->sequence[list->len++] = item; 
}


Item *pop(List *list, int index){
    if (!list->len){
        printf("[WARNING] List is already empty\n");
        return NULL;
    }
    while (index < 0)
        index = list->len + index;
    if (index > list->len - 1){
        fprintf(stderr, "List index out of range");
        return NULL;
    }
    Item **tmpSequence = malloc(sizeof(Item *) * (list->len - 1));
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at List.pop\n");
        return NULL;
    }
    Item *item = list->sequence[index];
    for (int i = 0; i < list->len; i++)
        if (i != index)
            tmpSequence[i > index ? i - 1 : i] = list->sequence[i];
    free(list->sequence);
    list->sequence = tmpSequence;
    --list->len;
    return item;
}


static bool equalBase(Item *item1, Item *item2){
    return item1->data == item2->data;
}


bool hasItem(List *list, Item *item, Equal equal){
    equal = equal != NULL ? equal : equalBase;
    for (int i = 0; i < list->len; i++)
        if (equal(item, list->sequence[i]))
            return true;
    return false;
}


void removeItem(List *list, Item *item, Equal equal){
    equal = equal != NULL ? equal : equalBase;
    if (!list->len){
        printf("[WARNING] List is already empty\n");
        freeItem(item);
        return;
    }
    Item **tmpSequence = NULL;
    Item **temp = NULL;
    int shift = 0;
    for (int i = 0; i < list->len; i++)
        if (equal(item, list->sequence[i]) && ++shift)
            freeItem(list->sequence[i]);
        else {
            temp = realloc(tmpSequence, sizeof(Item *) * (i - shift + 1));
            if (temp == NULL){
                fprintf(stderr, "Memory allocation error at List.remove\n");
                freeItem(item);
                return;
            }
            tmpSequence = temp;
            tmpSequence[i - shift] = list->sequence[i];    
        }
    freeItem(item);
    free(list->sequence);
    list->sequence = tmpSequence;
    list->len -= shift;
}


void insert(List *list, Item *item, int index){
    while (index < 0)
        index = list->len + index + 1;
    if (index > list->len){
        fprintf(stderr, "List index out of range\n");
        freeItem(item);
        return;
    }
    if ((list->len + 1) > list->maxSize){
        if (index == list->len){
            fprintf(stderr, "Cannot insert item at index %d\n", index);
            freeItem(item);
            return;
        }
        printf("[WARNING] List max size exceeded, items will be shifted\n");
        freeItem(list->sequence[--list->len]);
    }
    Item **tmpSequence = malloc(sizeof(Item *) * ++list->len);
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at List.append\n");
        freeItem(item);
        return;
    }
    for (int i = 0; i < list->len; i++)
        tmpSequence[i] = i == index ? item : list->sequence[i < index ? i : i - 1];
    free(list->sequence);
    list->sequence = tmpSequence;
}
