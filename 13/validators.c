#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>


int getValidatedIntInput(const char *message)
{
    while (1)
    {
        printf("%s", message);
        int input = 0;
        char a;
        int isAnyErrorsInInput = 0;
        int valueLen = 0;
        short sign = 1;
        int rawBufferLen = 0;
        while ((a = getchar()) != '\n')
        {
            if(tolower(a) == 'q') {
                while((getchar()) != '\n');
                return INT_MIN;
            }
            rawBufferLen++;
            if(valueLen == 0 && a == '-')
            {
                sign = -1;
                valueLen++;
                continue;
            }
            if(a < '0' || a > '9')
            {
                isAnyErrorsInInput = 1;
                break;
            }
            else
            {
                if (sign == 1 && input > (INT_MAX - '0') / 10) {
                    isAnyErrorsInInput = 1;
                    break;
                }
                if (sign == -1 && input < (INT_MIN + '0') / 10) {
                    isAnyErrorsInInput = 1;
                    break;
                }
                valueLen++;
                input = input * 10 + (a-'0');
            }
        }
        if(sign == -1 && valueLen == 1)
        {
            isAnyErrorsInInput = 1;
            rawBufferLen--;
        }
        if(!isAnyErrorsInInput && valueLen)
        {
            return input * sign;
        }
        else {
            input = 0;
            printf("Incorrect input \n");
        }
        if(rawBufferLen > 0 && isAnyErrorsInInput)
        {
            while((getchar()) != '\n');
        }
    }
    
}

char getValidatedCharInputE(const char *message, char validChars[], int validCharsLength) {
    char input;
    while (1) {
        printf("%s", message);
        if (scanf(" %c", &input) == 1) {
            bool hasInvalidExtra = false;
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (!isspace(c)) {
                    hasInvalidExtra = true;
                }
            }
            
            if (hasInvalidExtra) {
                printf("Invalid input. Please enter exactly one character.\n");
                continue;
            }
        
            
            if (validCharsLength == 0) {
                return input;
            } else {
                for (int i = 0; i < validCharsLength; i++) {
                    if (input == toupper(validChars[i])) {
                        return input;
                    }
                }
                printf("Invalid input. Please enter one of the following characters: ");
                for (int i = 0; i < validCharsLength; i++) {
                    printf("%c ", validChars[i]);
                }
                printf("\n");
            }
        } else {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a single character.\n");
        }
    }
}

char getValidatedCharInput(const char *message, char validChars[], int validCharsLength)
{
    if(validCharsLength < 2) return 'M';
    char input;
    while (1) 
    {
        printf("%s", message);
        if (scanf(" %c", &input) == 1) 
        {
            input = toupper(input);  
            for (int i = 0; i < validCharsLength; i++) 
            {
                if (input == toupper(validChars[i])) 
                {
                    while (getchar() != '\n');
                    return input;
                }
            }
        }
        printf("Invalid input. Please enter one of the following characters: ");
        for (int i = 0; i < validCharsLength; i++) 
        {
            printf("%c ", validChars[i]);
        }
        printf("\n");
        while (getchar() != '\n');  
    }
}