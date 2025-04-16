#include <file.h>


void freeLines(Lines *lines){
    for (int i = 0; i < lines->len; i++)
        free(lines->lines[i]);
    free(lines->lines);
    free(lines);
}


void printLines(Lines *lines){
    for (int i = 0; i < lines->len; i++)
        printf("%s\n", lines->lines[i]);
}


Lines *readLines(const char *filename){
    char c;
    char **tmpLines;
    Lines *lines = malloc(sizeof(Lines));
    if (lines == NULL){
        fprintf(stderr, "Memory allocation error at readLines\n");
        return NULL;
    }
    lines->len = 0;
    lines->lines = NULL;
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        fprintf(stderr, "Error occured opening file %s\n", filename);
        freeLines(lines);
        return NULL;
    }
    while (fread(&c, sizeof(char), 1, file)){
        if (c == '\n' || (!lines->len && !fseek(file, 0, SEEK_SET))){
            if ((((tmpLines = realloc(lines->lines, sizeof(char *) * ++lines->len)) == NULL) | ((tmpLines[lines->len - 1] = malloc(sizeof(char) * MaxStrSize)) == NULL)) | ((bool) (lines->lines = tmpLines) && (lines->lines[lines->len - 1][0] = '\0'))){
                freeLines(lines);
                fprintf(stderr, "Memory allocation error at readLines\n");
                return NULL;
            }
        }
        else {
            if (strlen(lines->lines[lines->len - 1]) + 1 != MaxStrSize){
                lines->lines[lines->len - 1][strlen(lines->lines[lines->len - 1]) + 1] = '\0';
                lines->lines[lines->len - 1][strlen(lines->lines[lines->len - 1])] = c;
            }
            else {
                while (fread(&c, sizeof(char), 1, file) && c != '\n');
                ungetc('\n', file);
            }
        }
    }
    return lines;
}
