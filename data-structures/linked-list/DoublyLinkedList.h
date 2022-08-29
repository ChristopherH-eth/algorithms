#pragma once

#include <iostream>
#include "Node.h"

/**
 * @file DoublyLinkedList.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The DoublyLinkedList class utilizes the Node struct to add and remove values from the list.
 *        This implementation allows the user to add nodes to the head and tail of the list, as well as
 *        at any particular index. Nodes can also be removed at the head or tail, as well as via the node
 *        itself, its value, or at any index. And index for an existing value can be returned as well.
 * 
 *        Time Complexity:
 *              Operation                   Average     Worst
 *              Insert at head or tail      O(1)        O(1)
 *              Remove at head or tail      O(1)        O(1)
 *              Search                      O(n)        O(n)
 *              Access                      O(n)        O(n)
 */

template <typename T>

class DoublyLinkedList {

    private:
        int size = 0;
        Node<T>* head;
        Node<T>* tail;
        Node<T>* newNode;

    public:
        /// @see DoublyLinkedList Constructor
        DoublyLinkedList() {}

        /// @see The ListSize() function returns the size of the linked list.
        /// @return Returns the size of the list
        int ListSize() {
            return size;
        }

        /// @see The IsEmpty() function returns true if the list is empty.
        /// @return Returns true if the list is empty
        bool IsEmpty() {
            return size == 0;
        }

        /**
         * @see The AddLast() function adds a the first node if the list is empty, or adds a node to the 
         * end of the list.
         * @param elem The value of the node to be added to the list
         */
        void AddLast(T elem) {
            if (IsEmpty()) {
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
         * @see The addFirst() function adds a the first node if the list is empty, or adds a node to the 
         * beginning of the list.
         * @param elem The value of the node to be added to the list
         */
        void AddFirst(T elem) {
            if (IsEmpty()) {
                head = new Node<T>(elem, NULL, NULL);
                tail = head;
            } else {
                head->previous = new Node<T>(elem, head, NULL);
                head = head->previous;
            }

            std::cout << head->data << " added" << std::endl;
            size++;
        }

        /**
         * @see The AddAt() function adds a new node to the list at a particular index.
         * @param index The index where the node is to be added
         * @param elem The value of the node to be added to the list
         */
        void AddAt(int index, T elem) {
            if (index < 0 || index > size) {
                throw "Index out of bounds";
            } else if (index == 0) {
                AddFirst(elem);
                return;
            } else if (index == size) {
                AddLast(elem);
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

        /// @see The PeekFirst() function returns the first node in the list.
        /// @return Returns the value of the head node
        T PeekFirst() {
            if (IsEmpty()) {
                throw "List is empty.";
            }

            return head->data;
        }

        /// @see The PeekLast() function returns the last node in the list.
        /// @return Returns the value of the tail node
        T PeekLast() {
            if (IsEmpty()) {
                throw "List is empty.";
            }

            return tail->data;
        }

        /// @see The RemoveFirst() function removes the node at the head of the linked list.
        /// @return Returns the value of the removed head node
        T RemoveFirst() {
            if (IsEmpty()) {
                throw "List is empty";
            }

            /// Get head data and move head pointer forward one node
            T data = head->data;
            head = head->next;
            size--;

            /// If the list is empty, set the tail to null; else, memory cleanup
            if (IsEmpty()) {
                tail = NULL;
            } else {
                head->previous = NULL;
            }

            return data;
        }

        /// @see The RemoveLast() function removes the node at the tail of the linked list.
        /// @return Returns the value of the removed tail node
        T RemoveLast() {
            if (IsEmpty()) {
                throw "List is empty";
            }

            /// Get tail data and move tail pointer back one node
            T data = tail->data;
            tail = tail->previous;
            size--;

            /// If the list is empty, set the head to null; else, memory cleanup
            if (IsEmpty()) {
                head = NULL;
            } else {
                tail->next = NULL;
            }

            return data;
        }

        /**
         * @see The Remove() function removes a node from the linked list.
         * @param node The specific node to be removed
         * @return Returns the value of the removed node
         */
        T Remove(Node<T>* node) {
            /// Check if the node to remove is the head or the tail
            if (node->previous == NULL) {
                return RemoveFirst();
            } else if (node->next == NULL) {
                return RemoveLast();
            }

            T data = node->data;
            node->next->previous = node->previous;
            node->previous->next = node->next;

            /// Memory cleanup
            node->data = 0;
            node = node->previous = node->next = NULL;

            size--;

            return data;
        }

        /**
         * @see The RemoveAt() function removes a node at a particular index.
         * @param index The index of the node to be removed
         * @return Returns the value of the node removed by the Remove() function
         */
        T RemoveAt(int index) {
            if (index < 0 || index >= size) {
                throw "Index out of bounds";
            }

            int i;
            Node<T>* trav;

            /// Search from the head; else, search from the tail
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

            return Remove(trav);
        }

        /**
         * @see The RemoveByValue() function removes a node by its data value.
         * @param elem The value of the node to be removed from the list
         * @return Returns true if the node is removed
         */
        bool RemoveByValue(T elem) {
            Node<T>* trav;

            /// Support searching for NULL; else, search for non-NULL value
            if (elem == 0) {
                for (trav = head; trav != NULL; trav = trav->next) {
                    if (trav->data == 0) {
                        Remove(trav);

                        return true;
                    }
                }
            } else {
                for (trav = head; trav != NULL; trav = trav->next) {
                    if (elem == trav->data) {
                        Remove(trav);

                        return true;
                    }
                }
            }

            return false;
        }

        /**
         * @see The IndexOf() function returns the index of a given value.
         * @param elem The value of the node to be searched for
         * @return Returns the index of the node if it exists
         */
        int IndexOf(T elem) {
            int index = 0;
            Node<T>* trav = head;

            /// Support searching for NULL; else, search for non-NULL value
            if (elem == 0) {
                for (; trav != NULL; trav = trav->next, index++) {
                    if (trav->data == 0) {
                        return index;
                    }
                }
            } else {
                for (; trav != NULL; trav = trav->next, index++) {
                    if (elem == trav->data) {
                        return index;
                    }
                }
            }

            return -1;
        }

        /**
         * @see The Contains() function checks if a value is contained within the linked list.
         * @param elem The value of the node to be searched for
         * @return Returns true if the node exists
         */
        bool Contains(T elem) {
            return IndexOf(elem) != -1;
        }

        /// @see The PrintList() function prints the entire linked list.
        void PrintList() {
            std::cout << "Current list: ";

            Node<T>* trav = head;

            for (int i = 0; i < size; i++) {
                std::cout << trav->data << " ";
                trav = trav->next;
            }

            std::cout << "" << std::endl;
        }

};