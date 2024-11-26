#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

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


void freeStr(Str *str){
    free(str->raw);
    for (int i = 0; i < str->len; i++){
        free(str->words[i]->value);
        free(str->words[i]);
    }
    free(str->words);
    free(str);
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
    return str;
}


int main(){
    Str *str = getStr("Enter string: ");
    printf("\n");
    for (int i = 0; i < str->len; i++)
        printf("%s ", str->words[i]->value);
    printf("\n");
    for (int i = 0; i < str->len; i++)
        printf("%d ", str->words[i]->size);
    freeStr(str);
    return EXIT_SUCCESS;
}

