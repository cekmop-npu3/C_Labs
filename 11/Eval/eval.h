#ifndef EVAL_H
#define EVAL_H

#include <list.h>
#include <ctype.h>


bool hasError(char *exp);

List *infixToPostfix(char *exp);

Item *evalPostfix(List *postfix);


#endif