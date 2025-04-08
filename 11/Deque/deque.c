#include <deque.h>


Item *initItem(void *data, void *meta, Print printFunc, Free freeFunc){
    Item *item = malloc(sizeof(Item));
    if (item == NULL){
        fprintf(stderr, "Cannot allocate memory for Item\n");
        return NULL;
    }
    item->data = data;
    item->meta = meta;
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


Deque *initDeque(int maxSize){
    Deque *deque = malloc(sizeof(Deque));
    if (deque == NULL){
        fprintf(stderr, "Cannot allocate memory for Deque\n");
        return NULL;
    }
    deque->sequence = NULL;
    deque->len = 0;
    deque->maxSize = maxSize;
    return deque;
}


void printDeque(void *dequeRaw){
    Deque *deque = (Deque *) dequeRaw;
    printf("[");
    for (int i = 0; i < deque->len; i++){
        printItem(deque->sequence[i]);
        if (i != deque->len - 1)
            printf(", ");
    }
    printf("]");
}


void freeDeque(void *dequeRaw){
    Deque *deque = (Deque *) dequeRaw;
    for (int i = 0; i < deque->len; i++)
        freeItem(deque->sequence[i]);
    free(deque->sequence);
    free(deque);
}


void append(Deque *deque, Item *item){
    if ((deque->len + 1) > deque->maxSize){
        printf("[WARNING] Deque max size exceeded, items will be shifted\n");
        freeItem(deque->sequence[0]);
        memmove(deque->sequence, deque->sequence + 1, sizeof(Item *) * --deque->len);
    }
    Item **tmpSequence = realloc(deque->sequence, sizeof(Item *) * (deque->len + 1));
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at Deque.append\n");
        return;
    }
    deque->sequence = tmpSequence;
    deque->sequence[deque->len++] = item; 
}


Item *pop(Deque *deque, int index){
    if (!deque->len){
        printf("[WARNING] Deque is already empty\n");
        return NULL;
    }
    while (index < 0)
        index = deque->len + index;
    if (index > deque->len - 1){
        fprintf(stderr, "Deque index out of range");
        return NULL;
    }
    Item **tmpSequence = malloc(sizeof(Item *) * (deque->len - 1));
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at Deque.pop\n");
        return NULL;
    }
    Item *item = deque->sequence[index];
    for (int i = 0; i < deque->len; i++)
        if (i != index)
            tmpSequence[i > index ? i - 1 : i] = deque->sequence[i];
    free(deque->sequence);
    deque->sequence = tmpSequence;
    --deque->len;
    return item;
}


static bool equalBase(Item *item1, Item *item2){
    return item1->data == item2->data;
}


bool hasItem(Deque *deque, Item *item, Equal equal){
    equal = equal != NULL ? equal : equalBase;
    for (int i = 0; i < deque->len; i++)
        if (equal(item, deque->sequence[i])){
            freeItem(item);
            return true;
        }
    freeItem(item);
    return false;
}


void removeItem(Deque *deque, Item *item, Equal equal){
    equal = equal != NULL ? equal : equalBase;
    if (!deque->len){
        printf("[WARNING] Deque is already empty\n");
        freeItem(item);
        return;
    }
    Item **tmpSequence = NULL;
    Item **temp = NULL;
    int shift = 0;
    for (int i = 0; i < deque->len; i++)
        if (equal(item, deque->sequence[i]) && ++shift)
            freeItem(deque->sequence[i]);
        else {
            temp = realloc(tmpSequence, sizeof(Item *) * (i - shift + 1));
            if (temp == NULL){
                fprintf(stderr, "Memory allocation error at Deque.remove\n");
                freeItem(item);
                return;
            }
            tmpSequence = temp;
            tmpSequence[i - shift] = deque->sequence[i];    
        }
    freeItem(item);
    free(deque->sequence);
    deque->sequence = tmpSequence;
    deque->len -= shift;
}


void insert(Deque *deque, Item *item, int index){
    while (index < 0)
        index = deque->len + index + 1;
    if (index > deque->len){
        fprintf(stderr, "Deque index out of range\n");
        freeItem(item);
        return;
    }
    if ((deque->len + 1) > deque->maxSize){
        if (index == deque->len){
            fprintf(stderr, "Cannot insert item at index %d\n", index);
            freeItem(item);
            return;
        }
        printf("[WARNING] Deque max size exceeded, items will be shifted\n");
        freeItem(deque->sequence[--deque->len]);
    }
    Item **tmpSequence = malloc(sizeof(Item *) * ++deque->len);
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at Deque.append\n");
        freeItem(item);
        return;
    }
    for (int i = 0; i < deque->len; i++)
        tmpSequence[i] = i == index ? item : deque->sequence[i < index ? i : i - 1];
    free(deque->sequence);
    deque->sequence = tmpSequence;
}
