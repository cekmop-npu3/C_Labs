#include <stdio.h>
#include "tree.h"
#include "validators.h"

int main() {
    BTree * tree = NULL;
    int taskChoice;
    while((taskChoice = getValidatedIntInput("Menu: \n Insertion mode - Press 1 \n Print tree - Press 2 \n Delete element - Press 3 \n Get last positive level - Press 4 \n Exit - Press 0 \nInput number: ")) != 0) {
        switch (taskChoice)
        {
        case 1:
            if(!tree) {
                tree = newBTree(getValidatedIntInput("Input max size of the tree: "));
            }
            fillTree(tree);
            break;
        case 2:
            if(!tree) {
                printf("Fill tree firstly...\n");
                continue;
            }
            printTree(tree);
            break;
        case 3:
            if(!tree) {
                printf("Fill tree firstly...\n");
                continue;
            }
            delElem(getValidatedIntInput("Input value to delete: "), tree);
            printTree(tree);
            break;
        case 4:
            if(!tree) {
                printf("Fill tree firstly...\n");
                continue;
            }
            printf("Last positive level is: %d\n", findLastPositiveLevel(tree));
            break;
        case 0:
            return 0;
        default:
            printf("Invalid command\n");
            break;
        }
    }
    return 0;
}