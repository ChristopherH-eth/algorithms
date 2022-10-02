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
        T m_data;         /// Node data
        Node* m_left;     /// Left child
        Node* m_right;    /// Right child

    public:
        /** 
         * @brief Node constructor
         * @param data The value of the node
         * @param left Left child
         * @param right right child
         */
        Node(T data, Node* left, Node* right) :
            m_data(data), m_left(left), m_right(right) {}

        /// @brief Node destructor (for testing)
        ~Node() {
            std::cout << "Node removed" << std::endl;
        }

};