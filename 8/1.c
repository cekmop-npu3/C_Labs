#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/inputHandler.h"


int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Provide correct filename");
        return EXIT_FAILURE;
    }
    char *filename = argv[1];
    if (strstr(filename, ".bin") == NULL)
        strcat(filename, ".bin");
    Elem *elem = input("Enter the number: ");
    if (elem->type != typeInt){
        fprintf(stderr, "Wrong input");
        freeElem(elem);
    }
    FILE *file = fopen(filename, "wb+");
    fwrite(&(elem->value.Int), sizeof(int), 1, file);
    rewind(file);
    int num;
    fread(&num, sizeof(int), 1, file);
    printf("%d", num);
    freeElem(elem);
    fclose(file);
    return EXIT_SUCCESS;
}
