#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fileHandler.h>


void sort(char *filename){
    FILE *file = fopen(filename, "rb+");
    fseek(file, 0, SEEK_END);
    int len = ftell(file) / sizeof(int);
    rewind(file);
    int indexes[2] = {1, 4};
    shiftFromIndexes(file, shiftLeft, indexes);
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

