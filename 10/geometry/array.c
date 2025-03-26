#include <array.h>


Array *initArray(){
    Array *array = malloc(sizeof(Array));
    array->size = 0;
    array->figures = NULL;
    return array;
}


bool addFigure(Array *array, Figure *figure){
    array->figures = realloc(array->figures, ++array->size * sizeof(Figure *));
    array->figures[array->size - 1] = figure;
    return true;
}


bool removeFigures(Array *array, Key key, void *data){
    if (!array->size)
        return false;
    Figure **figures = NULL;
    int index = 0;
    for (int i = 0; i < array->size; i++){
        if (key(array->figures[i], data))
            free(array->figures[i]);
        else {
            figures = realloc(figures, sizeof(Figure *) * ++index);
            figures[index - 1] = array->figures[i];
        }
    }
    free(array->figures);
    array->figures = figures;
    array->size = index;
    return true;
}


Array *findFigures(Array *array, Key key, void *data){
    Array *tmpArray = initArray();
    for (int i = 0; i < array->size; i++)
        if (key(array->figures[i], data))
            addFigure(tmpArray, array->figures[i]);
    return tmpArray;
}


void freeArray(Array *array){
    if (array != NULL){
        for (int i = 0; i < array->size; i++)
            free(array->figures[i]);
        free(array->figures);
    }
    free(array);
}


void printArray(Array *array){
    printf("[");
    for (int i = 0; i < array->size; i++){
        printFigure(array->figures[i]);
        printf(", ");
    }
    printf("]\n");
}
