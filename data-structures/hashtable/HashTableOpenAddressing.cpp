#include <iostream>
#include "LinearProbing.h"

/**
 * @file HashTableOpenAddressing.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the HashTable class
 */

int keys[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
char _keys[] = {'A', 'B', 'C', 'd', 'e', 'f', 'g', 'h', 'Z', 'U', 't'};
int values[] = {123, 234, 345, 456, 567, 678, 789, 890, 111, 222, 333};
int rem = 11;

int main() {
    LinearProbing hashTable;

    /// @see Check that the hash table has been initialized
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking capacity and load factor..." << std::endl;
    std::cout << "Capacity: " << hashTable.GetCapacity() << std::endl;
    std::cout << "Load Factor: " << hashTable.GetLoadFactor() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Insert items into the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Populating hash table..." << std::endl;

    for (int i = 0; i < (sizeof(keys)/sizeof(int)); i++) {
        hashTable.Insert(keys[i], values[i]);
    }

    std::cout << "Items added!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Check if a key exists in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    
    for (int i = 1; i < 15; i++) {
        if (hashTable.HasKey(i)) {
            std::cout << "Hash table contains: " << i << std::endl;
        } else {
            std::cout << "Hash table doesn't contain: " << i << std::endl;
        }
    }

    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Print all items currently in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Printing hash table key-value pairs..." << std::endl;
    hashTable.GetHashTableItems();
    std::cout << "\nHash table size: " << hashTable.Size() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Remove a key-value pair from the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing key " << rem << " from the hash table..." << std::endl;
    int removed = hashTable.Remove(rem);

    if (removed) {
        std::cout << "Value of " << rem << " is " << removed << ", and was removed" << std::endl;
    } else {
        std::cout << "Key not found" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Get the corresponding value of a key
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Getting the value of key " << keys[10] << "..." << std::endl;
    int val = hashTable.GetValue(keys[10]);
    std::cout << "The value of " << keys[10] << " is: " << val << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Print all items currently in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Printing hash table key-value pairs..." << std::endl;
    hashTable.GetHashTableItems();
    std::cout << "\nHash table size: " << hashTable.Size() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Clear all values in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Clearing table..." << std::endl;
    hashTable.Clear();
    std::cout << "Table cleared. Ending program...\nPress 'Enter' to continue..." << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
};