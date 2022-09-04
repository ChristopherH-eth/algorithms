#pragma once

#include <stdio.h>
#include <typeinfo>
#include <math.h>
#include <algorithm>
#include <queue>
#include "../balanced-tree/Node.h"

/**
 * @file AVLTree.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief AVL Tree implementation, also known as a self-balancing Binary Search Tree. The reasoning
 *        behind this data structure is that the its self-balancing nature keeps operations
 *        logarithmic. After each insert or removal, the height of each node is checked, and if not
 *        -1, 0, or 1, the tree is rebalanced through either left or right rotations. The AVL Tree must
 *        also adhere to the Binary Search Tree invariant, such that each node's left child is less than
 *        itself, and its right child greater.
 * 
 *        Time Complexity (Search, Insert, Delete): O(log n)
 */

template <typename T>

class AVLTree {

    private:
        int nodeCount = 0;
        Node<T>* TOKEN = nullptr; /// Used to indicate duplicate values in the AVL Tree
        Node<T>* tmp;

        /**
         * @brief The Insert() function inserts a node into the AVL Tree
         * @param node The root of the tree
         * @param value The value of the node to be inserted
         * @return Returns a TOKEN for duplicate node values, or returns a new Node
         */
        Node<T>* Insert(Node<T>*& node, T value) {
            if (node == nullptr)
                return new Node<T>(value, nullptr, nullptr);

            if (typeid(value) == typeid(node->value) && typeid(value) != typeid(std::string)) {
                if (value < node->value) {
                    Node<T>* newLeftNode = Insert(node->left, value);

                    if (newLeftNode == TOKEN)
                        return TOKEN;

                    node->left = newLeftNode;
                } else if (value > node->value) {
                    Node<T> *newRightNode = Insert(node->right, value);

                    if (newRightNode == TOKEN)
                        return TOKEN;

                    node->right = newRightNode;
                } else {
                    return TOKEN;
                }
            }

            /// Update node balance factor and height
            Update(node);
            
            /// Rebalance tree
            return Balance(node);
        }

        /// @brief The Update() function updates a node's height and balance factor.
        /// @param node The node to be updated
        void Update(Node<T>*& node) {
            int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
            int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;

            node->height = 1 + fmax(leftNodeHeight, rightNodeHeight);
            node->bf = rightNodeHeight - leftNodeHeight;
        }

        /**
         * @brief The Balance() function rebalances the AVL tree if a node's balance factor
         * is -2 or 2.
         * @param node The node to be rebalanced
         * @return Returns the re-balanced node
         */
        Node<T>* Balance(Node<T>*& node) {
            /// Left heavy subtree
            if (node->bf == -2) {
                if (node->left->bf <= 0) {
                    return LeftLeftCase(node);
                } else {
                    return LeftRightCase(node);
                }

            /// Right heavy subtree
            } else if (node->bf == 2) {
                if (node->right->bf >= 0) {
                    return RightRightCase(node);
                } else {
                    return RightLeftCase(node);
                }

            /// Node has a balance factor of -1, 0, or 1
            } else {
                return node;
            }
        }

        /* Tree Rotations */
        Node<T>* LeftLeftCase(Node<T>*& node) {
            return RightRotation(node);
        }

        Node<T>* LeftRightCase(Node<T>*& node) {
            node->left = LeftRotation(node->left);
            return LeftLeftCase(node);
        }

        Node<T>* RightRightCase(Node<T>*& node) {
            return LeftRotation(node);
        }

        Node<T>* RightLeftCase(Node<T>*& node) {
            node->right = RightRotation(node->right);
            return RightRightCase(node);
        }

        /**
         * @brief The LeftRotation() function performs a left rotation on the current node.
         * @param node The node to be rotated
         * @return Returns the new parent node
         */
        Node<T>* LeftRotation(Node<T>*& node) {
            Node<T>* newParent = node->right;
            node->right = newParent->left;
            newParent->left = node;

            Update(node);
            Update(newParent);

            return newParent;
        }

        /**
         * @brief The RightRotation() function performs a right rotation on the current node.
         * @param node The node to be rotated
         * @return Returns the new parent node
         */
        Node<T>* RightRotation(Node<T>*& node) {
            Node<T>* newParent = node->left;
            node->left = newParent->right;
            newParent->right = node;

            Update(node);
            Update(newParent);

            return newParent;
        }

