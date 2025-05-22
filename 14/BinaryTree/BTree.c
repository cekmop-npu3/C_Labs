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


static Node *findNode(Node **parent, Node *node){
    // On non-NULL return, "Parent" stores pointer to the parent of a found node 
    if ((*parent)->left != NULL && node->value < (*parent)->value){
        if ((*parent)->left->value == node->value)
            return (*parent)->left;
        else {
            *parent = (*parent)->left;
            return findNode(parent, node);
        }
    }
    if ((*parent)->right != NULL && node->value > (*parent)->value){
        if ((*parent)->right->value == node->value)
            return (*parent)->right;
        else {
            *parent = (*parent)->right;
            findNode(parent, node);
        }
    }
    return NULL;
}


static void assignNewChild(Node *parent, Node *nodeToDelete, Node *node){
    if (parent->left != NULL && parent->left->value == nodeToDelete->value)
        parent->left = node;
    else
        parent->right = node;
    freeNode(nodeToDelete);
}


static Node *findTheSmallestParent(Node *node){
    return node->left == NULL || node->left->left == NULL ? node : findTheSmallestParent(node->left);
}


bool deleteNode(BTree *b_tree, Node *node){
    Node *nodeToDelete;
    Node *temp;
    if (b_tree == NULL){
        printf("Cannot delete from an empty BTree\n");
        return false;
    }
    Node *parent = b_tree->root;
    if ((nodeToDelete = findNode(&parent, node)) == NULL){
        freeNode(node);
        return false;
    }
    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL)
        assignNewChild(parent, nodeToDelete, NULL);
    else if (nodeToDelete->left != NULL && nodeToDelete->right == NULL)
        assignNewChild(parent, nodeToDelete, nodeToDelete->left);
    else if (nodeToDelete->left == NULL && nodeToDelete->right != NULL)
        assignNewChild(parent, nodeToDelete, nodeToDelete->right);
    else {
        Node *smallestParent = findTheSmallestParent(nodeToDelete->right);
        if (smallestParent->left == NULL){
            nodeToDelete->value = smallestParent->value;
            freeNode(smallestParent);
            nodeToDelete->right = NULL;
        }
        else {
            nodeToDelete->value = smallestParent->left->value;
            freeNode(smallestParent->left);
            smallestParent->left = NULL;
        }
    }
    freeNode(node);
    return true;
}

