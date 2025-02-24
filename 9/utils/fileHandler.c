#include <fileHandler.h>


char *setFilename(int argc, char *argv[]){
    if (argc != 2 || strpbrk("./\\\\<>:", argv[1])){
        fprintf(stderr, "Provide correct filename");
        return NULL;
    }
    return strstr(argv[1], ".txt") == NULL ? strcat(argv[1], ".txt") : argv[1];
}


void fileInput(char *filename){
    FILE *file = fopen(filename, "w+");
    char c;
    char string[MaxStrSize];
    printf("Enter the string: ");
    while ((c = getchar()) != '\n')
        putc(c, file);
    rewind(file);
    fgets(string, MaxStrSize, file);
    printf("%s\n", string);
    fclose(file);
}


void fileSwap(FILE *file, int index, int swapIndex){
    char elem, swapElem;
    bool toWrite = false;
    bool exit = false;
    while (!exit){
        fseek(file, index * sizeof(char), SEEK_SET);
        toWrite ? fwrite(&swapElem, sizeof(char), 1, file) : fread(&elem, sizeof(char), 1, file);
        fseek(file, swapIndex * sizeof(char), SEEK_SET);
        toWrite ? (fwrite(&elem, sizeof(char), 1, file), exit = true) : (fread(&swapElem, sizeof(char), 1, file), toWrite = true);
    }
}

void shiftFile(FILE *file, ShiftType type, int bound[2]){
    int elem, prev;
    fseek(file, 0, SEEK_END);
    int indexes[2] = {bound == NULL ? 0 : bound[0], bound == NULL ? ftell(file) / sizeof(char) - 1 : bound[1]};
    int index = (type ? indexes[1] : indexes[0]);
    fseek(file, (type ? indexes[0] : indexes[1]) * sizeof(char), SEEK_SET);
    fread(&prev, sizeof(char), 1, file);
    for (index; (type ? index >= indexes[0] : index < indexes[1] + 1); (index += (1 - 2 * type))){
        fseek(file, index * sizeof(char), SEEK_SET);
        fread(&elem, sizeof(char), 1, file);
        fseek(file, index * sizeof(char), SEEK_SET);
        fwrite(&prev, sizeof(char), 1, file);
        prev = elem;
    }
}


// qwerty qwe ui
// uierty qwe qw

// qwe rty qwerty uio  fgh p asd
// qwe rty p uio  fgh qwerty asd

// ui qwe qwerty
// 

// qwerty qwe ui - ui qwe qwerty
// uierty qwe qw
// 

