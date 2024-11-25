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
    do {
        if (scanf("%d", num)){
            if (range != NULL){
                if (*num >= range[0] && *num <= range[1]){
                    while (getchar() != '\n');
                    break;
                }
            }
            else {
                while (getchar() != '\n');
                break;
            }
        }
        printf("%s", error);
        while (getchar() != '\n');
    }
    while (true);
}
