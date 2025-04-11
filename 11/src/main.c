#include <eval.h>
  

int main(){
    const char exp[] = "(-12+23)*5";
    if (hasError(exp))
        return EXIT_FAILURE;
    Deque *postfix = infixToPostfix(exp);
    Item *item = evalPostfix(postfix);
    printf("%.2f\n", *(double *) item->data);
    freeItem(item);
    freeDeque(postfix);
    return EXIT_SUCCESS;
}
