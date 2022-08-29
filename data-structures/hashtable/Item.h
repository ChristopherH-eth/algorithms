#pragma once

/**
 * @file Item.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Item struct provides a framework for item creation in the HashTable class
 *        (HashTableOpenAddressing.h).
 */

struct Item {

    public:
        int key = 0;
        int value = 0;
        bool tombstone = false; /// Tombstone is used to mark deleted key-value pairs
 
        /// @see Item Constructors
        Item() {}

        /**
         * @param key The key of the key-value pair
         * @param value The value of the key-value pair
         * @param tombstone A placeholder for a deleted key-value pair
         */
        Item(int key, int value, bool tombstone) {
            this->key = key;
            this->value = value;
            this->tombstone = tombstone;
        }

};