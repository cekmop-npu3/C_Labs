#include <inputHandler.h>


void freeElem(Elem *elem){
    if (elem->type == typeStr)
        free(elem->value->Str);
    free(elem->value);
    free(elem);
}


static int onIntType(char *literal, int size){
    int result = 0;
    for (int i = size; i > 0; i--)
        result += pow(10, i - 1) * (literal[size - i] - '0');
    return result;
}


static int addChar(char **dest, int size, char c) {
    char *tmp = realloc(*dest, ++size * sizeof(char));
    if (tmp == NULL) {
        fprintf(stderr, "Memory reallocation error\n");
        return 0;
    }
    *dest = tmp;
    (*dest)[size - 1] = c;
    return size;
}


Elem *input(char *message, ...){
    if (message != NULL){
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
    }
    char c;
    int sign = 1;
    int index = 0;

    int rawSize = 0;
    char *raw = NULL;

    char *result[2] = {NULL, NULL};
    int partsSizes[2] = {0, 0};

    Type type = typeInt;
    Elem *elem = NULL;
    while (!((c = getchar()) == '\n' && rawSize)){
        if (!(rawSize = addChar(&raw, rawSize, c)))
            goto cleanup;
        if (c == '-' && !partsSizes[0] && sign == 1 && (type == typeInt || type == typeDouble)){
            sign = -1;
            continue;
        }
        if ((c == '.' || c == ',') && partsSizes[0] && type == typeInt){
            type = typeDouble;
            ++index;
            continue;
        }
        if (!(partsSizes[index] = addChar(&result[index], partsSizes[index], c)) || c == '\n')
            goto cleanup;
        if (!isdigit(c))
            type = typeStr;
    }
    elem = malloc(sizeof(Elem));
    if (elem == NULL){
        fprintf(stderr, "Memory allocation error");
        goto cleanup;
    }
    elem->value = malloc(sizeof(Value));
    if (elem->value == NULL){
        fprintf(stderr, "Memory allocation error");
        free(elem);
        goto cleanup;
    }
    switch (elem->type = type){
        case typeInt:
            elem->value->Int = sign * onIntType(result[0], partsSizes[0]);
            break;
        case typeDouble:
            if (partsSizes[1]){
                elem->value->Double = sign * (onIntType(result[0], partsSizes[0]) + onIntType(result[1], partsSizes[1]) / pow(10, partsSizes[1]));
                break;
            }
            elem->type = typeStr;
        case typeStr:
            elem->value->Str = malloc((rawSize + 1) * sizeof(char));
            if (elem->value->Str == NULL){
                fprintf(stderr, "Memory allocation error\n");
                free(elem);
                elem = NULL;
                goto cleanup;
            }
            strcpy(elem->value->Str, raw);
            elem->value->Str[rawSize] = '\0';
            break;
    }
    cleanup:
        free(result[0]);
        free(result[1]);
        free(raw);
        return elem;
}
