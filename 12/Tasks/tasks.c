#include "tasks.h"


static void print(void *data){
    printf("%s", ((Elem *) data)->value.Str);
}


static void printInt(void *data){
    printf("%d", *(int *) data);
}


static Queue *getQueue(const char *str, const char *pattern){
    Queue *queue = initQueue(100);
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED);
    regmatch_t matches[1];
    while (regexec(&regex, str, 1, matches, 0) != REG_NOMATCH){
        char string[3];
        strncpy(string, str + matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so);
        string[2] = '\0';
        int *res = malloc(sizeof(int));
        *res = atoi(string);
        add(queue, initItem(res, printInt, free));
        str += matches[0].rm_eo;
    }
    regfree(&regex);
    return queue;
}


static void queueMenu(Elem *maxSize, Elem *ref){
    Queue *queue = initQueue(maxSize->value.Int);
    double actionRange[2] = {0, 3};
    Elem *option;
    Elem *elem;
    Item *item;
    while (true){
        option = handle(typeInt, actionRange, "0 to add\n1 to pop\n2 to print\n>> ");
        switch (option->value.Int){
            case ADD:
                if ((elem = handle(typeStr, NULL, "Enter char: "))->value.Str[0] == ref->value.Str[0]){
                    freeElem(elem);
                    printQueue(queue);
                    printf("\n");
                    freeElem(option);
                    freeQueue(queue);
                    return;
                }
                add(queue, initItem(elem, print, freeElem));
                break;
            case DELETE:
                if ((item = delete(queue)) != NULL){
                    printItem(item);
                    printf("\n");
                    freeItem(item);
                }
                break;
            case PRINT_QUEUE:
                printQueue(queue);
                printf("\n");
                break;
        }
        freeElem(option);
    }
}


static void dequeMenu(Elem *maxSize, Elem *ref){
    Deque *deque = initDeque(maxSize->value.Int);
    double actionRange[2] = {0, 3};
    bool right = true;
    Elem *option;
    Elem *elem;
    Item *item;
    while (true){
        option = handle(typeInt, actionRange, "0 to append\n1 to pop\n2 to popLeft\n3 to print\n>> ");
        switch (option->value.Int){
            case APPEND:
                if ((elem = handle(typeStr, NULL, "Enter char: "))->value.Str[0] == ref->value.Str[0]){
                    freeElem(elem);
                    printDeque(deque);
                    printf("\n");
                    freeElem(option);
                    freeDeque(deque);
                    return;
                }
                if (right ^= 1)
                    appendLeft(deque, initItem(elem, print, freeElem));
                else
                    append(deque, initItem(elem, print, freeElem));
                break;
            case POP:
                if ((item = pop(deque)) != NULL){
                    printItem(item);
                    printf("\n");
                    freeItem(item);
                }
                break;
            case POP_LEFT:
                if ((item = popLeft(deque)) != NULL){
                    printItem(item);
                    printf("\n");
                    freeItem(item);
                }
                break;
            case PRINT_DEQUE:
                printDeque(deque);
                printf("\n");
                break;
        }
        freeElem(option);
    }
}


void task1(){
    Elem *maxSize = handle(typeInt, NULL, "Enter max size: ");
    Elem *ref = handle(typeStr, NULL, "Enter ref: ");
    queueMenu(maxSize, ref);
    freeElem(maxSize);
    freeElem(ref);
}


void task2(){
    Elem *maxSize = handle(typeInt, NULL, "Enter max size: ");
    Elem *ref = handle(typeStr, NULL, "Enter ref: ");
    dequeMenu(maxSize, ref);
    freeElem(maxSize);
    freeElem(ref);
}


void task3(){
    const char *str = "12 34 3 56 1 45 67 3";
    Queue *queue1 = getQueue(str, "\\b[0-9]{2}\\b");
    Queue *queue2 = getQueue(str, "\\b[0-9]\\b");
    Queue *result = initQueue(100);
    Item *item1;
    Item *item2;
    printQueue(queue1);
    printf("\n");
    printQueue(queue2);
    printf("\n");
    while (((item1 = delete(queue1)) != NULL) & ((item2 = delete(queue2)) != NULL)){
        int *res = malloc(sizeof(int));
        *res = *(int *) item1->data * *(int *) item2->data;
        add(result, initItem(res, printInt, free));
        freeItem(item1);
        freeItem(item2);
    }
    if (item1 != NULL)
        add(result, item1);
    if (item2 != NULL)
        add(result, item2);
    while ((item1 = delete(queue1)) != NULL)
        add(result, item1);
    while ((item2 = delete(queue2)) != NULL)
        add(result, item2);
    printQueue(result);
    printf("\n");
    freeQueue(result);
    freeQueue(queue1);
    freeQueue(queue2);
}