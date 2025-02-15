#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <inputHandler.h>


char *setFilename(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Provide correct filename");
        return NULL;
    }
    return strstr(argv[1], ".bin") == NULL ? strcat(argv[1], ".bin") : argv[1];
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    Array *array = initArray();
    userInput(array);
    printArray(array);
    free(array);
    return EXIT_SUCCESS;
}
