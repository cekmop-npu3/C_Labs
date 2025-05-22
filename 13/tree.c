#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree.h"
#include "validators.h"

Node * newNode(int val, Node * prev) {
    Node * node = malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->prev = prev;
    return node;
}

BTree * newBTree(int maxSize) {
    BTree * btree = malloc(sizeof(BTree));
    btree->maxSize = maxSize;
    btree->currSize = 0;
    btree->root = NULL;
    return btree;
}

void addElemLoc(int val, Node*root) {
    if(!root->left && !root->right) {
        if(val > root->val) {
            root->right = newNode(val, root);
        } else if(val > root->val) {
            root->left = newNode(val, root);
        } else {
            return;
        }
        return;
    }

    if(root->val > val) {
        addElemLoc(val, root->left);
    } else if(root->val < val) {
        addElemLoc(val, root->right);
    } else {
        return;
    }

}

void addElem(int val, BTree * btree) {
    if(!btree->root) {
        btree->root = newNode(val, NULL);
        return;
    }
    addElemLoc(val, btree->root);
}

Node * findParentForAdd(int val, Node * node) {
    if(!node) return NULL;
    if(val == node->val) return NULL;
    if(val > node->val) {
        if(node->right) {
            return findParentForAdd(val, node->right);
        } else {
            return node;
        }
    }
    if(val < node->val) {
        if(node->left) {
            return findParentForAdd(val, node->left);
        } else {
            return node;
        }
    }
}

void addTest(int val, BTree *tree) {
    if(!tree->root) {
        tree->root = newNode(val, NULL);
        return;
    }
    Node * p = findParentForAdd(val, tree->root);
    if(!p) return;
    if(val > p->val) {
        p->right = newNode(val, p);
    } else {
        p->left = newNode(val, p);
    }
    tree->currSize++;
}


Node * getExistingChild(Node * p) {
    if(p->left) {
        return p->left;
    } else {
        return p->right;
    }
}

Node* findMin(Node* node, Node** parent) {
    *parent = NULL;
    if (node == NULL) return NULL;
    while (node->left != NULL) {
        *parent = node;
        node = node->left;
    }
    return node;
}

void delElem(int val, BTree * btree) {
    if (btree == NULL || btree->root == NULL) return;

    Node* toDel = findApprEl(val, btree->root);
    if (toDel == NULL) return;


    if (toDel->left == NULL && toDel->right == NULL) {
        if (toDel->prev != NULL) {
            if (toDel->prev->left == toDel) {
                toDel->prev->left = NULL;
            } else {
                toDel->prev->right = NULL;
            }
        } else {
            btree->root = NULL;
        }
        free(toDel);
        btree->currSize--;
    }
    else if ((toDel->left == NULL) ^ (toDel->right == NULL)) {
        Node* child = (toDel->left != NULL) ? toDel->left : toDel->right;
        
        if (toDel->prev != NULL) {
            if (toDel->prev->left == toDel) {
                toDel->prev->left = child;
            } else {
                toDel->prev->right = child;
            }
        } else {
            btree->root = child;
        }
        
        child->prev = toDel->prev;
        free(toDel);
        btree->currSize--;
    }
    else {
        Node* parentOfSuccessor = NULL;
        Node* successor = findMin(toDel->right, &parentOfSuccessor);
        toDel->val = successor->val;

        if (parentOfSuccessor == NULL) {
            toDel->right = successor->right;
        } else {
            parentOfSuccessor->left = successor->right;
        }
        if (successor->right != NULL) {
            successor->right->prev = (parentOfSuccessor != NULL) ? parentOfSuccessor : toDel;
        }

        free(successor);
        btree->currSize--;
    }
} 

Node * findApprEl(int val, Node * compare) {
    if (!compare->left && !compare->right) {
        return compare;
    }
    if(compare->val == val) return compare;
    if(compare->val > val) {
        return findApprEl(val, compare->left);
    } else {
        return findApprEl(val, compare->right);
    }
}

void checkLevel(Node *node, int current_level, int *max_positive_level) {
    if (node == NULL) return;
    
    if (node->val > 0 && current_level > *max_positive_level) {
        *max_positive_level = current_level;
    }
    
    checkLevel(node->left, current_level + 1, max_positive_level);
    checkLevel(node->right, current_level + 1, max_positive_level);
}

int findLastPositiveLevel(BTree *tree) {
    int max_level = -1;
    if (tree != NULL && tree->root != NULL) {
        checkLevel(tree->root, 0, &max_level);
    }
    return max_level;
}

void printTreeHelper(Node *node, int space) {
    if (node == NULL)
        return;

    space += 5;
    
    printTreeHelper(node->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d", node->val);
    
    printTreeHelper(node->left, space);
}

void printTree(BTree *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printTreeHelper(tree->root, 0);
    printf("\n");
}

void fillTree(BTree *btree) {
    if (btree == NULL) return;
    printf("Insertion Mode (enter 'q' to quit)\n");
    while (1) {
        if(btree->maxSize <= btree->currSize + 1) {
            printf("Tree is busy\n");
            return;
        }
        int value = getValidatedIntInput("Enter value: ");
        
        if (value == INT_MIN) {
            printf("Quitting insertion mode...\n");
            break;
        }
        
        addTest(value, btree);
        printTree(btree);
    }
}