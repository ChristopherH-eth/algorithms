#pragma once

#include <iostream>
#include <map>

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Node struct contains the Node variables and pointers.
 */

class Node {
    friend class Trie;

    private:
        char m_ch;
        int count = 0;
        bool isWordEnding = false;
        std::map<char, Node*> children;

    public:
        /// @brief Node constructor and destructor
        /// @param ch Character value
        Node(char& ch) 
            : m_ch(ch) {
                for (char i = 'a'; i <= 'z'; i++) {
                    this->children.emplace(i, nullptr);
                }

                std::cout << "(Node created)" << std::endl;
            }

        /// Root node constructor
        Node(const char& ch) 
            : m_ch(ch) {
                for (char i = 'a'; i <= 'z'; i++) {
                    this->children.emplace(i, nullptr);
                }

                std::cout << "(Node created)" << std::endl;
            }

        ~Node() {
            std::cout << "(Node removed)" << std::endl;
        }

        /**
         * @brief The AddChild() function adds a child node to the current node's map
         * @param node The node to be added to the local map
         * @param c The char key of the local map
         */
        void AddChild(Node*& node, char c) {
            children.at(c) = node;
        }

        /// @brief The RemoveChild() function removes a child node from the current nodes map and resets it.
        /// @param c The key of the node to be removed
        void RemoveChild(char c) {
            children.erase(c);
            children.emplace(c, nullptr);
        }

};