#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MaxArraySize 64
#define MaxStrLen 1024


typedef struct {
    char *value;
    int size;
} Word;


typedef struct {
    char *raw;
    Word **words;
    int size;
    int len;
} Str;


typedef struct {
    Str **sequence;
    int size;
} StrArray;


void handleIntInput(int *num, int range[2], char *message, ...){
    char error[MaxStrLen + 25] = "Wrong input, try again.\n";
    if (message != NULL){
        char tmpString[MaxStrLen * 2];
        va_list args;
        va_start(args, message);
        vsnprintf(tmpString, MaxStrLen, message, args);
        va_end(args);
        printf("%s", tmpString);
        strcat(error, tmpString);
    }

    char c;
    start:
    *num = 0;
    char *res = NULL;
    int size = 0;
    int sign = 1;

    while (true){
        c = getchar();
        if (c == '\n' && size)
            break;
        if (c == '-' && sign == 1){
            sign = -1;
            continue;
        }
        if (isdigit(c)){
            res = realloc(res, ++size * sizeof(char));
            res[size - 1] = c;
            continue;
        }
        ungetc(c, stdin);
        while (getchar() != '\n');
        free(res);
        printf("%s", error);
        goto start;
    }
    for (int i = size; i > 0; i--)
        *num += pow(10, i - 1) * (res[size - i] - '0');
    free(res);
    *num *= sign;
    if (range != NULL && !(*num >= range[0] && *num <= range[1])){
        printf("%s", error);
        *num = 0;
        goto start;
    }
}


Str *getStr(char *message, ...){
    if (message != NULL){
        char tempString[MaxStrLen * 2];
        va_list args;
        va_start(args, message);
        vsnprintf(tempString, MaxStrLen, message, args);
        va_end(args);
        printf("%s", tempString);
    }

    Str *str = malloc(sizeof(Str));
    str->words = NULL;
    str->raw = NULL;
    str->size = 0;
    str->len = 0;
    char c;
    bool splited = true;

    while ((c = getchar()) != '\n' && c != EOF){
        putchar(c);
        c = (c == '\t' ? ' ' : c);
        if (c != ' '){
            if (splited){
                Word **tempWords = realloc(str->words, ++str->len * sizeof(Word *));
                if (tempWords != NULL)
                    str->words = tempWords;
                str->words[str->len - 1] = NULL;
                str->words[str->len - 1] = realloc(str->words[str->len - 1], sizeof(Word));
                str->words[str->len - 1]->size = 0;
                str->words[str->len - 1]->value = malloc(sizeof(char));
                str->words[str->len - 1]->value[str->words[str->len - 1]->size++] = c;
            }
            else {
                char *tempValue = realloc(str->words[str->len - 1]->value, ++str->words[str->len - 1]->size * sizeof(char));
                if (tempValue != NULL)
                    str->words[str->len - 1]->value = tempValue;
                str->words[str->len - 1]->value[str->words[str->len - 1]->size - 1] = c;
            }
            splited = false;
        }
        else if (c == ' ')
            splited = true;
        char *tempRaw = realloc(str->raw, ++str->size * sizeof(char));
        if (tempRaw != NULL)
            str->raw = tempRaw;
        str->raw[str->size - 1] = c;
    }
    str->raw = realloc(str->raw, str->size + 1); 
    str->raw[str->size] = '\0';
    for (int i = 0; i < str->len; i++){
        char *value = realloc(str->words[i]->value, str->words[i]->size + 1);
        if (value != NULL)
            str->words[i]->value = value;
        str->words[i]->value[str->words[i]->size] = '\0';
    }
    printf("\n");
    return str;
}


StrArray *initStrArray(int size){
    StrArray *array = malloc(sizeof(StrArray));
    if (array != NULL){
        array->sequence = malloc(sizeof(Str *) * size);
        array->size = 0;
    }
    return array;
}


void userInput(StrArray *array){
    for (int i = 0; i < array->size; i++)
        array->sequence[i] = getStr("Enter the string [%d]: ", i);
}


StrArray *getFilledStrArray(){
    int size;
    int arraySizeRange[2] = {1, MaxArraySize};
    int choiceRange[2] = {0, 1};
    handleIntInput(&size, arraySizeRange, "Enter the size of an array: ");
    StrArray *array = initStrArray(size);
    array->size = size;
    userInput(array);
    return array;
}


void printArray(StrArray *array){
    if (array != NULL && array->sequence != NULL && array->size > 0)
        for (int i = 0; i < array->size; i++)
            printf("%s\n", array->sequence[i]->raw);
    printf("\n");
}


void freeArray(StrArray *array){
    free(array->sequence);
    free(array);
}


void freeStr(Str *str){
    free(str->raw);
    for (int i = 0; i < str->len; i++){
        free(str->words[i]->value);
        free(str->words[i]);
    }
    free(str->words);
    free(str);
}


Word *getTheShortestWord(Str *str){
    Word *shortest = str->words[0];
    for (int i = 0; i < str->len; i++)
        if (str->words[i]->size < shortest->size)
            shortest = str->words[i];
    return shortest;
}


void swap(Str **str1, Str **str2){
    Str *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}


void recursiveCall(StrArray *array, int start, int stop){
    if (stop - start){
        Word *pivot = getTheShortestWord(array->sequence[stop - 1]);
        int j = start - 1;
        for (int i = start; i < stop - 1; i++)
            if (getTheShortestWord(array->sequence[i])->size < pivot->size)
                swap(&array->sequence[i], &array->sequence[++j]);
        swap(&array->sequence[stop - 1], &array->sequence[++j]);
        recursiveCall(array, start, j);
        recursiveCall(array, ++j, stop);
    }
}


void quickSort(StrArray *array){
    recursiveCall(array, 0, array->size);
}


int main(){
    StrArray *array = getFilledStrArray();
    printf("\n");
    printArray(array);
    quickSort(array);
    printArray(array);
    for (int i = 0; i < array->size; i++)
        freeStr(array->sequence[i]);
    freeArray(array);
    return EXIT_SUCCESS;
}

