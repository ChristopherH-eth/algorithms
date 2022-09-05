#include <iostream>
#include <vector>
#include "AVLTree.h"

/**
 * @file AVLTree.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the AVLTree class
 */

int root = 9;
int rem1 = 12;
int rem2 = 11;
std::vector<int> data = {5, 3, 2, 7, 12, 6, 13, 24, 23, 11, 15};

int main() {
    AVLTree<int> avlTree;

    /// @brief Check AVL Tree initialization
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << avlTree.IsEmpty() << std::endl;
    avlTree.CheckInsert(root);
    std::cout << avlTree.IsEmpty() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Add elements to tree and display
    std::cout << "------------------------------------------------------" << std::endl;

    for (int i = 0; i < data.size(); i++) {
        avlTree.CheckInsert(data[i]);
    }

    std::cout << "Data successfully added" << std::endl;
    avlTree.Display();
    std::cout << "\nNumber of nodes in AVL Tree: " << avlTree.Size() << std::endl;
    std::cout << "Current tree height: " << avlTree.Height() << std::endl;

    if (avlTree.CheckBSTInvariant()){
        std::cout << "Tree adhears to BST invariant." << std::endl;
    } else {
        std::cout << "Tree fails to adhear to BST invariant." << std::endl;
    }

    avlTree.PrintTree();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Remove node from tree
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing nodes: " << rem1 << " and " << rem2 << std::endl;
    avlTree.CheckRemove(rem1);
    avlTree.CheckRemove(rem2);
    avlTree.Display();
    std::cout << "\nNumber of nodes in AVL Tree: " << avlTree.Size() << std::endl;
    std::cout << "Current tree height: " << avlTree.Height() << std::endl;

    if (avlTree.CheckBSTInvariant()){
        std::cout << "Tree adhears to BST invariant." << std::endl;
    } else {
        std::cout << "Tree fails to adhear to BST invariant." << std::endl;
    }

    avlTree.PrintTree();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}