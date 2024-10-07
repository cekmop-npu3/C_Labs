#include <stdio.h>
#include <stdbool.h>


bool isArithmeticProgression(int *a, int *b, int *c){
    return (*b == (*a + *c) / 2);
}


void scanNums(char name[], int *num){
    printf("Enter the %s number: ", name);
    scanf("%d", num);
}


int main(){
    int num1, num2, num3;

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