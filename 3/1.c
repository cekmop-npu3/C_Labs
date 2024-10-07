#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


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


float max(float array[], size_t *size){
    float maxFloat = array[0];
    for (int i = 1; i < *size; i++){
        if (maxFloat < array[i])
            maxFloat = array[i];
    }
    return maxFloat;
}


float positiveNumSum(float array[], size_t *size){
    int count = 0;
    float sum = 0.0;
    for (int i = 1; i < *size - 1; i++){
        if (count < 2){
            if (array[i] > 0){
                sum += array[i - 1] + array[i + 1];
                count++;
            }  
        }
        else {
            break;
        }
    }
    return sum;
}


int main(){
    size_t size;
    float *array;
    printf("Enter the size of an array: ");
    if (!scanf("%zu", &size))
        throwException("Incorrect size type", 0);
    array = calloc(size, sizeof(float));
    printf("Enter the array elements: ");
    for (int i = 0; i < size; i++){
        if (!scanf("%f", &array[i]))
            throwException("Wrong element type", 1, array);
    }
    printf("Max element of an array: %.1f\n", max(array, &size));
    printf("Sum of first two positive numbers: %.1f\n", positiveNumSum(array, &size));
    free(array);
    return EXIT_SUCCESS;
}

