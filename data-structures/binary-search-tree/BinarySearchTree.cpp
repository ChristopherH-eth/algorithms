#include <iostream>
#include <string>
#include "BinarySearchTree.h"

/**
 * @file BinarySearchTree.cpp
 * @author 0xChristopher
 */

int root {45};
int value[] = {1, 4, 56, 13, 76, 63, 7, 90};

int main() {
    BinarySearchTree<int> BST;

    std::cout << "Adding root (" << root << ") node to BST..." << std::endl;
    BST.add(root);

    for (int i = 0; i < 8; i++) {
        std::cout << "Adding value " << value[i] << " to BST..." << std::endl;
        BST.add(value[i]);
    }

    std::cout << "Printing Binary Search Tree values..." << std::endl;
    BST.display();
};