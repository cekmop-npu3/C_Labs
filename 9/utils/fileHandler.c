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
