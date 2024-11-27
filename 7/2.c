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
        str->raw = realloc(str->raw, ++str->size * sizeof(char));
        str->raw[str->size - 1] = c;
        c = (c == '\t' ? ' ' : c);
        if (c != ' '){
            if (splited){
                str->words = realloc(str->words, ++str->len * sizeof(Word *));
                str->words[str->len - 1] = NULL;
                str->words[str->len - 1] = realloc(str->words[str->len - 1], sizeof(Word));
                str->words[str->len - 1]->size = 0;
                str->words[str->len - 1]->value = malloc(sizeof(char));
                str->words[str->len - 1]->value[str->words[str->len - 1]->size++] = c;
            }
            else {
                str->words[str->len - 1]->value = realloc(str->words[str->len - 1]->value, ++str->words[str->len - 1]->size * sizeof(char));
                str->words[str->len - 1]->value[str->words[str->len - 1]->size - 1] = c;
            }
            splited = false;
        }
        else
            splited = true;
    }
    str->raw = realloc(str->raw, str->size + 1); 
    str->raw[str->size] = '\0';
    for (int i = 0; i < str->len; i++){
        str->words[i]->value = realloc(str->words[i]->value, str->words[i]->size + 1);
        str->words[i]->value[str->words[i]->size] = '\0';
    }
    return str;
}


// void removeFromWords(Str *str, Word *word){
//     int newArrIndex = 0;
//     bool removed = false;
//     int j = 0;
//     bool start = false;
//     for (int i = 0; i < str->len; i++){
//         if (word->size <= str->words[i])
//             for (j; j < word->size; j++)
//                 if (word->value[j] == str->words[j]->value)
//                     s
//         printf("%s %s\n", str->words[i]->value, word->value);
//         if ((str->words[i]->value != word->value) || removed){
//             str->words[newArrIndex] = str->words[i];
//             newArrIndex++;
//             continue;
//         }
//         printf("was removed\n");
//         removed = true;
//     }
//     if (removed)
//         str->words = realloc(str->words, --str->len);
// }


void removeFromRaw(Str *str, Word *word){
    int startIndex = -1;
    int endIndex;
    int j = 1;
    for (int i = 0; i < str->size; i++)
        if (str->raw[i] == word->value[0]){
            for (j; j < word->size; j++)
                if (str->raw[i + j] != word->value[j])
                    break;
            if (j == word->size){
                startIndex = i;
                endIndex = startIndex + word->size;
                break;
            }
        }
    if (startIndex != -1){
        for (int i = endIndex; i < str->size; i++)
            str->raw[i - word->size] = str->raw[i];
        str->raw = realloc(str->raw, (str->size -= word->size) + 1);
        str->raw[str->size] = '\0';
    }
}


int main(){
    Str *str = getStr("Enter the first string: ");
    printf("\n");
    Str *str2 = getStr("Enter the second string: ");
    printf("\n");
    //removeFromWords func is not working properly
    removeFromWords(str, str2->words[0]);
    //removeFromRaw(str, str2->words[0]);
    for (int i = 0; i < str->len; i++)
        printf("{%s %d}", str->words[i]->value, str->words[i]->size);
    //printf("%s", str->raw);
    return EXIT_SUCCESS;
}

