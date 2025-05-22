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


void menu(BTree *b_tree){
    Elem *option;
    Elem *elem;
    double actionRange[2] = {0, 4};
    while (true){
        option = handle(typeInt, actionRange, "1 - to add\n2 - to delete\n3 - to print\n4 - task\n0 - to exit\n>>");
        switch (option->value.Int){
            case ADD:
                addNode(b_tree, initNode(elem = handle(typeInt, NULL, "Enter the number: ")));
                freeElem(elem);
                break;
            case DELETE:
                deleteNode(b_tree, initNode(elem = handle(typeInt, NULL, "Enter the number to delete: ")));
                freeElem(elem);
                break;
            case PRINT:
                break;
            case TASK:
                break;
            default:
                freeElem(elem);
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
