#pragma once

#include <iostream>
#include <math.h>
#include <functional>
#include <utility>
#include <list>
#include <vector>
#include "Item.h"

/**
 * @file HashTableOpenAddressing.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief HashTable implementation
 */

class HashTable {

    protected:
        double loadFactor;
        int capacity, threshold;
        int modificationCount, usedBuckets, keyCount;
        std::vector<Item> items;
        std::hash<int> keyHash; // Used to hash keys in key-value pairs

        // Hash table iterators
        std::list<int> keyList;
        std::list<int> valueList;
        typedef std::list<int>::iterator keyIt;
        typedef std::list<int>::iterator valueIt;

        // Starting size values of a hash table
        static int const DEFAULT_CAPACITY = 7;
        static double constexpr DEFAULT_LOAD_FACTOR = 0.65;

        // These three virtual functions are used based on the desired open addressing scheme.
        virtual void SetupProbing(int key) {
            return;
        }

        virtual int Probe(int x) {
            return 0;
        }

        virtual void AdjustCapacity() {
            return;
        }

        // The IncreaseCapacity() function doubles the hash table capacity.
        void IncreaseCapacity() {
            capacity = (2 * capacity) + 1;
        }

        // The ResizeTable() function doubles the size of the hash table once the capacity threshold
        // has been met.
        void ResizeTable() {
            std::cout << "Table threshold reached, increasing capacity..." << std::endl;
            int oldCapacity = capacity;

            IncreaseCapacity();
            AdjustCapacity();

            threshold = (int) (capacity * loadFactor);
            keyCount = usedBuckets = 0;

            // Copy the original vector into a temporary vector.
            std::vector<Item> tmpItems(items);

            // Empty the original vector and resize to new capacity.
            for (int i = 0; i < oldCapacity; i++) {
                items.pop_back();
            }

            items.resize(capacity);
            std::cout << "Table resized, new capacity: " << capacity << std::endl;

            // Reinsert the original items into the resized array
            for (int i = 0; i < oldCapacity; i++) {
                if (tmpItems[i].key != 0 && tmpItems[i].tombstone == false) {
                    Insert(tmpItems[i].key, tmpItems[i].value);
                }
            }
        }

        // The NoramlizeIndex() function converts a hash value to an index in the domain [0, capacity).
        int NormalizeIndex(int keyHash) {
            return (keyHash % capacity);
        }

        // The GCD() function finds the greatest common denominator of a and b
        static int GCD(int a, int b) {
            if (b == 0) {
                return a;
            }

            return GCD(b, a % b);
        }

    public:
        // Hash table constructors
        HashTable() {
            this->loadFactor = DEFAULT_LOAD_FACTOR;
            this->capacity = DEFAULT_CAPACITY;
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;
            items.resize(DEFAULT_CAPACITY);
        }

        HashTable(int capacity) {
            // Check for valid capacity
            if (capacity <= 0) {
                throw "Illegal capacity";
            }

            this->loadFactor = DEFAULT_LOAD_FACTOR;
            this->capacity = fmax(DEFAULT_CAPACITY, capacity);
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;
            items.resize(DEFAULT_CAPACITY);
        }

        HashTable(int capacity, double loadFactor) {
            // Check for valid capacity and load factor
            if (capacity <= 0) {
                throw "Illegal capacity";
            } else if (loadFactor <= 0 || isnan(loadFactor) || isinf(loadFactor)) {
                throw "Illegal load factor";
            }

            this->loadFactor = loadFactor;
            this->capacity = fmax(DEFAULT_CAPACITY, capacity);
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;
            items.resize(DEFAULT_CAPACITY);
        } 

        // The Clear() function clears all heap allocated data in the hash table.
        void Clear() {
            for (int i = 0; i < capacity; i++) {
                items.pop_back();
            }

            keyCount = usedBuckets = 0;
            modificationCount++;
        }

