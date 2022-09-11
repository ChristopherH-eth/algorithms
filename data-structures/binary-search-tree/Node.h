#pragma once

#include <iostream>

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Node struct contains the Node variables and pointers.
 */

template <typename T>

struct Node{

    template <typename U>
    friend class BinarySearchTree;

    private:
        T data;         /// Node data
        Node* left;     /// Left child
        Node* right;    /// Right child

    public:
        /** 
         * @brief Node constructor
         * @param data The value of the node
         * @param left Left child
         * @param right right child
         */
        Node(T data, Node* left, Node* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        }

        /// @brief Node destructor (for testing)
        ~Node() {
            std::cout << "Node removed" << std::endl;
        }

};