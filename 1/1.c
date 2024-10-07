#include <stdio.h>
#include <math.h>
#include <string.h>


typedef struct {
    float x;
    float y;
} Point;


float distance(Point *firstPoint, Point *secondPoint){
    return sqrt(pow(firstPoint->x - secondPoint->x, 2) + pow(firstPoint->y - secondPoint->y, 2));
}


float trianglePerimeter(Point *point1, Point *point2, Point *point3){
    return distance(point1, point2) + distance(point2, point3) + distance(point1, point3);
}


void scanPoint(char name[], Point *point){
    printf("Enter the %s point coordinates\n", name);
    printf("(float) X: ");
    scanf("%f", &(*point).x);
    printf("(float) Y: ");
    scanf("%f", &point->y);
}


int main(){
    Point point1, point2, point3;

    scanPoint("first", &point1);
    scanPoint("second", &point2);
    scanPoint("third", &point3);

    printf("The perimeter is %f", trianglePerimeter(&point1, &point2, &point3));

    return 0;
}
