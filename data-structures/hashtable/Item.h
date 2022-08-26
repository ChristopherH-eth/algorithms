#pragma once

/**
 * @file Item.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Item struct provides a framework for item creation in the HashTable class.
 */

struct Item {

    public:
        int key = 0;
        int value = 0;
        bool tombstone = false; // Tombstone is used to mark deleted key-value pairs
 
        Item() {}

        Item(int key, int value, bool tombstone) {
            this->key = key;
            this->value = value;
            this->tombstone = tombstone;
        }

};