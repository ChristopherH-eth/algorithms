#pragma once

#include <iostream>
#include <string>
#include <queue>
#include "../binary-search-tree/Node.h"

/**
 * @file BinarySearchTree.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The BinarySearchTree (BST) class utilizes the Node struct to add values to the BST.
 *        This implementation allows a user to insert new nodes, find the minimum and maximum
 *        values, remove nodes from the tree, and print nodes in pre-order, in-order, and 
 *        post-order. It also allows for a level-order search, and can return the height of the
 *        BST.
 * 
 *        Average Time Complexity (Search, Insert, Delete):     O(log n)
 *        Worst Case Time Complexity (Search, Insert, Delete):  O(n)
 */

template <typename T>

class BinarySearchTree {

    private:
        int nodeCount = 0;              /// The number of nodes in the BST
        Node<T>* root = nullptr;        /// The root of the BST
        Node<T>* tmp = nullptr;

        /// @brief The Size() function returns the size of the BinarySearchTree.
        /// @return The number of nodes in the BST
        int Size() {
            return nodeCount;
        }

        /// @brief The IsEmpty() function returns true if the BST is empty.
        /// @return True if the BST is empty
        bool IsEmpty() {
            return nodeCount == 0;
        }

        /**
         * @brief The Add(Node<T>* node, T elem) function adds a new node the the BST based on the size
         * of the element to be added.
         * @param node The node to be added to the BST
         * @param elem The value of the node being added
         * @return Returns the successfully added node
         */
        Node<T>* Add(Node<T>*& node, T elem) {
            if (node == nullptr) {
                node = new Node<T>(elem, nullptr, nullptr);
            } else {
                if (elem < node->m_data)
                    node->m_left = Add(node->m_left, elem);
                else
                    node->m_right = Add(node->m_right, elem);
            }

            return node;
        }

        /**
         * @brief The Contains(T elem) function returns true if the root node has a value.
         * @param elem The node value being searched for
         * @return Returns true or false based on the overloaded function
         */
        bool Contains(T elem) {
            return Contains(root, elem);
        }

        /**
         * @brief The Contains(Node<T>* node, T elem) function checks the left then right children of the
         * current node for value insertion.
         * @param node The root node of the BST or sub-tree passed in from the function overload
         * @param elem The node value being searched for
         * @return Returns true of the node/value exists
         */
        bool Contains(Node<T>*& node, T elem) {
            if (node == nullptr)
                return false;

            if (elem < node->m_data)
                return Contains(node->m_left, elem);
            else if (elem > node->m_data)
                return Contains(node->m_right, elem);
            else
                return true;
        }

        /**
         * @brief The FindMin() function finds and returns the minimum value in the BST.
         * @param node The root node of the BST or subtree to begin searching from
         * @return Returns the node with the smallest value in the BST or subtree
         */
        Node<T>* FindMin(Node<T>*& node) {
            Node<T>* minNode = node;

            while (minNode->m_left != nullptr)
                minNode = minNode->m_left;

            return minNode;
        }

        /**
         * @brief The FindMax() function finds and returns the maximum value in the BST.
         * @param node The root node of the BST or subtree to being searching from
         * @return Returns the node with the largest value in the BST or subtree
         */
        Node<T>* FindMax(Node<T>*& node) {
            Node<T>* maxNode = node;

            while (maxNode->m_right != nullptr)
                maxNode = maxNode->m_right;

            return maxNode;
        }

        /**
         * @brief The Remove() function removes a node from the BST.
         * @param node The root node of the BST or subtree to being searching from
         * @param elem The value of the node to be removed
         * @return Returns the node removed
         */
        Node<T>* Remove(Node<T>*& node, T elem) {
            if (node == nullptr)
                return nullptr;

            /// Dig left if node is smaller than the root, otherwise dig right.
            if (elem < node->m_data)
                node->m_left = Remove(node->m_left, elem);
            else if (elem > node->m_data)
                node->m_right = Remove(node->m_right, elem);
            else {
                /// Check for left, right, or no subtree. If node has two links, find the largest
                /// value in the left subtree (could also be the smallest value in the right subtree).
                if (node->m_left == nullptr)
                    return node->m_right;
                else if (node->m_right == nullptr)
                    return node->m_left;
                else {
                    tmp = FindMax(node->m_left);

                    /// Swap nodes, then remove the node we found to swap with.
                    node->m_data = tmp->m_data;
                    node->m_left = Remove(node->m_left, tmp->m_data);
                    
                    delete tmp;
                }
            }

            return node;
        }

        /**
         * @brief The Height() function returns the height of the BST.
         * @param node The root node of the BST
         * @return Returns the height of the left or right subtree, whichever is greater
         */
        int Height(Node<T>*& node) {
            /// If node is not null, compute left and right subtrees
            if (node == nullptr)
                return 0;
            else {
                int lHeight = Height(node->m_left);
                int rHeight = Height(node->m_right);

                /// Check height of each subtree and return largest
                if (lHeight > rHeight)
                    return (lHeight + 1);
                else
                    return (rHeight + 1);
            }
        }

