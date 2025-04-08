#include <eval.h>
  

int main(){
    const char *exp = "(12.34 + 13.01)()";
    if (hasError(exp))
        return EXIT_FAILURE;
    Deque *postfix = infixToPostfix(exp);
    printDeque(postfix);
    printf("\n");
    printf("Result: %.2f\n", evalPostfix(postfix));
    freeDeque(postfix);
    return EXIT_SUCCESS;
}