#include <iostream>
#include "HashTableOpenAddressing.h"

/**
 * @file HashTableOpenAddressing.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the HashTable class
 */

int main() {
    HashTable hashTable;

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking capacity and load factor..." << std::endl;
    std::cout << "Capacity: " << hashTable.GetCapacity() << std::endl;
    std::cout << "Load Factor: " << hashTable.GetLoadFactor() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Inserting key..." << std::endl;
    hashTable.Insert(1, 3);
    std::cout << "Item added!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Clearing table..." << std::endl;
    hashTable.Clear();
    std::cout << "Table cleared. Ending program..." << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
};