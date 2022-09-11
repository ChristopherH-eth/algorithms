#include <iostream>
#include <string>
#include "BinarySearchTree.h"

/**
 * @file BinarySearchTree.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Binary Search Tree functionality examples.
 */

int root = 9;
int valueArray1[] = {45, 13, 56, 76, 63, 7, 81, 8, 90, 4, 1, 2};
int valueArray2[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14};
int valueLength1 = sizeof(valueArray1)/sizeof(int);
int valueLength2 = sizeof(valueArray2)/sizeof(int);
int toRemove = 7;

int main() {
    BinarySearchTree<int> BST;

    /// @brief Populating the Binary Search Tree
    std::cout << "Adding root (" << root << ") node to BST..." << std::endl;
    BST.Add(root);

    for (int i = 0; i < valueLength1; i++) {
        std::cout << "Adding value " << valueArray1[i] << " to BST..." << std::endl;
        BST.Add(valueArray1[i]);
    }

    /// @brief Displays pre-order, in-order, post-order, and level-order representations of current nodes
    BST.Display(); 

    /// @brief Provides the BST min. value
    BST.Min(); 

    /// @brief Provides the BST max. value
    BST.Max(); 

    /// @brief Provides the height of the BST
    BST.GetHeight(); 

    /// @brief Removes a node from the BST
    BST.Rem(toRemove); 

    BST.Display();
};