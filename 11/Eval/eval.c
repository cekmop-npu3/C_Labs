#include <eval.h>
#include <ctype.h>


// static int orderOfOperation(char c){
//     switch (c){
//         case '(':
//         case ')':
//             return 3;
//         case '*':
//         case '/':
//             return 2;
//         case '+':
//         case '-':
//             return 1;
//         default:
//             return 0;
//     }
// }


void printChar(void *data){
    printf("%c", *(char *) data);
}


bool equal(Item *item1, Item *item2){
    return !strcmp(item1->meta, "char") && !strcmp(item2->meta, "char") && *(char *) item1->data == *(char *) item2->data;
}


void setList(Deque *deque, const char list[]){
    for (int i = 0; i < deque->len; i++)
        freeItem(deque->sequence[i]);
    deque->len = 0;
    for (size_t j = 0; j < strlen(list); j++)
        append(deque, initItem((void *) &list[j], "char", printChar, NULL));
}


Deque *infixToPostfix(const char *exp){
    Deque *expectedValues = initDeque(20);
    setList(expectedValues, "0123456789-(");
    bool firstMinus = true;
    bool hasDot = false;
    for (size_t j = 0; j < strlen(exp); (isspace(exp[j]) ? (++j && j++) : j++)){
        printDeque(expectedValues);
        printf("\n");
        if (!hasItem(expectedValues, initItem((void *) &exp[j], "char", printChar, NULL), equal)){
            fprintf(stderr, "%s\n", exp);
            for (size_t i = 0; i < strlen(exp); i++)
                i == j ? fprintf(stderr, "^") : fprintf(stderr, "=");
            fprintf(stderr, "\n[SyntaxError] Invalid character at pos %ld\n", j);
            freeDeque(expectedValues);
            return NULL;
        }
        if (isdigit(exp[j]) && !(firstMinus = false))
            hasDot ? setList(expectedValues, "0123456789+-*/)") : setList(expectedValues, "0123456789.+-*/)");
        else if (exp[j] == '.' && (hasDot = true))
            setList(expectedValues, "0123456789");  
        else if (exp[j] == '(' && (firstMinus = true))
            setList(expectedValues, "0123456789-(");
        else if (exp[j] == ')' && !(hasDot = false))
            setList(expectedValues, "+-*/");
        else {
            firstMinus ? setList(expectedValues, "0123456789") : setList(expectedValues, "0123456789(");
            hasDot = false;
        }
            
    }
    freeDeque(expectedValues);
    return NULL;
}


