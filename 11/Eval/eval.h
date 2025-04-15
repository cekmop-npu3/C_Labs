#ifndef EVAL_H
#define EVAL_H

#include <list.h>
#include <ctype.h>


bool hasError(const char *exp);

List *infixToPostfix(const char *exp);

Item *evalPostfix(List *postfix);


#endif