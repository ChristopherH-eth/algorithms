#pragma once

#include <iostream>

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Node struct contains the Node variables and pointers.
 */

template <typename T>

class Node {
    
    template <typename U>
    friend class AVLTree;

    private:
        int bf = 0;         /// Balance factor
        T value;            /// Node data
        int height = 0;     /// Height of node within the tree
        Node* left;         /// Left child 
        Node* right;        /// Right child

    public:
        /// @brief Node constructor
        /// @param value The Node data
        Node(T value, Node* left, Node* right) {
            this->value = value;
            this->left = left;
            this->right = right;
        }

        /// @brief Node destructor (for testing)
        ~Node() {
            std::cout << "Node removed" << std::endl;
        }

};