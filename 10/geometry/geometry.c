#include <geometry.h>


Figure *createFigure(
    int square,
    const char *name,
    float perimeter,
    const char *color
){
    Figure *figure = malloc(sizeof(Figure));
    figure->square = square;
    figure->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(figure->name, name);
    figure->name[strlen(name)] = '\0';
    figure->perimeter = (Perimeter) {.num=perimeter};
    strncpy(figure->color, color, MaxStrSize - 1);
    figure->color[MaxStrSize - 1] = '\0';
    return figure;
}


void printFigure(Figure *figure){
    printf(
        "{square: %d, name: %s, perimeter: %.2f, color: %s}",
        figure->square, 
        figure->name, 
        figure->perimeter.num, 
        figure->color
    );
}


void freeFigure(Figure *figure){
    if (figure != NULL)
        free(figure->name);
    free(figure);
}
