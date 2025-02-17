#include <stdio.h>
#include <stdlib.h>

#include <fileHandler.h>


void zeroOutEvenIndexes(char *filename){
    FILE *file = fopen(filename, "rb+");
    fseek(file, 0, SEEK_END);
    int len = ftell(file) / sizeof(int);
    rewind(file);
    int elem = 0;
    for (int i = 0; i < len; i++)
        if (!(i % 2)){
            fseek(file, i * sizeof(int), SEEK_SET);
            fwrite(&elem, sizeof(int), 1, file);
        }
    rewind(file);
    while (fread(&elem, sizeof(int), 1, file))
        printf("%d ", elem);
    fclose(file);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    zeroOutEvenIndexes(filename);
    return EXIT_SUCCESS;
}

