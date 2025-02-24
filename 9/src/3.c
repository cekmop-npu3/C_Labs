#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fileHandler.h>


typedef bool (*Lambda)(char *, char *);


bool greaterThan(char *str1, char *str2){
    return strlen(str1) > (str2 == NULL ? 0 : strlen(str2));
}

bool lessThan(char *str1, char *str2){
    return (str2 == NULL ? true : strlen(str1) < strlen(str2));
}


void getWord(char *filename, Lambda callable){
    FILE *file = fopen(filename, "r");
    char c;
    char *prev = NULL;
    char *word = NULL;
    bool inWord = true;
    int size = 0;
    while ((c = getc(file)) != EOF){
        c = (c == '\t' ? ' ' : c);
        if (c != ' '){
            if (inWord && size){
                word = realloc(word, ++size);
                word[size - 1] = '\0';
                if (callable(word, prev))
                    prev = realloc(word, size);
                word = NULL;
                size = 0;
            }
            word = realloc(word, ++size);
            word[size - 1] = c;
            inWord = false;
        }
        else
            inWord = true;
    }
    word = realloc(word, ++size);
    word[size - 1] = '\0';
    if (callable(word, prev))
        prev = realloc(word, size);
    printf("%s", prev);
    free(prev);
    free(word);
}



int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    getWord(filename, lessThan);
    return EXIT_SUCCESS;
}

