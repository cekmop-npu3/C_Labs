#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


int getFib(int n){
    if (n <= 1)
        return n;
    return getFib(n - 1) + getFib(n - 2);
}


int getSequenceNum(int *num){
    int seqNum = 0;
    while (true){
        int fib = getFib(seqNum);
        if (*num < fib){
            seqNum = -1;
            break;
        }
        else if (*num != fib){
            seqNum += 1;
            continue;
        }
        break;
    }
    return seqNum + 1;
    
}


int main(){
    int num;

    printf("Enter the number from Fibonacci sequence: ");

    if (!scanf("%d", &num))
        assert(1 == 0);

    int seqNum = getSequenceNum(&num);
    
    if (seqNum != -1)
        printf("Sequence number is %d", seqNum);
    else
        printf("%d is not a number from Fibonacci sequence", num);
    return 0;
}
