#ifndef BTREE_H
#define BTREE_H


typedef struct Node {
    int val;
    struct Node * prev;
    struct Node * left;
    struct Node * right;
}Node;

typedef struct BTree {
    int currSize;
    int maxSize;
    struct Node * root;
}BTree;

void printTree(BTree* tree);

BTree * newBTree(int maxSize);

void addElemLoc(int val, Node*root);

void addElem(int val, BTree * btree);

void delElem(int val, BTree * btree);

Node * findApprEl(int val, Node * compare);

void addTest(int val, BTree * tree);

int findLastPositiveLevel(BTree *tree);

void fillTree(BTree *btree);


#endif