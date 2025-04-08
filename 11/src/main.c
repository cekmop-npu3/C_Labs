#include <eval.h>
  

int main(){
    const char *exp = "12*23+34*45-37";
    if (hasError(exp))
        return EXIT_FAILURE;
    Deque *postfix = infixToPostfix(exp);
    printDeque(postfix);
    freeDeque(postfix);
    printf("\n");
    return EXIT_SUCCESS;
}