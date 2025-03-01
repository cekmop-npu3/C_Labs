#include <stdio.h>
#include <stdlib.h>

#include "utils/fileHandler.h"


typedef enum {
    Max,
    Min
} Mode;


int getElem(char *filename, Mode mode){
    FILE *file = fopen(filename, "rb");
    int elem, nextElem;
    fread(&elem, sizeof(int), 1, file);
    while (fread(&nextElem, sizeof(int), 1, file))
        if (mode ? nextElem < elem : nextElem > elem)
            elem = nextElem;
    fclose(file);
    return elem;
}


int getMaxCount(char *filename, int maxElem){
    FILE *file = fopen(filename, "rb");
    int elem;
    int count = 0;
    while (fread(&elem, sizeof(int), 1, file))
        if (elem == maxElem)
            count++;
    return count;
}


void replaceMaxWithMin(char *filename, int max, int min){
    FILE *file = fopen(filename, "rb+");
    fseek(file, 0, SEEK_END);
    int len = ftell(file) / sizeof(int);
    rewind(file);
    int elem;
    for (int i = 0; i < len; i++){
        fread(&elem, sizeof(int), 1, file);
        if (elem == max){
            fseek(file, sizeof(int) * i, SEEK_SET);
            fwrite(&min, sizeof(int), 1, file);
            fseek(file, sizeof(int) * (i + 1), SEEK_SET);
        }
    }
    rewind(file);
    while (fread(&elem, sizeof(int), 1, file))
        printf("%d ", elem);
    printf("\n");
    fclose(file);
}


void selectionSortWithCondition(char *filename){
    FILE *file = fopen(filename, "rb+");
    fseek(file, 0, SEEK_END);
    int len = ftell(file) / sizeof(int);
    rewind(file);
    int elem, indexElem;
    int index = 0;
    start:
    fseek(file, sizeof(int) * index, SEEK_SET);
    int res = fread(&indexElem, sizeof(int), 1, file);
    fseek(file, sizeof(int) * index, SEEK_SET);
    if (indexElem < 0 && res){
        ++index;
        goto start;
    }
    for (int i = index; i < len; i++){
        fread(&elem, sizeof(int), 1, file);
        if (elem >= 0 && (elem < indexElem)){
            fileSwap(file, i, index);
            fseek(file, sizeof(int) * i, SEEK_SET);
            indexElem = elem;
        }
    }
    if (++index < len)
        goto start;
    rewind(file);
    while (fread(&elem, sizeof(int), 1, file))
        printf("%d ", elem);
    printf("\n");
    fclose(file);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    int max = getElem(filename, Max);
    int min = getElem(filename, Min);
    printf("Max elem count: %d\n", getMaxCount(filename, max));
    replaceMaxWithMin(filename, max, min);
    selectionSortWithCondition(filename);
    return EXIT_SUCCESS;
}