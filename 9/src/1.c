#include <stdio.h>
#include <stdlib.h>

#include <fileHandler.h>


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    return EXIT_SUCCESS;
}