        /**
         * @brief The ClearTree() function iterates over the BST via level order traversal utilizing
         * the nodes queue, simultaneously storing each node in the removal queue to be deleted.
         * @param node The node to begin the traversal from (typically the root of the BST)
         */
        void ClearTree(Node<T>*& node) {
            if (node == nullptr)
                return;

            std::queue<Node<T>*> nodes;
            std::queue<Node<T>*> removal;
            nodes.emplace(node);

            /// Begin level order traversal
            while (!nodes.empty()) {
                Node<T>* node = nodes.front();
                removal.emplace(node);

                nodes.pop();

                if (node->m_left != nullptr)
                    nodes.emplace(node->m_left);

                if (node->m_right != nullptr)
                    nodes.emplace(node->m_right);
            }

            int nodesRemoved = 0;

            /// Deallocate Node memory utilizing removal queue 
            while (!removal.empty()) {
                delete removal.front();

                removal.pop();
                nodesRemoved++;
            }
        }

        /// @brief The PreOrder() function prints all of the node values in the BST via pre-order traversal.
        /// @param node The root node of the BST
        void PreOrder(Node<T>*& node) {
            if (node == nullptr)
                return;

            std::cout << node->m_data << " ";
            PreOrder(node->m_left);
            PreOrder(node->m_right);
        }

        /// @brief The InOrder() function prints all of the node values in the BST in ascending order.
        /// @param node The root node of the BST
        void InOrder(Node<T>*& node) {
            if (node == nullptr)
                return;

            InOrder(node->m_left);
            std::cout << node->m_data << " ";
            InOrder(node->m_right);
        }

        /// @brief The PostOrder() function prints all of the node values in the BST via post-order traversal.
        /// @param node The root node of the BST
        void PostOrder(Node<T>*& node) {
            if (node == nullptr)
                return;

            PostOrder(node->m_left);
            PostOrder(node->m_right);
            std::cout << node->m_data << " ";
        }

        /// @brief The LevelOrder() function performs a breadth-first-search using a queue.
        /// @param node The root node of the BST
        void LevelOrder(Node<T>*& node) {
            if (node == nullptr)
                return;

            std::queue<Node<T>*> nodes;
            nodes.emplace(node);

            while (!nodes.empty()) {
                Node<T>* node = nodes.front();
                std::cout << node->m_data << " ";
                nodes.pop();

                if (node->m_left != nullptr)
                    nodes.emplace(node->m_left);

                if (node->m_right != nullptr)
                    nodes.emplace(node->m_right);
            }
        }

    public: 
        /// @brief BinarySearchTree constructor and destructor
        BinarySearchTree() {}

        ~BinarySearchTree() {
            /// TODO check if BST is already empty
            Clear();
        }

        /// @brief The Display() function displays the values of all nodes in the BST in pre-order, in-order, post-order,
        /// and level-order. It then provides the total count of all the nodes in the BST.
        void Display() {
            std::cout << "\nPrinting Binary Search Tree values..." << std::endl;
            std::cout << "Node values in pre-order: " << std::endl;
            PreOrder(root);
            std::cout << "\nNode values in order: " << std::endl;
            InOrder(root);
            std::cout << "\nNode values in post-order: " << std::endl;
            PostOrder(root);
            std::cout << "\nNode values via level order traversal (breadth first search): " << std::endl;
            LevelOrder(root);
            std::cout << "\nTotal of " << nodeCount << " nodes in tree." << std::endl;
        }

        /// @brief The Min() function allows the main function to call FindMin().
        void Min() {
            std::cout << "\nFinding the minimum value..." << std::endl;
            std::cout << "Minimum value: " << FindMin(root)->m_data << std::endl;
        }

        /// @brief The Max() function allows the main function to call FindMax().
        void Max() {
            std::cout << "\nFinding the maximum value..." << std::endl;
            std::cout << "Maximum value: " << FindMax(root)->m_data << std::endl;
        }

        /// @brief The GetHeight() function allows the main function to call Height().
        void GetHeight() {
            std::cout << "\nThe height of the Binary Search Tree is: " << Height(root) << std::endl;
        }

        /**
         * @brief The Add(T elem) function attempts to add an element to the BST and returns true if it
         * is successful.
         * @param elem The value of the node to be added to the BST
         */
        bool Add(T elem) {
            if (Contains(elem)) {
                return false;
            } else {
                root = Add(root, elem);
                nodeCount++;
                return true;
            }
        }

        /// @brief The Rem() function allows the main function to call remove().
        /// @param elem The value of the node to be removed from the BST
        void Rem(T elem) {
            std::cout << "\nRemoving node that contains: " << elem << std::endl;
            Remove(root, elem);
            nodeCount--;
        }

        /// @brief The Clear() function removes the remaining nodes from the BST.
        void Clear() {
            std::cout << "\nClearing BST" << std::endl;
            ClearTree(root);
        }

};