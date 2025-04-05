#include <eval.h>


void printInt(void *data){
    printf("%d", *(int *) data);
}

void printString(void *data){
    printf("%s", (char *) data);
}
  

int main(){
    infixToPostfix("(-12+(((23*45)-23");
}