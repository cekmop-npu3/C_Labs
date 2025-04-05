#include <eval.h>


static void printChar(void *data){
    printf("%c", *(char *) data);
}


static bool equal(Item *item1, Item *item2){
    return !strcmp(item1->meta, "char") && !strcmp(item2->meta, "char") && *(char *) item1->data == *(char *) item2->data;
}


static void setList(Deque *deque, const char list[]){
    for (int i = 0; i < deque->len; i++)
        freeItem(deque->sequence[i]);
    deque->len = 0;
    for (size_t j = 0; j < strlen(list); j++)
        append(deque, initItem((void *) &list[j], "char", printChar, NULL));
}


bool hasError(const char *exp){
    Deque *expectedValues = initDeque(17);
    setList(expectedValues, "0123456789-(");
    bool firstMinus = true;
    bool hasDot = false;
    int brackets[] = {0, 0};
    for (size_t j = 0; j < strlen(exp) + 1; (isspace(exp[j + 1]) ? j += 2 : j++)){
        if (!hasItem(expectedValues, initItem((void *) &exp[j], "char", printChar, NULL), equal)){
            if (j == strlen(exp) && (isdigit(exp[j - 1]) || exp[j - 1] == ')'))
                break;
            fprintf(stderr, "%s\n", exp);
            for (size_t i = 0; i < strlen(exp) + 1; i++)
                i == j ? fprintf(stderr, "^") : fprintf(stderr, "=");
            fprintf(stderr, "\n[SyntaxError] Invalid character at pos %ld\n", j);
            freeDeque(expectedValues);
            return true;
        }
        if (isdigit(exp[j]) && !(firstMinus = false))
            hasDot ? setList(expectedValues, "0123456789+-*/)") : setList(expectedValues, "0123456789.+-*/)");
        else if (exp[j] == '.' && (hasDot = true))
            setList(expectedValues, "0123456789");  
        else if (exp[j] == '(' && (firstMinus = true) && ++brackets[0])
            setList(expectedValues, "0123456789-(");
        else if (exp[j] == ')' && !(hasDot = false) && ++brackets[1])
            setList(expectedValues, "+-*/)");
        else 
            !(hasDot = false) && firstMinus ? setList(expectedValues, "0123456789") : setList(expectedValues, "0123456789(");
    }
    freeDeque(expectedValues);
    if (brackets[0] != brackets[1])
        return (bool) fprintf(stderr, "[SyntaxError] Brackets count does not match\n");
    return false;
}


