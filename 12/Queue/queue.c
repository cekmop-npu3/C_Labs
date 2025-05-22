#include <queue.h>


Queue *initQueue(int maxSize){
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL){
        fprintf(stderr, "Cannot allocate memory for Queue\n");
        return NULL;
    }
    queue->sequence = NULL;
    queue->len = 0;
    queue->maxSize = maxSize;
    return queue;
}


void printQueue(void *queueRaw){
    Queue *queue = (Queue *) queueRaw;
    printf("[");
    for (int i = 0; i < queue->len; i++){
        printItem(queue->sequence[i]);
        if (i != queue->len - 1)
            printf(", ");
    }
    printf("]");
}


void freeQueue(void *queueRaw){
    if (queueRaw == NULL)
        return;
    Queue *queue = (Queue *) queueRaw;
    for (int i = 0; i < queue->len; i++)
        freeItem(queue->sequence[i]);
    free(queue->sequence);
    free(queue);
}


void add(Queue *queue, Item *item){
    if ((queue->len + 1) > queue->maxSize){
        printf("[WARNING] Queue max size exceeded, items will be shifted\n");
        freeItem(queue->sequence[0]);
        memmove(queue->sequence, queue->sequence + 1, sizeof(Item *) * --queue->len);
    }
    Item **tmpSequence = realloc(queue->sequence, sizeof(Item *) * (queue->len + 1));
    if (tmpSequence == NULL){
        fprintf(stderr, "Memory allocation error at Queue.append\n");
        return;
    }
    queue->sequence = tmpSequence;
    queue->sequence[queue->len++] = item; 
}


Item *delete(Queue *queue){
    if (!queue->len){
        printf("[WARNING] Queue is already empty\n");
        return NULL;
    }
    Item *item = queue->sequence[0];
    memmove(queue->sequence, queue->sequence + 1, sizeof(Item *) * --queue->len);
    return item;
}
