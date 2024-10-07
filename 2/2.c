#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdbool.h>


bool scanNum(char name[], int *num){
    printf("Enter the %s number: ", name);
    int check = scanf("%d", num);
    assert(*num < INT_MAX && *num > INT_MIN);
    return check;
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

    if (!scanNum("first", &num1) || !scanNum("second", &num2))
        assert(1 == 0);
    printf("%f", calculateSum(&num1, &num2));
}

