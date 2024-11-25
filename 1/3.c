#include <stdio.h>
#include <stdbool.h>


bool isArithmeticProgression(float *a, float *b, float *c){
    return (*b == (*a + *c) / 2);
}


void scanNums(char name[], float *num){
    printf("Enter the %s number: ", name);
    scanf("%f", num);
}


int main(){
    float num1, num2, num3;

    scanNums("first", &num1);
    scanNums("second", &num2);
    scanNums("third", &num3);

    if (isArithmeticProgression(&num1, &num2, &num3)){
        printf("These nums make up an arithmetic progression");
    }
    else {
        printf("Ain't no arithmetic progression here");
    }

    return 0;
}