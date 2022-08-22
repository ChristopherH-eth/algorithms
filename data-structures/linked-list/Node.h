#pragma once

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Node struct contains the Node variables and pointers.
 */

template <typename T>

struct Node{

    public:
        T data;
        Node* next; 
        Node* previous;

};