#include <BTree.h>
#include <stdio.h>
#include <input.h>
#include <stdlib.h>


typedef enum {
    ADD = 1,
    DELETE,
    PRINT,
    TASK
} Actions;


static void checkLevel(Node *node, int currentLevel, int *maxLevel) {
    if (node == NULL) 
        return;
    if (node->value > 0 && currentLevel > *maxLevel)
        *maxLevel = currentLevel;
    checkLevel(node->left, currentLevel + 1, maxLevel);
    checkLevel(node->right, currentLevel + 1, maxLevel);
}


int lastPositiveLevel(BTree *b_tree){
    int max_level = 0;
    if (b_tree != NULL && b_tree->root != NULL) {
        checkLevel(b_tree->root, 0, &max_level);
    }
    return max_level;
}


void menu(BTree *b_tree){
    Elem *option;
    Elem *elem = NULL;
    double actionRange[2] = {0, 4};
    while (true){
        option = handle(typeInt, actionRange, "1 - to add\n2 - to delete\n3 - to print\n4 - task\n0 - to exit\n>>");
        switch (option->value.Int){
            case ADD:
                addNode(b_tree, initNode((elem = handle(typeInt, NULL, "Enter the number: "))->value.Int));
                freeElem(elem);
                elem = NULL;
                break;
            case DELETE:
                deleteNode(b_tree, initNode((elem = handle(typeInt, NULL, "Enter the number to delete: "))->value.Int));
                freeElem(elem);
                elem = NULL;
                break;
            case PRINT:
                printBTRee(b_tree);
                break;
            case TASK:
                printf("Last positive level: %d\n", lastPositiveLevel(b_tree));
                break;
            default:
                if (elem != NULL)
                    freeElem(elem);
                freeElem(option);
                return;
        }
        freeElem(option);
    }
}


int main(){
    BTree *b_tree = initBTree();
    menu(b_tree);
    freeBTree(b_tree);
    return EXIT_SUCCESS;
}
