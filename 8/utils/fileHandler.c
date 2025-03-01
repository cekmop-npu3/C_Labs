#include "fileHandler.h"


char *setFilename(int argc, char *argv[]){
    if (argc != 2 || strpbrk("./\\\\<>:", argv[1])){
        fprintf(stderr, "Provide correct filename");
        return NULL;
    }
    return strstr(argv[1], ".bin") == NULL ? strcat(argv[1], ".bin") : argv[1];
}


void fileInput(char *filename){
    FILE *file = fopen(filename, "wb+");
    Elem *len;
    int range[2] = {0, INT_MAX};
    do {
        if ((len = input("Enter the number of elements: ")) != NULL && len->type == typeInt && (range == NULL || (len->value.Int > range[0] && len->value.Int < range[1])))
            break;
        printf("Wrong input, try again\n");
    } while (true);
    Elem *elem;
    for (int i = 0; i < len->value.Int; i++)
        do {
            if ((elem = input("Enter the element [%d]: ", i)) != NULL && elem->type == typeInt){
                fwrite(&(elem->value.Int), sizeof(int), 1, file);
                break;
            }
            printf("Wrong input, try again\n");
        } while (true);
    rewind(file);
    while (fread(&(elem->value.Int), sizeof(int), 1, file))
        printf("%d ", elem->value.Int);
    printf("\n");
    fclose(file);
}


void fileSwap(FILE *file, int index, int swapIndex){
    int elem, swapElem;
    bool toWrite = false;
    bool exit = false;
    while (!exit){
        fseek(file, index * sizeof(int), SEEK_SET);
        toWrite ? fwrite(&swapElem, sizeof(int), 1, file) : fread(&elem, sizeof(int), 1, file);
        fseek(file, swapIndex * sizeof(int), SEEK_SET);
        toWrite ? (fwrite(&elem, sizeof(int), 1, file), exit = true) : (fread(&swapElem, sizeof(int), 1, file), toWrite = true);
    }
}
