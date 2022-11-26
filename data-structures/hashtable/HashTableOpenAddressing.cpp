#include "LinearProbing.h"

/**
 * @file HashTableOpenAddressing.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Functional demonstration of the HashTable class
 */

std::vector<int> keys = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};                        // int keys
std::vector<char> keys1 = {'A', 'B', 'C', 'd', 'e', 'f', 'g', 'h', 'Z', 'U', 't'};      // char keys
std::vector<int> values = {123, 234, 345, 456, 567, 678, 789, 890, 111, 222, 333};      // int values
std::vector<std::string> values1 = {"test", "being", "retro", "lash", "blue", "lost"};  // string values
int rem = 3;                                                                            // int key to remove
char rem1 = 'C';                                                                        // char key to remove

int main() {
    LinearProbing<char, std::string> hashTable;

    // Check that the hash table has been initialized
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking capacity and load factor..." << std::endl;
    std::cout << "Capacity: " << hashTable.GetCapacity() << std::endl;
    std::cout << "Load Factor: " << hashTable.GetLoadFactor() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Insert items into the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Populating hash table..." << std::endl;

    for (int i = 0; i < values1.size(); i++)
        hashTable.Insert(keys1[i], values1[i]);

    std::cout << "Items added!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Check if a key exists in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    
    for (int i = 1; i < values1.size(); i++) 
    {
        if (hashTable.HasKey(keys1[i]))
            std::cout << "Hash table contains: " << keys1[i] << std::endl;
        else
            std::cout << "Hash table doesn't contain: " << keys1[i] << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    // Print all items currently in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Printing hash table key-value pairs..." << std::endl;
    hashTable.GetHashTableItems();
    std::cout << "\nHash table size: " << hashTable.Size() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove a key-value pair from the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing key " << rem1 << " from the hash table..." << std::endl;
    std::string removed = hashTable.Remove(rem1);

    if (removed != "")
        std::cout << "Value of " << rem1 << " is " << removed << ", and was removed" << std::endl;
    else
        std::cout << "Key not found" << std::endl;

    std::cout << "------------------------------------------------------" << std::endl;

    // Get the corresponding value of a key
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Getting the value of key " << keys1[2] << "..." << std::endl;
    std::string val = hashTable.GetValue(keys1[2]);
    std::cout << "The value of " << keys1[2] << " is: " << val << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Print all items currently in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Printing hash table key-value pairs..." << std::endl;
    hashTable.GetHashTableItems();
    std::cout << "\nHash table size: " << hashTable.Size() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    // Clear all values in the hash table
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Clearing table..." << std::endl;
    hashTable.Clear();
    std::cout << "Table cleared. Ending program...\nPress 'Enter' to continue..." << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
};