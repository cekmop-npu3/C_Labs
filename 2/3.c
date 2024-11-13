#include <stdio.h>
#include <stdbool.h>


int getFib(int n) {
    if (n < 1)
        return -1;
    if (n == 1 || n == 2)
        return 1;
    else
        return getFib(n - 1) + getFib(n - 2);
}


int getSeqNum(int num){
    int seqNum = 1;
    while (true){
        if (getFib(seqNum) == num)
            break;
        else if (getFib(seqNum) > num){
            seqNum = -1;
            break;
        }
        seqNum++;
    }
    return seqNum;
}


int main(){
    int num;
    do {
        printf("Enter the number from Fibonacci sequence: ");
        if (!scanf("%d", &num)){
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        break;

    }
    while (true);

    int seqNum = getSeqNum(num);
    if (seqNum == -1)
        printf("%d is not a number from Fibonacci sequence", num);
    else 
        printf("Sequence number is %d", seqNum);

    return 0;
}
