#pragma once

#include <math.h>
#include <functional>
#include "Item.h"

/**
 * @file HashTableOpenAddressing.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief 
 */

class HashTable {

    protected:
        double loadFactor;
        int capacity, threshold;
        int modificationCount, usedBuckets, keyCount;
        Item* item; // Used to store key-value pairs
        std::hash<int> keyHash; // Used to hash keys in key-value pairs

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
            int oldCapacity = capacity;

            IncreaseCapacity();
            AdjustCapacity();

            threshold = (int) (capacity * loadFactor);
            keyCount = usedBuckets = 0;
            Item** tmpItems = new Item*[oldCapacity];

            // Copy the original array into a temporary array
            for (int i = 0; i < oldCapacity; i++) {
                tmpItems[i] = items[i];
                delete items[i];
            }

            // Delete the original array
            delete[] items;
            // Update original array capacity
            Item** items = new Item*[capacity];

            // Initialize the new resized array
            for (int i = 0; i < capacity; i++) {
                items[i] = new Item;
            }

            // Reinsert the original items into the resized array
            for (int i = 0; i < oldCapacity; i++) {
                if (tmpItems[i]->key != 0 && tmpItems[i]->tombstone == false) {
                    Insert(tmpItems[i]->key, tmpItems[i]->value);
                    delete tmpItems[i];
                }
            }

            // Cleanup the temporary array
            delete[] tmpItems;
        }

        // The NoramlizeIndex() function converts a hash value to an index in the domain [0, capacity).
        int NormalizeIndex(int keyHash) {
            return (keyHash & 0x7FFFFFFF) % capacity;
        }

        // The GCD() function finds the greatest common denominator of a and b
        static int GCD(int a, int b) {
            if (b == 0) {
                return a;
            }

            return GCD(b, a % b);
        }

        //Item* items[DEFAULT_CAPACITY] = {};
        Item** items = new Item*[DEFAULT_CAPACITY];

    public:
        // Hash table constructors
        HashTable() {
            this->loadFactor = DEFAULT_LOAD_FACTOR;
            this->capacity = DEFAULT_CAPACITY;
            threshold = (int) (this->capacity * this->loadFactor);
            modificationCount = usedBuckets = keyCount = 0;

            //Initialize blank array
            for (int i = 0; i < DEFAULT_CAPACITY; i++) {
                items[i] = new Item;
            }
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

            //Initialize blank array
            for (int i = 0; i < DEFAULT_CAPACITY; i++) {
                items[i] = new Item;
            }
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

            //Initialize blank array
            for (int i = 0; i < DEFAULT_CAPACITY; i++) {
                items[i] = new Item;
            }
        } 

        // The Clear() function clears all heap allocated data in the hash table.
        void Clear() {
            for (int i = 0; i < capacity; i++) {
                delete items[i];
            }

            delete[] items;

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
                if (items[i]->tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i]->key != 0) {
                    // The key we're trying to insert already exists, so update the value.
                    if (items[i]->key == key) {
                        int oldValue = items[i]->value;

                        if (j == -1) {
                            items[i]->value = value;
                        } else {
                            items[i] = item;
                        }

                        modificationCount++;

                        return;
                    }
                } else {
                    // Current slot is empty so a new key-value pair can be inserted.
                    if (j == -1) {
                        usedBuckets++;
                        keyCount++;
                        items[i]->key = key;
                        items[i]->value = value;
                    } else {
                        keyCount++;
                        items[j]->key = key;
                        items[j]->value = value;
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
                if (items[i]->tombstone == true) {
                    if (j == -1) {
                        j = i;
                    }
                } else if (items[i]->key != 0) {
                    // Check if we found the key we're looking for
                    if (items[i]->key == key) {
                        // Perform optimization if we've encountered a previously deleted cell
                        if (j != -1) {
                            items[j]->key = items[i]->key;
                            items[j]->value = items[i]->value;
                            items[j]->tombstone = items[i]->tombstone;

                            // Memory cleanup
                            delete items[i];
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