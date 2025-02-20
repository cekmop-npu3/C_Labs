#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fileHandler.h>


bool onEven(int elem){
    return !(elem % 2) && elem;
}

bool onZero(int elem){
    return !elem;
}


typedef bool (*Lambda)(int);


int shift(FILE *file, int shiftIndex, Lambda condition){
    int elem;
    fseek(file, 0, SEEK_END);
    int len = ftell(file) / sizeof(int);
    rewind(file);
    for (int i = shiftIndex; i < len; i++){
        fseek(file, i * sizeof(int), SEEK_SET);
        fread(&elem, sizeof(int), 1, file);
        if (condition(elem)){
            int bound[2] = {shiftIndex, i};
            for (int j = 0; j < (i - shiftIndex); j++)
                shiftFile(file, shiftLeft, bound);
            shiftIndex++;
        }
    }
    return shiftIndex;
}


void sort(char *filename){
    FILE *file = fopen(filename, "rb+");
    shift(file, shift(file, 0, onEven), onZero);
    rewind(file);
    int elem;
    while (fread(&elem, sizeof(int), 1, file))
        printf("%d ", elem);
    fclose(file);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    sort(filename);
    return EXIT_SUCCESS;
}

