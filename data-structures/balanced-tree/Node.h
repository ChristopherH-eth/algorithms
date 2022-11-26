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

    // Check instantiation type (valid: double, float, int)
    static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value || 
        std::is_same<T, int>::value, "Invalid type");

    private:
    int bf = 0;             // Balance factor
    T value;                // Node data
    int height = 0;         // Height of node within the tree
    Node* left;             // Left child 
    Node* right;            // Right child

    public:
    /**
     * @brief Node constructor and destructor
     * @param value The Node data
     * @param left Left child
     * @param right Right child
     */
    Node(T value, Node* left, Node* right) 
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    ~Node() 
    {
        if (this->value == -1)
            std::cout << "TOKEN removed" << std::endl;
        else
            std::cout << "Node removed" << std::endl;
    }

};