        /**
         * @brief The Remove() function removes a node from the AVL Tree.
         * @param node The root of the AVL Tree
         * @param value The value of the node to be removed
         * @return Returns the rebalanced node upon successful removal, or TOKEN if the node doesn't exist
         * in the tree
         */
        Node<T>* Remove(Node<T>*& node, T value) {
            if (node == nullptr)
                return TOKEN;

            if (typeid(value) == typeid(node->value) && typeid(value) != typeid(std::string)) {
                /// Node value is less than the root, so dig left
                if (value < node->value) {
                    Node<T>* newLeftNode = Remove(node->left, value);

                    if (newLeftNode == TOKEN)
                        return TOKEN;

                    return newLeftNode;

                /// Node value is greater than the root, so dig right
                } else if (value > node->value) {
                    Node<T>* newRightNode = Remove(node->right, value);

                    if (newRightNode == TOKEN)
                        return TOKEN;

                    return newRightNode;

                /// Found the node to remove    
                } else {
                    /// Swap with right child if it exists and left child is null
                    if (node->left == nullptr) {
                        tmp = node;
                        std::swap(node, node->right);
                        return node->right;

                    /// Swap with left child if it exists and right child is null
                    } else if (node->right == nullptr) {
                        tmp = node;
                        std::swap(node, node->left);
                        return node;

                    /// Node has left and right subtrees
                    } else {
                        /// Remove from the left subtree
                        if (node->left->height > node->right->height) {
                            T successorValue = FindMax(node->left);
                            node->value = successorValue;
                            Node<T>* replacement = Remove(node->left, successorValue);

                            if (replacement == TOKEN)
                                return TOKEN;
                            
                            node->left = replacement;

                        /// Remove from the right subtree
                        } else {
                            T successorValue = FindMin(node->right);
                            node->value = successorValue;
                            Node<T>* replacement = Remove(node->right, successorValue);

                            if (replacement == TOKEN)
                                return TOKEN;

                            node->right = replacement;
                        }
                    }
                }
            }

            /// Update node balance factor and height
            Update(node);
            
            /// Rebalance tree
            return Balance(node);
        }

        /**
         * @brief The FindMin() function finds the minimum value in the tree or subtree.
         * @param node The node to begin searching from
         * @return Returns the value of the smallest node in the given subtree
         */
        T FindMin(Node<T>*& node) {
            while (node->left != nullptr)
                node = node->left;

            return node->value;
        }

        /**
         * @brief The FindMax() function finds the maximum value in the tree or subtree.
         * @param node The node to begin searching from
         * @return Returns the value of the largest node in the given subtree
         */
        T FindMax(Node<T>*& node) {
            while (node->right != nullptr)
                node = node->right;

            return node->value;
        }

    public:
        Node<T>* root = nullptr;

        /// @brief Default constructor/destructor
        AVLTree() {}
        ~AVLTree() {}

        /// @brief The Height() function returns the height of the AVL Tree.
        /// @return Returns the height based on the root node
        int Height() {
            if (root == nullptr)
                return 0;

            return root->height;
        }

        /// @brief The Size() function returns the number of nodes in the AVL Tree.
        /// @return Returns nodeCount
        int Size() {
            return nodeCount;
        }

        /// @brief The IsEmpty() function checks if the AVL Tree contains any nodes.
        /// @return Returns true if no nodes exist
        bool IsEmpty() {
            return Size() == 0;
        }

        /** 
         * @brief The Contains() function checks if a node exists in the AVL Tree.
         * @param value The value of the node
         * @return Returns true if the node exists
         */
        bool Contains(T value) {
            Node<T>* node = root;

            while (node != nullptr) {
                if (typeid(value) == typeid(node->value) && typeid(value) != typeid(std::string)) {
                    if (value < node->value) {
                        node = node->left;
                    } else if (value > node->value) {
                        node = node->right;
                    } else {
                        return true;
                    }
                }
            }

            return false;
        }

        /**
         * @brief The CheckInsert() function checks to see if a node was successfully inserted.
         * @param value The value of the node to be inserted
         * @return Returns true if the node is successfully inserted
         */
        bool CheckInsert(T value) {
            if (!value)
                return false;

            Node<T>* newRoot = Insert(root, value);
            bool insertedNode = (newRoot != TOKEN);

            if (insertedNode) {
                root = newRoot;
                nodeCount++;
            }

            return insertedNode;
        }

        /**
         * @brief The CheckRemove() function tries to remove a node from the AVL Tree.
         * @param elem The value of the node to be removed
         * @return Returns true if a node has been removed
         */
        bool CheckRemove(T elem) {
            Node<T>* newRoot = Remove(root, elem);
            bool removedNode = (newRoot != TOKEN) || (newRoot == nullptr);

            if (removedNode) {
                delete tmp;
                //root = newRoot;
                nodeCount--;

                return true;
            }

            return false;
        }

        /* Test Functions */
        void Display() {
            DisplayNode(root);
        }

        void DisplayNode(Node<T>*& node) {
            if (node == nullptr)
                return;

            std::queue<Node<T>*> nodes;
            nodes.push(node);
            int nodeHeight = node->height;

            while (nodes.empty() == false) {
                Node<T>* node = nodes.front();

                // if (node->height != nodeHeight) {
                //     printf("\n");
                //     nodeHeight = node->height;
                // }

                printf("%d ", node->value);
                nodes.pop();

                if (node->left != nullptr) {
                    nodes.push(node->left);
                }

                if (node->right != nullptr) {
                    nodes.push(node->right);
                }
            }
        }

};