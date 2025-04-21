#include "tasks.h"


static void print(void *data){
    printf("%s", ((Elem *) data)->value.Str);
}


static void printInt(void *data){
    printf("%d", *(int *) data);
}


static bool equal(Item *item1, Item *item2){
    return  ((Elem *) item1->data)->value.Str[0] == ((Elem *) item2->data)->value.Str[0];
}


static void listMenu(Elem *maxSize, Elem *ref){
    List *list = initList(maxSize->value.Int);
    double actionRange[2] = {0, 4};
    Elem *option;
    Elem *elem;
    Elem *index;
    Item *item;
    while (true){
        option = handle(typeInt, actionRange, "0 to add\n1 to insert\n2 to pop\n3 to print\n4 to remove\n>> ");
        switch (option->value.Int){
            case ADD:
                if ((elem = handle(typeStr, NULL, "Enter char: "))->value.Str[0] == ref->value.Str[0]){
                    freeElem(elem);
                    printList(list);
                    printf("\n");
                    freeList(list);
                    freeElem(option);
                    return;
                }
                append(list, initItem(elem, print, freeElem));
                break;
            case INSERT:
                if ((elem = handle(typeStr, NULL, "Enter char: "))->value.Str[0] == ref->value.Str[0]){
                    freeElem(elem);
                    printList(list);
                    printf("\n");
                    freeList(list);
                    freeElem(option);
                    return;
                }
                insert(list, initItem(elem, print, freeElem), (index = handle(typeInt, NULL, "Enter the index: "))->value.Int);
                freeElem(index);
                break;
            case POP:
                index = handle(typeInt, NULL, "Enter the index to delete: ");
                if ((item = pop(list, index->value.Int)) != NULL){
                    printItem(item);
                    printf("\n");
                    freeItem(item);
                }
                freeElem(index);
                break;
            case PRINT:
                printList(list);
                printf("\n");
                break;
            case REMOVE:
                removeItem(list, initItem(handle(typeStr, NULL, "Enter char to remove: "), print, freeElem), equal);
                break;
        }
        freeElem(option);
    }
}


static List *getList(const char *str, const char *pattern){
    List *list = initList(100);
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED);
    regmatch_t matches[1];
    while (regexec(&regex, str, 1, matches, 0) != REG_NOMATCH){
        char string[3];
        strncpy(string, str + matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so);
        string[2] = '\0';
        int *res = malloc(sizeof(int));
        *res = atoi(string);
        append(list, initItem(res, printInt, free));
        str += matches[0].rm_eo;
    }
    regfree(&regex);
    return list;
}


void task1(){
    Elem *maxSize = handle(typeInt, NULL, "Enter max size: ");
    Elem *ref = handle(typeStr, NULL, "Enter ref: ");
    listMenu(maxSize, ref);
    freeElem(maxSize);
    freeElem(ref);
}


void task2(){
    const char *str = "12 34 3 56 1 45 67 3";
    List *list1 = getList(str, "\\b[0-9]{2}\\b");
    List *list2 = getList(str, "\\b[0-9]\\b");
    List *result = initList(100);
    Item *item1;
    Item *item2;
    printList(list1);
    printf("\n");
    printList(list2);
    printf("\n");
    while (((item1 = pop(list1, 0)) != NULL) & ((item2 = pop(list2, 0)) != NULL)){
        int *res = malloc(sizeof(int));
        *res = *(int *) item1->data * *(int *) item2->data;
        append(result, initItem(res, printInt, free));
        freeItem(item1);
        freeItem(item2);
    }
    if (item1 != NULL)
        insert(list1, item1, 0);
    if (item2 != NULL)
        insert(list2, item2, 0);
    while ((item1 = pop(list1, 0)) != NULL)
        append(result, item1);
    while ((item2 = pop(list2, 0)) != NULL)
        append(result, item2);
    printList(result);
    printf("\n");
    freeList(result);
    freeList(list1);
    freeList(list2);
}