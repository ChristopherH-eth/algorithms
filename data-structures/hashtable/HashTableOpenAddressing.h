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
 * @brief HashTable implementation which allows users to construct hash tables either with
 *        default dimensions, or dimensions of their own. Once created, a user can insert new
 *        items, remove items, check if certain keys exist, print the current key-value pairs
 *        stored in the hash table, and return the value of a pair using its key. The hash
 *        table automatically resizes once a certain threshold has been met, and will 
 *        optimize itself while doing so. It also has built in optimizations when performing
 *        insert, remove, and value check functions.
 * 
 *        Open Addressing is used to resolve hash collisions, and this table currently uses
 *        a linear probing method (found in LinearProbing.h of this repository).
 * 
 *        Best case time complexity (Search, Insert, Delete):   O(1)
 *        Worst case time complexity (Search, Insert, Delete):  O(n)
 */

class HashTable {

    protected:
        double loadFactor;
        int capacity, threshold;
        int modificationCount, usedBuckets, keyCount;
        std::vector<Item> items;
        std::hash<int> keyHash;

        /// Hash table iterators
        std::list<int> keyList;
        std::list<int> valueList;
        typedef std::list<int>::iterator keyIt;
        typedef std::list<int>::iterator valueIt;

        /// Default starting size values of a hash table
        static int const DEFAULT_CAPACITY = 7;
        static double constexpr DEFAULT_LOAD_FACTOR = 0.65;

        /// @see These three virtual functions are used based on the desired open addressing scheme.
        /// @param key The key to probe for
        virtual void SetupProbing(int key) {
            return;
        }

        /// @see The Probe() function determines the next bucket to probe for the key
        /// @param x The given probing iteration
        virtual int Probe(int x) {
            return 0;
        }

        
        /// @see The AdjustCapacity() function adjusts the capacity of the hash table such that
        /// the GCD (greatest common denominator) of the LINEAR_CONSTANT and the capacity is 1.
        virtual void AdjustCapacity() {
            return;
        }

        /// @see The IncreaseCapacity() function doubles the hash table capacity.
        void IncreaseCapacity() {
            capacity = (2 * capacity) + 1;
        }

        /// @see The ResizeTable() function doubles the size of the hash table once the capacity threshold
        /// has been met.
        void ResizeTable() {
            std::cout << "Table threshold reached, increasing capacity..." << std::endl;
            int oldCapacity = capacity;

            IncreaseCapacity();
            AdjustCapacity();

            threshold = (int) (capacity * loadFactor);
            keyCount = usedBuckets = 0;

            /// Copy the original vector into a temporary vector.
            std::vector<Item> tmpItems(items);

            /// Empty the original vector and resize to new capacity.
            for (int i = 0; i < oldCapacity; i++) {
                items.pop_back();
            }

            items.resize(capacity);
            std::cout << "Table resized, new capacity: " << capacity << std::endl;

            /// Reinsert the original items into the resized array
            for (int i = 0; i < oldCapacity; i++) {
                if (tmpItems[i].key != 0 && tmpItems[i].tombstone == false) {
                    Insert(tmpItems[i].key, tmpItems[i].value);
                }
            }
        }

        /**
         * @see The NoramlizeIndex() function converts a hash value to an index in the domain [0, capacity).
         * @param keyHash The hash value of the current key
         * @return The hash value modulo the table capacity so we get a value in bounds
         */
        int NormalizeIndex(int keyHash) {
            return (keyHash % capacity);
        }

        /**
         * @see The GCD() function finds the greatest common denominator of the linear constant (a) and the
         * capacity (b).
         * @param a The linear constant (see LinearProbing.h)
         * @param b The table capacity
         * @return Returns a if b == 0, otherwise returns the capacity value of a % b
         */
        static int GCD(int a, int b) {
            if (b == 0) {
                return a;
            }

            return GCD(b, a % b);
        }

    public:
        /// @see Hash table constructors
        HashTable() {
            this->loadFactor = DEFAULT_LOAD_FACTOR;
            this->capacity = DEFAULT_CAPACITY;
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;
            items.resize(DEFAULT_CAPACITY);
        }

        /// @param capacity The pre-defined capacity of the hash table
        HashTable(int capacity) {
            /// Check for valid capacity
            if (capacity <= 0) {
                throw "Illegal capacity";
            }

            this->loadFactor = DEFAULT_LOAD_FACTOR;
            this->capacity = fmax(DEFAULT_CAPACITY, capacity);
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;
            items.resize(DEFAULT_CAPACITY);
        }

