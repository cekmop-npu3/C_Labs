#ifndef EVAL_H
#define EVAL_H

#include <deque.h>
#include <ctype.h>


bool hasError(const char *exp);

Deque *infixToPostfix(const char *exp);

Item *evalPostfix(Deque *postfix);


#endif