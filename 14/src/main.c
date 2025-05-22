#include <BTree.h>
#include <stdio.h>


int main(){
    BTree *b_tree = initBTree();
    addNode(b_tree, initNode(12));
    addNode(b_tree, initNode(13));
    addNode(b_tree, initNode(14));
    addNode(b_tree, initNode(2));
    addNode(b_tree, initNode(3));
    deleteNode(b_tree, initNode(3));
    freeBTree(b_tree);
}