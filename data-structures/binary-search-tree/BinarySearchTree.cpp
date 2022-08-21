#include <iostream>
#include <string>
#include "BinarySearchTree.h"

/**
 * @file BinarySearchTree.cpp
 * @author 0xChristopher
 * @brief Binary Search Tree functionality examples.
 */

int root {8};
int valueArray1[] = {45, 13, 56, 76, 63, 7, 81, 90, 4, 1, 2};
int valueArray2[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13};
int valueLength1 = sizeof(valueArray1)/sizeof(int);
int valueLength2 = sizeof(valueArray2)/sizeof(int);
int toRemove {7};

int main() {
    BinarySearchTree<int> BST;

    // Populating the Binary Search Tree
    std::cout << "Adding root (" << root << ") node to BST..." << std::endl;
    BST.add(root);

    for (int i = 0; i < valueLength1; i++) {
        std::cout << "Adding value " << valueArray1[i] << " to BST..." << std::endl;
        BST.add(valueArray1[i]);
    }
    //End populating the Binary Search Tree

    BST.display(); // Displays pre-order, in-order, post-order, and level-order representations of current nodes

    BST.min(); // Provides the BST min. value

    BST.max(); // Provides the BST max. value

    BST.getHeight(); // Provides the height of the BST

    BST.rem(toRemove); // Removes a node from the BST

    BST.display();
};