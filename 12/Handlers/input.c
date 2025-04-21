#include <input.h>


void freeElem(void *elemRaw){
    Elem *elem = (Elem *) elemRaw;
    if (elem->type == typeStr)
        free(elem->value.Str);
    free(elem);
}


Elem *input(const char *message, ...){
    char *result = malloc(sizeof(char) * MaxStrSize);
    if (result == NULL){
        fprintf(stderr, "Memory allocation error at input\n");
        return NULL;
    }
    if (message != NULL){
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
    }
    if (fgets(result, MaxStrSize, stdin) == NULL){
        fprintf(stderr, "Error occured reading stdin\n");
        free(result);
        return NULL;
    }
    result[strlen(result) - 1] = '\0';
    if (!strlen(result)) {
        free(result);
        return NULL;
    }
    Elem *elem = malloc(sizeof(Elem));
    if (elem == NULL){
        fprintf(stderr, "Memory allocation error at input\n");
        free(result);
        return NULL;
    }
    char *endPtr;
    elem->value.Int = strtol(result, &endPtr, 10);
    if (*endPtr == '\0'){
        elem->type = typeInt;
        free(result);
        return elem;
    }
    elem->value.Double = strtod(result, &endPtr);
    if (*endPtr == '\0'){
        elem->type = typeDouble;
        free(result);
        return elem;
    }
    elem->type = typeStr;
    elem->value.Str = result;
    return elem;
}


Elem *handle(Type type, double range[2], const char *message, ...){
    Elem *elem;
    char buffer[MaxStrSize];
    if (message != NULL){
        va_list args;
        va_start(args, message);
        vsprintf(buffer, message, args);
        va_end(args);
    }
    do {
        printf("%s", buffer);
        if ((elem = input(NULL)) != NULL && elem->type == type && (range == NULL || ((elem->type == typeInt ? elem->value.Int : elem->value.Double) >= range[0] && (elem->type == typeInt ? elem->value.Int : elem->value.Double) <= range[1])))
            return elem;
        freeElem(elem);
        printf("Wrong input, try again\n");
    } while (true);
}

