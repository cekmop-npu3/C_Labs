#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <fileHandler.h>


typedef bool (*Lambda)(int *bound1, int *bound2);


bool greaterThan(int bound1[2], int bound2[2]){
    return (bound1[1] - bound1[0]) > (bound2[1] - bound2[0]);
}

bool lessThan(int bound1[2], int bound2[2]){
    return (!bound2[0] && !bound2[1] ? true : (bound1[1] - bound1[0]) < (bound2[1] - bound2[0]));
}


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
    rewind(file);
}


int *getWord(char *filename, Lambda callable){
    FILE *file = fopen(filename, "r");
    char c;
    bool inWord = true;
    int size = 0;
    int *prev = malloc(sizeof(int) * 2);
    prev[0] = 0;
    prev[1] = 0;
    int word[2] = {0, 0};
    while ((c = getc(file)) != EOF){
        c = (c == '\t' ? ' ' : c);
        if (c != ' '){
            if (inWord && (word[1] - word[0])){
                if (callable(word, prev))
                    memcpy(prev, word, sizeof(int) * 2);
                word[0] = word[1];
            }
            inWord = false;
        }
        else
            inWord = true;
        word[1]++;
    }
    if (callable(word, prev)){
        memcpy(prev, word, sizeof(int) * 2);
    }
    else
        --prev[1];
    fclose(file);
    return prev;
}


void swapWords(char *filename, int *bound1, int *bound2){
    FILE *file = fopen(filename, "r+");
    char string[MaxStrSize];
    int len1 = bound1[1] - bound1[0];
    int len2 = bound2[1] - bound2[0];
    int index = 0;
    for (index; index < (len1 > len2 ? len2 : len1); index++)
        fileSwap(file, bound1[0] + index, bound2[0] + index);
    int ranged[2] = {bound2[0] > bound1[0] ? bound1[0] + index: bound2[0] + index, bound2[0] > bound1[0] ? bound2[1] - 1: bound1[1] - 1};
    for (int i = 0; i < (len1 < len2 ? len2 : len1) - index; i++)
        shiftFile(file, ((len1 < len2) && (bound1[0] < bound2[0]) ? shiftRight : shiftLeft), ranged);
    rewind(file);
    fgets(string, MaxStrSize, file);
    printf("%s\n", string);
    fclose(file);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    printIndexes(filename);
    int *shortStr = getWord(filename, lessThan);
    int *longStr = getWord(filename, greaterThan);
    swapWords(filename, shortStr, longStr);
    free(shortStr);
    free(longStr);
    return EXIT_SUCCESS;
}


