#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>


void throwException(char message[], size_t count, ...){
    if (count > 0){
        va_list args;
        va_start(args, count);
        for (int i = 0; i < count; i++){
            void *mem = va_arg(args, void*);
            free(mem);
        }
        va_end(args);
    }
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}


void printArray(float array[], size_t *size){
    for (int i = 0; i < *size; i++)
        printf("%.1f ", array[i]);
}


typedef struct {
    float *array;
    size_t size;
} Array;


bool inArray(float array[], size_t *size, float *elem){
    for (int i = 0; i < *size; i++)
        if (*elem == array[i])
            return true;
    return false;
}


Array set(float array[], size_t *size){
    float *tempArray = calloc(*size, sizeof(float));
    int index = 0;
    for (int i = 0; i < *size; i++){
        if (!inArray(tempArray, size, &(array[i]))){
            tempArray[index] = array[i];
            index++;
        }
    }
    Array result;
    result.array = calloc(index, sizeof(float));
    memcpy(result.array, tempArray, index * sizeof(float));
    result.size = index;
    free(tempArray);
    return result;
}


float *scanInput(size_t *size){
    printf("Enter the size of an array: ");
    if (!scanf("%zu", size))
        throwException("Incorrect size type", 0);
    float *array = calloc(*size, sizeof(float));
    if (array == NULL)
        throwException("Cannot allocate memory", 0);
    printf("Enter the array elements: ");
    for (int i = 0; i < *size; i++){
        if (!scanf("%f", &array[i]))
            throwException("Wrong element type", 1, array);
    }
    return array;
}


int main(){
    size_t size;
    float *array;
    array = scanInput(&size);
    Array result = set(array, &size);
    free(array);
    printArray(result.array, &result.size);
    free(result.array);
    return EXIT_SUCCESS;
}
