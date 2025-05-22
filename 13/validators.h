#ifndef VALIDATORS_H
#define VALIDATORS_H


int getValidatedIntInput(const char *message);

char getValidatedCharInput(const char *message, char validChars[], int validCharsLength);

char getValidatedCharInputE(const char *message, char validChars[], int validCharsLength);


#endif