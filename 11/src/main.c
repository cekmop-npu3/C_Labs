#include <eval.h>
  

int main(){
    const char *exp = "(13+34)*12";
    if (hasError(exp))
        return EXIT_FAILURE;
    Deque *postfix = infixToPostfix(exp);
    printDeque(postfix);
    freeDeque(postfix);
    printf("\n");
    return EXIT_SUCCESS;
}