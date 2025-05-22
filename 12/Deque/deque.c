#include <deque.h>


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
    if (dequeRaw == NULL)
        return;
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


void appendLeft(Deque *deque, Item *item){
    if ((deque->len + 1) > deque->maxSize){
        printf("[WARNING] Deque max size exceeded, items will be shifted\n");
        freeItem(deque->sequence[deque->len - 1]);
        deque->sequence = realloc(deque->sequence, sizeof(Item *) * --deque->len);
    }
    Item **tmpSequence = malloc(sizeof(Item *) * ++deque->len);
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at Deque.appendLeft\n");
        freeItem(item);
        return;
    }
    tmpSequence[0] = item;
    for (int i = 1; i < deque->len; i++)
        tmpSequence[i] = deque->sequence[i - 1];
    free(deque->sequence);
    deque->sequence = tmpSequence;
}


Item *pop(Deque *deque){
    if (!deque->len){
        printf("[WARNING] Deque is already empty\n");
        return NULL;
    }
    Item *item = deque->sequence[0];
    memmove(deque->sequence, deque->sequence + 1, sizeof(Item *) * --deque->len);
    return item;
}


Item *popLeft(Deque *deque){
    if (!deque->len){
        printf("[WARNING] Deque is already empty\n");
        return NULL;
    }
    Item *item = deque->sequence[deque->len - 1];
    deque->sequence = realloc(deque->sequence, sizeof(Item *) * --deque->len);
    return item;
}
