#pragma once

/**
 * @file Item.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief The Item struct provides a framework for item creation in the HashTable class
 *      (HashTableOpenAddressing.h).
 */

template <typename T, typename U>

struct Item {

    template <typename V, typename W>
    friend class HashTable;

    // Check instantiation type (valid: double, float, int, char)
    static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value || 
        std::is_same<T, int>::value || std::is_same<T, char>::value, "Invalid type");

    static_assert(std::is_same<U, double>::value || std::is_same<U, float>::value || 
        std::is_same<U, int>::value || std::is_same<U, char>::value || std::is_same<U, std::string>::value, 
        "Invalid type");

    private:
        T m_key = 0;                    // The key of the key-value pair
        U m_value;                      // The value of the key-value pair
        bool m_tombstone = false;       // Tombstone is used to mark deleted key-value pairs

    public:
        /**
         * @brief Item constructors and destructor
         */
        Item() 
        {

        }

        /**
         * @param key The key of the key-value pair
         * @param value The value of the key-value pair
         * @param tombstone A placeholder for a deleted key-value pair
         */
        Item(T key, U value, bool tombstone) 
            : m_key(key), m_value(value), m_tombstone(tombstone) 
        {

        }

        ~Item() 
        {

        }

};