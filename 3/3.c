#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>


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


typedef struct {
    float elem;
    int count;
} Count;


typedef struct {
    Count *counters;
    size_t size;
} Counter;


void printCounter(Counter *counter){
    for (int i = 0; i < counter->size; i++){
        printf("elem: %.1f, count: %d\n", counter->counters[i].elem, counter->counters[i].count);
    }
}


bool inArray(Count countArray[], size_t *size, float *elem){
    for (int i = 0; i < *size; i++)
        if (*elem == countArray[i].elem){
            countArray[i].count++;
            return true;    
        }
    return false;
}


Counter count(float array[], size_t *size){
    Count counter;
    Count *countArray = calloc(*size, sizeof(Count));
    if (countArray == NULL)
        throwException("Cannot allocate memory", 1, array);
    size_t newSize = 0;
    for (int i = 0; i < *size; i++)
        if (!inArray(countArray, size, &(array[i]))){
            counter.count = 1;
            counter.elem = array[i];
            countArray[newSize] = counter;
            newSize++;
        }
    Counter result;
    result.counters = calloc(newSize, sizeof(Count));
    if (result.counters == NULL)
        throwException("Cannot allocate memory", 2, array, countArray);
    memcpy(result.counters, countArray, newSize * sizeof(Count));
    result.size = newSize;
    free(countArray);
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
    Counter result = count(array, &size);
    printCounter(&result);
    free(array);
    free(result.counters);
    return EXIT_SUCCESS;
}
