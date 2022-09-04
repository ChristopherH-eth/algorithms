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
int rem = 12;
std::vector<int> data = {5, 3, 2, 7, 12, 6, 13, 24, 23, 11, 15};

int main() {
    AVLTree<int> avlTree;

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << avlTree.IsEmpty() << std::endl;
    avlTree.CheckInsert(root);
    std::cout << avlTree.IsEmpty() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;

    for (int i = 0; i < data.size(); i++) {
        avlTree.CheckInsert(data[i]);
    }

    std::cout << "Data successfully added" << std::endl;
    avlTree.Display();
    std::cout << "\n------------------------------------------------------" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node: " << rem << std::endl;
    avlTree.CheckRemove(rem);
    avlTree.Display();
    std::cout << "\n------------------------------------------------------" << std::endl;

    std::cin.get();
}