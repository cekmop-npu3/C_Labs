#include <eval.h>


static int priority(char c){
    switch (c){
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }
    return 0;
}


static void printDouble(void *data){
    printf("%.2f", *(double *) data);
}


static void printChar(void *data){
    printf("%c", *(char *) data);
}


static void printString(void *data){
    printf("%s", (char *) data);
}


static bool equal(Item *item1, Item *item2){
    return  *(char *) item1->data == *(char *) item2->data;
}


static void setList(List *list, const char seq[]){
    for (int i = 0; i < list->len; i++)
        freeItem(list->sequence[i]);
    list->len = 0;
    for (size_t j = 0; j < strlen(seq); j++)
        append(list, initItem((void *) &seq[j], printChar, NULL));
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


static double *evalExp(Item *item1, Item *item2, char operand){
    double num1 = item1->printFunc == printDouble ? *(double *) item1->data : atof(item1->data);
    double num2 = item2->printFunc == printDouble ? *(double *) item2->data : atof(item2->data);
    freeItem(item1);
    freeItem(item2);
    double *result = malloc(sizeof(double));
    if (result == NULL){
        fprintf(stderr, "Memory allocation failed at evalExp\n");
        free(result);
        return NULL;
    }
    switch (operand){
        case '+':
            *result = num1 + num2;
            break;
        case '-':
            *result = num1 - num2;
            break;
        case '*':
            *result = num1 * num2;
            break;
        case '/':
            if (!num2){
                fprintf(stderr, "ZeroDivision error, terminating\n");
                free(result);
                return NULL;
            }
            *result = num1 / num2;
            break;
    }
    return result;
}
    
    
bool hasError(char *exp){
    Item *cmp;
    List *expectedValues = initList(17);
    setList(expectedValues, "0123456789-(");
    bool firstMinus = true;
    bool hasDot = false;
    int brackets[] = {0, 0};
    for (size_t j = 0; j < strlen(exp) + 1; (isspace(exp[j + 1]) ? j += 2 : j++)){
        if (!hasItem(expectedValues, (cmp = initItem((void *) &exp[j], printChar, NULL)), equal)){
            freeItem(cmp);
            if (j == strlen(exp) && (isdigit(exp[j - 1]) || exp[j - 1] == ')' || isspace(exp[j - 1])))
                break;
            fprintf(stderr, "%s\n", exp);
            for (size_t i = 0; i < strlen(exp) + 1; i++)
                i == j ? fprintf(stderr, "^") : fprintf(stderr, "=");
            fprintf(stderr, "\n[SyntaxError] Invalid character at pos %ld\n", j);
            freeList(expectedValues);
            return true;
        }
        freeItem(cmp);
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
    freeList(expectedValues);
    if (brackets[0] != brackets[1])
        return (bool) fprintf(stderr, "[SyntaxError] Brackets count does not match\n");
    return false;
}


List *infixToPostfix(char *exp){
    List *postfix = initList(100);
    List *operands = initList(20);
    bool firstMinus = true;
    bool newDigit = true;
    char *tmpString;
    Item *tmpItem;
    for (size_t j = 0; j < strlen(exp); (isspace(exp[j + 1]) ? j += 2 : j++)){
        if ((isdigit(exp[j]) || exp[j] == '.' || (exp[j] == '-' && firstMinus)) && !(firstMinus = false)){
            if (newDigit && !(newDigit = false))
                append(postfix, initItem(NULL, printString, free));
            if ((tmpString = extendString(postfix->sequence[postfix->len - 1]->data, exp[j])) == NULL){
                fprintf(stderr, "Memory allocation error at infixToPostfix\n");
                freeList(postfix);
                freeList(operands);
                return NULL;
            }
            postfix->sequence[postfix->len - 1]->data = tmpString;
            continue;
        }
        if (exp[j] == '(' && (firstMinus = true))
            append(operands, initItem((void *) &exp[j], printChar, NULL));
        else if (exp[j] == ')' && !(firstMinus = false)){
            while (operands->len && *(char *) (tmpItem = pop(operands, -1))->data != '(')
                append(postfix, tmpItem);
            freeItem(tmpItem);
        }
        else {
            firstMinus = false;
            while (operands->len && priority(*(char *) operands->sequence[operands->len - 1]->data) >= priority(exp[j]))
                append(postfix, pop(operands, -1));
            append(operands, initItem((void *) &exp[j], printChar, NULL));
        }
        newDigit = true;
    }
    while (operands->len)
        append(postfix, pop(operands, -1));
    freeList(operands);
    return postfix;
}


Item *evalPostfix(List *postfix){
    List *list = initList(100);
    Item *item;
    double *result;
    while (postfix->len){
        if ((item = pop(postfix, 0))->printFunc == printChar){
            result = evalExp(pop(list, -1), pop(list, -1), *(char *) item->data);
            freeItem(item);
            if (result == NULL){
                freeList(list);
                return NULL;
            }
            append(list, initItem(result, printDouble, free));
            continue;
        }
        append(list, item);
    }
    item = pop(list, -1);
    freeList(list);
    return item;
}


