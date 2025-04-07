#include <eval.h>


static int priority(char c){
    switch (c){
        case '(':
        case ')':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }
    return 0;
}


static void printChar(void *data){
    printf("%c", *(char *) data);
}


static void printString(void *data){
    printf("%s", (char *) data);
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


static char *extendString(char *string, char c){
    size_t len = string != NULL ? strlen(string) : 0;
    char *tmpString = (char *) realloc(string, sizeof(char) * (len + 2));
    if (tmpString == NULL){
        free(string);
        return NULL;
    }
    tmpString[len] = c;
    tmpString[len + 1] = '\0';
    return tmpString;
}
    
    
bool hasError(const char *exp){
    Deque *expectedValues = initDeque(17);
    setList(expectedValues, "0123456789-(");
    bool firstMinus = true;
    bool hasDot = false;
    int brackets[] = {0, 0};
    for (size_t j = 0; j < strlen(exp) + 1; j++){
        if (!hasItem(expectedValues, initItem((void *) &exp[j], "char", printChar, NULL), equal)){
            if (isspace(exp[j]) && !((isdigit(exp[j - 1]) || exp[j - 1] == '.') && (isdigit(exp[j + 1]) || exp[j + 1] == '.')))
                continue;
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


Deque *infixToPostfix(const char *exp){
    Deque *postfix = initDeque(100);
    Deque *operands = initDeque(20);
    bool firstMinus = true;
    bool newDigit = true;
    char *tmpString;
    Item *tmpItem;
    append(postfix, initItem(NULL, NULL, printString, free));
    for (size_t j = 0; j < strlen(exp); (isspace(exp[j + 1]) ? j += 2 : j++)){
        if ((isdigit(exp[j]) || exp[j] == '.') && !(newDigit = false)){
            if ((tmpString = extendString(postfix->sequence[postfix->len - 1]->data, exp[j])) == NULL){
                fprintf(stderr, "Memory allocation error at infixToPostfix\n");
                freeDeque(postfix);
                freeDeque(operands);
                return NULL;
            }
            postfix->sequence[postfix->len - 1]->data = tmpString;
        }
        else {
            if (exp[j] == '(' && (firstMinus = true))
                append(operands, initItem((void *) &exp[j], NULL, printChar, NULL));
            else if (exp[j] == ')')
                while (operands->len && *(char *) (tmpItem = pop(operands, -1))->data != '(')
                    append(postfix, tmpItem);
            else {
                while (operands->len && priority(*(char *) operands->sequence[operands->len - 1]->data) >= priority(exp[j]))
                    append(postfix, pop(operands, -1));
                append(operands, initItem((void *) &exp[j], NULL, printChar, NULL));
            }
            if (!newDigit)
                append(postfix, initItem(NULL, NULL, printString, free));
            newDigit = true;
        }
    }
    int len = operands->len;
    for (int i = 0; i < len; i++)
        append(postfix, pop(operands, -1));
    freeDeque(operands);
    return postfix;
}