        /// @param capacity The pre-defined capacity of the hash table
        /// @param loadFactor The pre-defined load factor of the hash table
        HashTable(int capacity, double loadFactor) {
            /// Check for valid capacity and load factor
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

        /// @see The Clear() function clears all heap allocated data in the hash table.
        void Clear() {
            for (int i = 0; i < capacity; i++) {
                items.pop_back();
            }

            keyCount = usedBuckets = 0;
            modificationCount++;
        }

        /// @see The Size() function returns the number of items currently inside the hash table
        /// @return Returns the key count of the hash table
        int Size() {
            return keyCount;
        }

        /// @see The GetCapacity() function returns the capacity of the hash table
        /// @return Returns the hash table capacity
        int GetCapacity() { 
            return capacity; 
        }

        /// @see The GetLoadFactor() function returns the load factor of the hash table
        /// @return Returns the current hash table load factor
        double GetLoadFactor() {
            return loadFactor;
        }

        /// @see The IsEmpty() function returns true if the hash table is empty
        /// @return Returns true if the hash table is empty
        bool IsEmpty() {
            return keyCount == 0;
        }

        /// @see The KeyList() function returns an index ordered list of hash table keys.
        /// @return Returns a list of keys
        std::list<int> KeyList() {
            /// Make sure the list is empty
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

        /// @see The ValueList() function returns an index ordered list of hash table values.
        /// @return Returns a list of values
        std::list<int> ValueList() {
            /// Make sure the list is empty
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

        /// @see The GetHashTableItems() function prints the hash table contents to the console by index.
        void GetHashTableItems() {
            std::list<int> keyList = KeyList();
            std::list<int> valueList = ValueList();

            for (std::pair<keyIt, valueIt> i(keyList.begin(), valueList.begin()); 
                i.first != keyList.end() && i.second != valueList.end(); i.first++, i.second++) {
                std::cout << "[" << *i.first << ", " << *i.second << "] ";
            }
        }

        /**
         * @see The Insert() function inserts a key-value pair into the hash table. If the key already exists,
         * the value is updated. If the table threshold has been reached, the hash table is resized.
         * @param key The key of the key-value pair to be inserted
         * @param value The value of the key-value pair to be inserted
         * @return Returns either the updated key-value pair, or the newly inserted pair
         */
        Item Insert(int key, int value) {
            if (key == 0 || !key) {
                throw "Empty key";
            } else if (usedBuckets >= threshold) {
                ResizeTable();
            }

            /// Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                /// Check if current index was previously deleted, contains a key, or is empty
                if (items[i].tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i].key != 0) {
                    /// The key we're trying to insert already exists, so update the value.
                    if (items[i].key == key) {
                        if (j == -1) {
                            items[i].value = value;
                            std::cout << "Key exists, updating value..." << std::endl;
                            modificationCount++;

                            return items[i];
                        } else {
                            items[j] = items[i];
                            items[i].key = 0;
                            items[i].value = 0;
                            items[i].tombstone = true;
                            modificationCount++;

                            return items[j];
                        }
                    }
                } else {
                    /// Current slot is empty so a new key-value pair can be inserted.
                    if (j == -1) {
                        usedBuckets++;
                        keyCount++;
                        items[i].key = key;
                        items[i].value = value;
                        std::cout << "Inserted [" << key << ", " << value << "] at index " << i << std::endl;
                        modificationCount++;

                        return items[i];
                    } else {
                        keyCount++;
                        items[j].key = key;
                        items[j].value = value;
                        std::cout << "Inserted [" << key << ", " << value << "] at index " << j << std::endl;
                        modificationCount++;

                        return items[j];
                    }
                }
            }
        }

        /**
         * @see The HasKey() function returns true if the key is contained within the hash table. The hash
         * table is optimized along the way if needed.
         * @param key The key to be searched for
         * @return Returns true if the key exists in the hash table
         */
        bool HasKey(int key) {
            if (key == 0 || !key) {
                throw "Empty key";
            }

            SetupProbing(key);
            /// Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            /// Start at the original hash value and probe until we find our key or an empty item,
            /// in which case our item does not exist.
            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                /// Ignore deleted cells, but record the first index in which one is encountered
                /// to perform lazy relocation later.
                if (items[i].tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i].key != 0) {
                    /// Check if we found the key we're looking for
                    if (items[i].key == key) {
                        /// Perform optimization if we've encountered a previously deleted cell
                        if (j != -1) {
                            items[j] = items[i];
                            items[i].key = 0;
                            items[i].value = 0;
                            items[i].tombstone = true;
                        } 

                        return true;
                    }
                } else {
                    return false;
                }
            }
        }

        /**
         * @see The GetValue() function returns a value for a given key, if such a key exists in the hash
         * table. The hash table is optimized along the way if needed.
         * @param key The key to be searched for
         * @return Returns the value of the key-value pair or 0 if the key doesn't exist
         */
        int GetValue(int key) {
            if (key == 0 || !key) {
                throw "Empty key";
            }

            SetupProbing(key);
            /// Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            /// Start at the original hash value and probe until we find our key or an empty item,
            /// in which case our item does not exist.
            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                /// Ignore deleted cells, but record the first index in which one is encountered
                /// to perform lazy relocation later.
                if (items[i].tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i].key != 0) {
                    /// Check if we found the key we're looking for
                    if (items[i].key == key) {
                        /// Perform optimization if we've encountered a previously deleted cell
                        if (j != -1) {
                            items[j] = items[i];
                            items[i].key = 0;
                            items[i].value = 0;
                            items[i].tombstone = true;

                            return items[j].value;
                        } else {
                            return items[i].value;
                        }
                    }
                } else {
                    return 0;
                }
            }
        }

        /**
         * @see The Remove() function removes a key-value pair from the hash table, adds a tombstone in its
         * place, and returns the value of the pair removed.
         * @param key The key to be searched for
         * @return Returns the value removed from the hash table or 0 if the key doesn't exist
         */
        int Remove(int key) {
            if (key == 0 || !key) {
                throw "Empty key";
            }

            SetupProbing(key);
            /// Hash the current key to be inserted and normalize to get the index
            int offset = NormalizeIndex(keyHash(key));

            /// Start at the original hash value and probe until we find our key or an empty item,
            /// in which case our item does not exist.
            for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) {
                /// Ignore deleted cells.
                if (items[i].tombstone == true) {
                    continue;
                } else if (items[i].key != 0) {
                    /// Check if we found the key we're looking for
                    if (items[i].key == key) {
                        keyCount--;
                        modificationCount++;
                        int oldValue = items[i].value;

                        items[i].key = 0;
                        items[i].value = 0;
                        items[i].tombstone = true;

                        return oldValue;
                    }
                } else {
                    return 0;
                }
            }
        }

};