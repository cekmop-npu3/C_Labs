#include <eval.h>
#include <input.h>
  

int main(){
    Elem *elem = handle(typeDouble, NULL, "Some message: ");
    printf("%d\n", elem->type);
    freeElem(elem);
    return EXIT_SUCCESS;
}
