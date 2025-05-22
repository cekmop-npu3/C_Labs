#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;


typedef struct {
    int size;
    Node *root;
} BTree;


BTree *initBTree();

Node *initNode(int value);

bool addNode(BTree *b_tree, Node *node);

void freeNode(Node *node);

void freeBTree(BTree *b_tree);

bool deleteNode(BTree *b_tree, Node *node);


#endif
