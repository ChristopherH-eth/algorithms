#pragma once

#include <iostream>
#include "Node.h"

/**
 * @file DoublyLinkedList.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The DoublyLinkedList class utilizes the Node struct to add and remove values from the list.
 */

template <typename T>

class DoublyLinkedList {

    private:
        int size = 0;
        Node<T>* head;
        Node<T>* tail;
        Node<T>* newNode;

    public:
        // DoublyLinkedList Constructor
        DoublyLinkedList() {}

        // The size() function returns the size of the linked list.
        int listSize() {
            return size;
        }

        // The isEmpty() function returns true if the list is empty.
        bool isEmpty() {
            return size == 0;
        }

        /**
         * The addLast() function adds a the first node if the list is empty, or adds a node to the 
         * end of the list.
         */
        void addLast(T elem) {
            if (isEmpty()) {
                head = new Node<T>(elem, NULL, NULL);
                tail = head;
            } else {
                tail->next = new Node<T>(elem, NULL, tail);
                tail = tail->next;
            }

            std::cout << tail->data << " added" << std::endl;
            size++;
        }

        /**
         * The addFirst() function adds a the first node if the list is empty, or adds a node to the 
         * beginning of the list.
         */
        void addFirst(T elem) {
            if (isEmpty()) {
                head = new Node<T>(elem, NULL, NULL);
                tail = head;
            } else {
                head->previous = new Node<T>(elem, head, NULL);
                head = head->previous;
            }

            std::cout << head->data << " added" << std::endl;
            size++;
        }

        // The addAt() function adds a new node to the list at a particular index.
        void addAt(int index, T elem) {
            if (index < 0 || index > size) {
                throw "Index out of bounds";
            } else if (index == 0) {
                addFirst(elem);
                return;
            } else if (index == size) {
                addLast(elem);
                return;
            } else {
                Node<T>* tmp = head;

                for (int i = 0; i < index - 1; i++) {
                    tmp = tmp->next;
                }

                newNode = new Node<T>(elem, tmp->next, tmp);
                tmp->next->previous = newNode;
                tmp->next = newNode;

                size++;
            }
        }

        // The peekFirst() function returns the first node in the list.
        T peekFirst() {
            if (isEmpty()) {
                throw "List is empty.";
            }

            return head->data;
        }

        // The peekLast() function returns the last node in the list.
        T peekLast() {
            if (isEmpty()) {
                throw "List is empty.";
            }

            return tail->data;
        }

        // The removeFirst() function removes the node at the head of the linked list.
        T removeFirst() {
            if (isEmpty()) {
                throw "List is empty";
            }

            T data = head->data;
            head = head->next;
            size--;

            if (isEmpty()) {
                tail = NULL;
            } else {
                head->previous = NULL;
            }

            return data;
        }

        // The removeLast() function removes the node at the tail of the linked list.
        T removeLast() {
            if (isEmpty()) {
                throw "List is empty";
            }

            T data = tail->data;
            tail = tail->previous;
            size--;

            if (isEmpty()) {
                head = NULL;
            } else {
                tail->next = NULL;
            }

            return data;
        }

        // The remove() function removes a node from the linked list.
        T remove(Node<T>* node) {
            if (node->previous == NULL) {
                return removeFirst();
            } else if (node->next == NULL) {
                return removeLast();
            }

            T data = node->data;
            node->next->previous = node->previous;
            node->previous->next = node->next;

            node->data = 0;
            node = node->previous = node->next = NULL;
            size--;

            return data;
        }

        // The removeAt() function removes a node at a particular index.
        T removeAt(int index) {
            if (index < 0 || index >= size) {
                throw "Index out of bounds";
            }

            int i;
            Node<T>* trav;

            if (index < size / 2) {
                trav = head;

                for (i = 0; i != index; i++) {
                    trav = trav->next;
                }
            } else {
                trav = tail;

                for (i = size - 1; i != index; i--) {
                    trav = trav->previous;
                }
            }

            return remove(trav);
        }

        // The printList() function prints the entire linked list.
        void printList() {
            std::cout << "Current list: ";

            Node<T>* trav = head;

            for (int i = 0; i < size; i++) {
                std::cout << trav->data << " ";
                trav = trav->next;
            }

            std::cout << "" << std::endl;
        }

};