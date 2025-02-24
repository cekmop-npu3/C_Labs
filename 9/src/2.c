#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fileHandler.h>


void printIndexes(char *filename){
    FILE *file = fopen(filename, "r");
    char c;
    char *prev = NULL;
    char *word = NULL;
    bool inWord = true;
    int size = 0;
    int index = 1;
    while ((c = getc(file)) != EOF){
        c = (c == '\t' ? ' ' : c);
        if (c != ' '){
            if (inWord && size){
                word = realloc(word, ++size);
                word[size - 1] = '\0';
                if (index == 2)
                    printf("second: %s, ", word);
                prev = realloc(word, size);
                word = NULL;
                size = 0;
                index++;
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
    if (index == 2)
        printf("second: %s, ", word);
    if (prev != NULL)
        printf("pre-last: %s\n", prev);
    free(prev);
    free(word);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    printIndexes(filename);
    return EXIT_SUCCESS;
}

