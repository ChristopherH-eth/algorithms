#include <iostream>
#include <vector>
#include "AVLTree.h"

/**
 * @file AVLTree.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Functional demonstration of the AVLTree class
 */

int root = 9;                                                           // Root node to add
int rem1 = 12;                                                          // Node to remove
int rem2 = 11;                                                          // Node to remove
std::vector<int> data = {5, 3, 2, 7, 12, 6, 13, 24, 23, 11, 15};        // Node data vector

int main() 
{
    AVLTree<int> avlTree;

    // Check AVL Tree initialization
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking AVL Tree initialization..." << std::endl;

    if (avlTree.IsEmpty())
        std::cout << "Tree is currently empty" << std::endl;
    else   
        std::cout << "Tree initialized!" << std::endl;

    std::cout << "Inserting root..." << std::endl;
    avlTree.CheckInsert(root);

    if (avlTree.IsEmpty())
        std::cout << "Tree is currently empty" << std::endl;
    else   
        std::cout << "Tree initialized!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Add elements to tree, display them, and validate binary search tree invariant
    std::cout << "------------------------------------------------------" << std::endl;

    for (int i = 0; i < data.size(); i++)
        avlTree.CheckInsert(data[i]);

    std::cout << "Data successfully added" << std::endl;
    avlTree.Display();

    std::cout << "\n\nNumber of nodes in AVL Tree: " << avlTree.Size() << std::endl;
    std::cout << "Current tree height: " << avlTree.Height() << std::endl;

    if (avlTree.CheckBSTInvariant())
        std::cout << "Tree adhears to BST invariant." << std::endl;
    else
        std::cout << "Tree fails to adhear to BST invariant." << std::endl;

    avlTree.PrintTree();
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove node from tree and validate binary search tree invariant
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing nodes: " << rem1 << " and " << rem2 << std::endl;
    avlTree.CheckRemove(rem1);
    avlTree.CheckRemove(rem2);
    avlTree.Display();

    std::cout << "\n\nNumber of nodes in AVL Tree: " << avlTree.Size() << std::endl;
    std::cout << "Current tree height: " << avlTree.Height() << std::endl;

    if (avlTree.CheckBSTInvariant())
        std::cout << "Tree adhears to BST invariant." << std::endl;
    else
        std::cout << "Tree fails to adhear to BST invariant." << std::endl;

    avlTree.PrintTree();
    std::cout << "------------------------------------------------------" << std::endl;

    // Check is specific values are stored in the tree
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking tree contents...\n" << std::endl;

    if (avlTree.Contains(root))
        std::cout << "The tree does contain " << root << std::endl;
    else
        std::cout << "The tree does not contain " << root << std::endl;
    
    if (avlTree.Contains(rem1))
        std::cout << "The tree does contain " << rem1 << std::endl;
    else
        std::cout << "The tree does not contain " << rem1 << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;

    // Clear and remove all nodes and the tree itself
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Clearing tree...\n" << std::endl;
    avlTree.Clear();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}