        // The Size() function returns the number of items currently inside the hash table
        int Size() {
            return keyCount;
        }

        // The GetCapacity() function returns the capacity of the hash table
        int GetCapacity() { 
            return capacity; 
        }

        // The GetLoadFactor() function returns the load factor of the hash table
        double GetLoadFactor() {
            return loadFactor;
        }

        // The IsEmpty() function returns true if the hash table is empty
        bool IsEmpty() {
            return keyCount == 0;
        }

        // The KeyList() function returns an index ordered list of hash table keys.
        std::list<int> KeyList() {
            // Make sure the list is empty
            if (!keyList.empty()) {
                while (!keyList.empty()) {
                    keyList.pop_back();
                }
            }

            for (int i = 0; i < capacity; i++) {
                if (items[i].key != 0 && items[i].tombstone == false) {
                    keyList.push_back(items[i].key);
                }
            }

            return keyList;
        }

        // The ValueList() function returns an index ordered list of hash table values.
        std::list<int> ValueList() {
            // Make sure the list is empty
            if (!valueList.empty()) {
                while (!valueList.empty()) {
                    valueList.pop_back();
                }
            }

            for (int i = 0; i < capacity; i++) {
                if (items[i].key != 0 && items[i].tombstone == false) {
                    valueList.push_back(items[i].value);
                }
            }

            return valueList;
        }

        // The GetHashTableItems() function prints the hash table contents to the console by index.
        void GetHashTableItems() {
            std::list<int> keyList = KeyList();
            std::list<int> valueList = ValueList();

            for (std::pair<keyIt, valueIt> i(keyList.begin(), valueList.begin()); 
                i.first != keyList.end() && i.second != valueList.end(); i.first++, i.second++) {
                std::cout << "[" << *i.first << ", " << *i.second << "] ";
            }
        }

        // The Insert() function inserts a key-value pair into the hash table. If the key already exists,
        // the value is updated.
        void Insert(int key, int value) {
            if (key == 0) {
                throw "Empty key";
            } else if (usedBuckets >= threshold) {
                ResizeTable();
            }

            // Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                // Check if current index was previously deleted, contains a key, or is empty
                if (items[i].tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i].key != 0) {
                    // The key we're trying to insert already exists, so update the value.
                    if (items[i].key == key) {
                        if (j == -1) {
                            items[i].value = value;
                            std::cout << "Key exists, updating value..." << std::endl;
                        } else {
                            items[j] = items[i];
                        }

                        modificationCount++;

                        return;
                    }
                } else {
                    // Current slot is empty so a new key-value pair can be inserted.
                    if (j == -1) {
                        usedBuckets++;
                        keyCount++;
                        items[i].key = key;
                        items[i].value = value;
                        std::cout << "Inserted [" << key << ", " << value << "] at index " << i << std::endl;
                    } else {
                        keyCount++;
                        items[j].key = key;
                        items[j].value = value;
                        std::cout << "Inserted [" << key << ", " << value << "] at index " << j << std::endl;
                    }

                    modificationCount++;

                    return;
                }
            }
        }

        // The HasKey() function returns true if the key is contained within the hash table.
        bool HasKey(int key) {
            if (key == 0) {
                throw "Empty key";
            }

            SetupProbing(key);
            // Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            // Start at the original hash value and probe until we find our key or an empty item,
            // in which case our item does not exist.
            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                // Ignore deleted cells, but record the first index in which one is encountered
                // to perform lazy relocation later.
                if (items[i].tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i].key != 0) {
                    // Check if we found the key we're looking for
                    if (items[i].key == key) {
                        // Perform optimization if we've encountered a previously deleted cell
                        if (j != -1) {
                            items[j].key = items[i].key;
                            items[j].value = items[i].value;
                            items[j].tombstone = items[i].tombstone;
                        } 

                        return true;
                    }
                } else {
                    // Key was not found
                    return false;
                }
            }
        }


};