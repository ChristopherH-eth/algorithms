#pragma once

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Node struct contains the Node variables and pointers.
 */

template <typename T>

struct Node {

    template <typename U>
    friend class DoublyLinkedList;

    private:
        T m_data;               /// Information held within the node
        Node* m_next;           /// Reference to the next node in the list
        Node* m_previous;       /// Reference to the previous node in the list

    public:
        Node(T data, Node* next, Node* previous) 
            : m_data(data), m_next(next), m_previous(previous) {}

        ~Node() {}

};