#ifndef EVAL_H
#define EVAL_H

#include <deque.h>


void printChar(void *data);

bool equal(Item *item1, Item *item2);

void setList(Deque *deque, const char list[]);

Deque *infixToPostfix(const char *exp);


#endif