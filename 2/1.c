#include <math.h>
#include <stdio.h>
#include <stdbool.h>


bool onCondition(int *num, int *digit1, int *digit2){
    return (*digit1 * (*digit1) + *digit2 * (*digit2) + 1) == 3 * (*digit1) * (*digit2) && (*num / (*digit1 + *digit2)) == 7 && (*num % (*digit1 + *digit2)) == 6 ? true : false; 
}


int searchForNum(){
    for (int i = 10; i < 100; i++){
        int digit1 = i/10;
        int digit2 = i - i/10*10;
        if (onCondition(&i, &digit1, &digit2)){
            return i;
        }
    }
    return 0;
}


int main(){
    int num = searchForNum();
    if (num){
        printf("Such number exists: %d", num);
    }
    else {
        printf("Such number has not been found");
    }
    return 0;
}