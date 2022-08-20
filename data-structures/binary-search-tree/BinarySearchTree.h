#pragma once

#include <string>
#include "Node.h"

/**
 * @file BinarySearchTree.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The BinarySearchTree (BST) class utilizes the Node struct to add values to the BST.
 */

template <typename T>

class BinarySearchTree {

    private:
        int nodeCount {0};
        Node<T>* root = NULL;

    public:
        // BinarySearchTree Constructor
        BinarySearchTree() {}

        // The size() function returns the size of the BinarySearchTree.
        int size() {
            return nodeCount;
        }

        // The isEmpty() function returns true if the BST is empty.
        bool isEmpty() {
            return nodeCount == 0;
        }

        // The add(T elem) function attempts to add an element to the BST and returns true if it
        // is successful.
        bool add(T elem) {
            if (contains(elem)) {
                return false;
            } else {
                root = add(root, elem);
                nodeCount++;
                return true;
            }
        }

        // The add(Node<T>* node, T elem) function adds a new node the the BST based on the size
        // of the element to be added.
        Node<T>* add(Node<T>* node, T elem) {
            if (node == NULL) {
                node = new Node<T>;
                node->data = elem;
                node->left = NULL;
                node->right = NULL;
            } else {
                if (elem < node->data) {
                    node->left = add(node->left, elem);
                } else {
                    node->right = add(node->right, elem);
                }
            }

            return node;
        }

        // The contains(T elem) function returns true if the root node has a value.
        bool contains(T elem) {
            return contains(root, elem);
        }

        // The contains(Node<T>* node, T elem) function checks the left then right children of the
        // current node for value insertion.
        bool contains(Node<T>* node, T elem) {
            if (node == NULL) {
                return false;
            }

            if (elem < node->data) {
                return contains(node->left, elem);
            } else if (elem > node->data) {
                return contains(node->right, elem);
            } else {
                return true;
            }
        }

        // The inOrder() function prints all of the node values in the BST in ascending order.
        void inOrder(Node<T>* root) {
            if (root == NULL) {
                return;
            }

            inOrder(root->left);
            std::cout << root->data << std::endl;
            inOrder(root->right);
        }

        // The display() function allows the main function to call the inOrder() function.
        void display() {
            inOrder(root);
            std::cout << "Total of " << nodeCount << " nodes in tree." << std::endl;
        }

};