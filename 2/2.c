#include <stdio.h>
#include <stdbool.h>


void scanNum(char name[], int *num){
    do {
        printf("Enter the %s number: ", name);
        if (!scanf("%d", num)){
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        break;
    }
    while (true);
}


double calculateSum(int *num1, int *num2){
    double sum = 0.0;
    for (int i = 0; i <= *num2; i++){
        sum += 1.0 / (*num1 + i);
    }
    return sum;
}


int main(){
    int num1, num2;

    scanNum("first", &num1);
    scanNum("second", &num2);
    printf("%f", calculateSum(&num1, &num2));
}

