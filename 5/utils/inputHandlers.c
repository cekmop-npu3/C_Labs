#include "inputHandlers.h"


void handleIntInput(int *num, int range[2], char *message, ...){
    char error[MaxStrLen + 25] = "Wrong input, try again.\n";
    if (message != NULL){
        char tmpString[MaxStrLen * 2];
        va_list args;
        va_start(args, message);
        vsnprintf(tmpString, MaxStrLen, message, args);
        va_end(args);
        printf("%s", tmpString);
        strcat(error, tmpString);
    }

    char c;
    *num = 0;
    char *res = NULL;
    int size = 0;
    int sign = 1;

    while (!((c = getchar()) == '\n' && size)){
        if (c == '-' && sign == 1 && !size){
            sign = -1;
            continue;
        }
        if (isdigit(c)){
            res = realloc(res, ++size * sizeof(char));
            res[size - 1] = c;
            continue;
        }
        ungetc(c, stdin);
        while (getchar() != '\n');
        free(res);
        printf("%s", error);
        *num = 0;
        char *res = NULL;
        int size = 0;
        int sign = 1;
    }
    for (int i = size; i > 0; i--)
        *num += pow(10, i - 1) * (res[size - i] - '0');
    free(res);
    *num *= sign;
    if (range != NULL && !(*num >= range[0] && *num <= range[1])){
        printf("%s", error);
        handleIntInput(num, range, message);
    }
}
