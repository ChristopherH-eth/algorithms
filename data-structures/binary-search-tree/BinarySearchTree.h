#pragma once

#include <string>
#include <queue>
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

        /**
        * The add(T elem) function attempts to add an element to the BST and returns true if it
        * is successful.
        */
        bool add(T elem) {
            if (contains(elem)) {
                return false;
            } else {
                root = add(root, elem);
                nodeCount++;
                return true;
            }
        }

        /**
         * The add(Node<T>* node, T elem) function adds a new node the the BST based on the size
         * of the element to be added.
         */
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

        /** 
        * The contains(Node<T>* node, T elem) function checks the left then right children of the
        * current node for value insertion.
        */
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

        // The findMin() function finds and returns the minimum value in the BST.
        Node<T>* findMin(Node<T>* node) {
            while (node->left != NULL) {
                node = node->left;
            }

            return node;
        }

        // The findMax() function finds and returns the maximum value in the BST.
        Node<T>* findMax(Node<T>* node) {
            while (node->right != NULL) {
                node = node->right;
            }

            return node;
        }

        // The remove() function removes a node from the BST.
        Node<T>* remove(Node<T>* node, T elem) {
            if (node == NULL) {
                return NULL;
            }

            if (elem < node->data) {
                node->left = remove(node->left, elem);
            } else if (elem > node->data) {
                node->right = remove(node->right, elem);
            } else {
                if (node->left == NULL) {
                    return node->right;
                } else if (node->right == NULL) {
                    return node->left;
                } else {
                    Node<T>* tmp = findMin(node->right);

                    node->data = tmp->data;
                    node->right = remove(node->right, tmp->data);

                    delete tmp;
                }
            }

            return node;
        }

        // The height() function returns the height of the BST.
        int height(Node<T>* node) {
            if (node == NULL) {
                return 0;
            } else {
                int lHeight = height(node->left);
                int rHeight = height(node->right);

                if (lHeight > rHeight) {
                    return (lHeight + 1);
                } else {
                    return (rHeight + 1);
                }
            }
        }

        // The preOrder() function prints all of the node values in the BST via pre-order traversal.
        void preOrder(Node<T>* node) {
            if (node == NULL) {
                return;
            }

            std::cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }

        // The inOrder() function prints all of the node values in the BST in ascending order.
        void inOrder(Node<T>* node) {
            if (node == NULL) {
                return;
            }

            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }

        // The postOrder() function prints all of the node values in the BST via post-order traversal.
        void postOrder(Node<T>* node) {
            if (node == NULL) {
                return;
            }

            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->data << " ";
        }

        // The levelOrder() function performs a breadth-first-search using a queue.
        void levelOrder(Node<T>* node) {
            if (node == NULL) {
                return;
            }

            std::queue<Node<T>*> nodes;
            nodes.push(node);

            while (nodes.empty() == false) {
                Node<T>* node = nodes.front();
                std::cout << node->data << " ";
                nodes.pop();

                if (node->left != NULL) {
                    nodes.push(node->left);
                }

                if (node->right != NULL) {
                    nodes.push(node->right);
                }
            }
        }

        /** 
         * The display() function displays the values of all nodes in the BST in pre-order, in-order, post-order,
         * and level-order. It then provides the total count of all the nodes in the BST.
         */
        void display() {
            std::cout << "\nPrinting Binary Search Tree values..." << std::endl;
            std::cout << "Node values in pre-order: " << std::endl;
            preOrder(root);
            std::cout << "\nNode values in order: " << std::endl;
            inOrder(root);
            std::cout << "\nNode values in post-order: " << std::endl;
            postOrder(root);
            std::cout << "\nNode values via level order traversal (breadth first search): " << std::endl;
            levelOrder(root);
            std::cout << "\nTotal of " << nodeCount << " nodes in tree." << std::endl;
        }

        // The min() function allows the main function to call findMin().
        void min() {
            std::cout << "\nFinding the minimum value..." << std::endl;
            std::cout << "Minimum value: " << findMin(root)->data << std::endl;
        }

        // The max() function allows the main function to call findMax().
        void max() {
            std::cout << "\nFinding the maximum value..." << std::endl;
            std::cout << "Maximum value: " << findMax(root)->data << std::endl;
        }

        // The getHeight() function allows the main function to call height().
        void getHeight() {
            std::cout << "\nThe height of the Binary Search Tree is: " << height(root) << std::endl;
        }

        // The rem() function allows the main function to call remove().
        void rem(T elem) {
            std::cout << "\nRemoving node that contains: " << elem << std::endl;
            remove(root, elem);
            nodeCount--;
            std::cout << "Node removed." << std::endl;
        }

};