#include <eval.h>
  

int main(){
    if (hasError("3.14*(2+1.5)+34"))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}