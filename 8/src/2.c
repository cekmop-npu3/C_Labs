#include <stdio.h>
#include <stdlib.h>

#include <fileHandler.h>


void printLongestSequence(char *filename){
    FILE *file = fopen(filename, "rb");
    int elem, nextElem;
    int main[2] = {0, 0};
    int temp[2] = {0, 0};
    fread(&elem, sizeof(int), 1, file);
    while (fread(&nextElem, sizeof(int), 1, file)){
        if (elem != nextElem){
            if ((temp[1] - temp[0]) > (main[1] - main[0]))
                memcpy(main, temp, sizeof(int) * 2);
            elem = nextElem;
            temp[0] = ++temp[1];
        }
        else
            temp[1]++;
    }
    if ((temp[1] - temp[0]) > (main[1] - main[0]))
        memcpy(main, temp, sizeof(int) * 2);
    fseek(file, main[0] * sizeof(int), SEEK_SET);
    while (fread(&elem, sizeof(int), 1, file))
        printf("%d ", elem);
    fclose(file);
}


int main(int argc, char *argv[]){
    char *filename = setFilename(argc, argv);
    if (filename == NULL)
        return EXIT_FAILURE;
    fileInput(filename);
    printLongestSequence(filename);
    return EXIT_SUCCESS;
}

