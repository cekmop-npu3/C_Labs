#include <stdio.h>
#include <stdbool.h>


void scanSide(char name[], int *side){
    printf("Enter the %s side: ", name);
    scanf("%d", side);
}


bool isEquilateral(int *side1, int *side2, int *side3){
    return (*side1 == *side2) && (*side2 == *side3);
}


int main(){
    int side1, side2, side3;

    scanSide("first", &side1);
    scanSide("second", &side2);
    scanSide("third", &side3);

    if (isEquilateral(&side1, &side2, &side3)){
        printf("This triangle is equilateral");
    }
    else {
        printf("This triangle is not equilateral");
    }

    return 0;
}
