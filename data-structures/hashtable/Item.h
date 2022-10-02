#pragma once

/**
 * @file Item.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Item struct provides a framework for item creation in the HashTable class
 *        (HashTableOpenAddressing.h).
 */

template <typename T>

struct Item {

    template <typename U>
    friend class HashTable;

    private:
        T m_key = 0;                    /// The key of the key-value pair
        T m_value = 0;                  /// The value of the key-value pair
        bool m_tombstone = false;       /// Tombstone is used to mark deleted key-value pairs

    public:
        /// @brief Item constructors and destructor
        Item() {}

        /**
         * @param key The key of the key-value pair
         * @param value The value of the key-value pair
         * @param tombstone A placeholder for a deleted key-value pair
         */
        Item(T key, T value, bool tombstone) 
            : m_key(key), m_value(value), m_tombstone(tombstone) {
        }

        ~Item() {}

};