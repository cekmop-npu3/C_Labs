#include <BTree.h>


BTree *initBTree(){
    BTree *b_tree = malloc(sizeof(BTree));
    if (b_tree == NULL){
        fprintf(stderr, "Memory allocation error at initBTree\n");
        return NULL;
    }
    b_tree->size = 0;
    b_tree->root = NULL;
    return b_tree;
}


Node *initNode(int value){
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}


static bool assignToParent(Node *parent, Node *node){
    if (node->value < parent->value)
        return parent->left != NULL ? assignToParent(parent->left, node) : (bool) (parent->left = node);
    if (node->value > parent->value)
        return parent->right != NULL ? assignToParent(parent->right, node) : (bool) (parent->right = node);
    return false;
}


bool addNode(BTree *b_tree, Node *node){
    if (b_tree == NULL){
        printf("Can't add Node to an empty BTree\n");
        return false;
    }
    if (b_tree->root == NULL && ++b_tree->size)
        return (bool) (b_tree->root = node);
    return assignToParent(b_tree->root, node) && ++b_tree->size;
}


void freeNode(Node *node){
    if (node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}


void freeBTree(BTree *b_tree){
    freeNode(b_tree == NULL ? NULL : b_tree->root);
    free(b_tree);
}




