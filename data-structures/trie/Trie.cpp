#include <iostream>
#include <string>
#include "Trie.h"

/**
 * @file Trie.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the Trie data structure
 */

std::string keys[] = {"this", "that", "thankful", "solo"};          /// Strings to be added to the Trie
std::string testKey = "cat";                                        /// Key to check if contained within the Trie
std::string removeKey = "that";                                     /// String to remove from Trie

int main() {
    Trie trie;

    /// @brief Insert key array into Trie
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Inserting keys..." << std::endl;

    for (int i = 0; i < 4; i++)
        trie.Insert(keys[i]);

    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Check if keys exist
    std::cout << "------------------------------------------------------" << std::endl;

    if (trie.Contains(keys[3]))
        std::cout << "The Trie contains \"" << keys[3] << "\"" << std::endl;
    else
        std::cout << "The Trie doesn't contain \"" << keys[3] << "\"" << std::endl;

    if (trie.Contains(testKey))
        std::cout << "The Trie contains \"" << testKey << "\"" << std::endl;
    else
        std::cout << "The Trie doesn't contain \"" << testKey << "\"" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Remove particular key
    std::cout << "------------------------------------------------------" << std::endl;

    if (trie.Contains(removeKey))
        std::cout << "The Trie contains \"" << removeKey << "\"" << std::endl;
    else
        std::cout << "The Trie doesn't contain \"" << removeKey << "\"" << std::endl;

    std::cout << "Removing \"" << removeKey << "\"..." << std::endl;
    trie.Remove(removeKey);

    if (trie.Contains(removeKey))
        std::cout << "The Trie contains \"" << removeKey << "\"" << std::endl;
    else
        std::cout << "The Trie doesn't contain \"" << removeKey << "\"" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Clear trie
    std::cout << "------------------------------------------------------" << std::endl;
    trie.Clear();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}