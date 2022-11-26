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

// TODO: Fix hashing for floats/doubles

template <typename T, typename U>

class HashTable {

    // Check instantiation type (valid: double, float, int, char)
    static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value || 
        std::is_same<T, int>::value || std::is_same<T, char>::value, "Invalid type");

    static_assert(std::is_same<U, double>::value || std::is_same<U, float>::value || 
        std::is_same<U, int>::value || std::is_same<U, char>::value, "Invalid type");

    protected:
    double m_loadFactor;                                    // Ratio before table resize
    int m_capacity;                                         // Total number of buckets
    int threshold;                                          // Number of key-value pairs allowed before resize
    int modificationCount;                                  // Number of modifications made to the HashTable
    int usedBuckets;                                        // Number of buckets containing key-value pairs
    int keyCount;                                           // Number of keys in the HashTable
    std::vector<Item<T, U>> items;                          // HashTable representation in vector format
    std::hash<T> keyHash;                                   // Hash function for keys

    std::list<T> keyList;                                   // List of HashTable keys
    std::list<U> valueList;                                 // List of Hashtable values
    typename std::list<T>::iterator keyIt;                  // Key iterator
    typename std::list<U>::iterator valueIt;                // Value iterator

    static int const DEFAULT_CAPACITY = 7;                  // Default capacity if one is not provided
    static double constexpr DEFAULT_LOAD_FACTOR = 0.65;     // Default load factor if one is not provided

    /**
     * @brief These three virtual functions are used based on the desired open addressing scheme.
     * @param key The key to probe for
     */
    virtual void SetupProbing(T key) const = 0;

    /**
     * @brief The Probe() function determines the next bucket to probe for the key
     * @param x The given probing iteration
     */
    virtual int Probe(int x) const = 0;

    /**
     * @brief The AdjustCapacity() function adjusts the capacity of the hash table such that
     *      the GCD (greatest common denominator) of the LINEAR_CONSTANT and the capacity is 1.
     */
    virtual void AdjustCapacity(int capacity) const = 0;

    /**
     * @brief The IncreaseCapacity() function doubles the hash table capacity.
     */
    void IncreaseCapacity() 
    {
        m_capacity = (2 * m_capacity) + 1;
    }

    /**
     * @brief The ResizeTable() function doubles the size of the hash table once the capacity threshold
     *      has been met.
     */
    void ResizeTable() 
    {
        std::cout << "Table threshold reached, increasing capacity..." << std::endl;
        int oldCapacity = m_capacity;

        IncreaseCapacity();
        AdjustCapacity(m_capacity);

        threshold = (int) (m_capacity * m_loadFactor);
        keyCount = usedBuckets = 0;

        // Copy the original vector into a temporary vector.
        std::vector<Item<T, U>> tmpItems(items);

        // Empty the original vector and resize to new capacity.
        for (int i = 0; i < oldCapacity; i++)
            items.pop_back();

        items.resize(m_capacity);
        std::cout << "Table resized, new capacity: " << m_capacity << std::endl;

        // Reinsert the original items into the resized array
        for (int i = 0; i < oldCapacity; i++) 
        {
            if (tmpItems[i].m_key != 0 && tmpItems[i].m_tombstone == false)
                Insert(tmpItems[i].m_key, tmpItems[i].m_value);
        }
    }

    /**
     * @brief The NoramlizeIndex() function converts a hash value to an index in the domain [0, capacity).
     * @param keyHash The hash value of the current key
     * @return The hash value modulo the table capacity so we get a value in bounds
     */
    int NormalizeIndex(int keyHash) 
    {
        return (keyHash % m_capacity);
    }

    /**
     * @brief The GCD() function finds the greatest common denominator of the linear constant (a) and the
     * capacity (b).
     * @param a The linear constant (see LinearProbing.h)
     * @param b The table capacity
     * @return Returns a if b == 0, otherwise returns the capacity value of a % b
     */
    static int GCD(int a, int b) 
    {
        if (b == 0)
            return a;

        return GCD(b, a % b);
    }

    public:
    /**
     * @brief Hash table constructors and destructor
     */
    HashTable() 
    {
        // Use default capacity and load factor values
        this->m_loadFactor = DEFAULT_LOAD_FACTOR;
        this->m_capacity = DEFAULT_CAPACITY;
        threshold = (int) (this->m_capacity * this->m_loadFactor);
        modificationCount = usedBuckets = keyCount = 0;
        items.resize(DEFAULT_CAPACITY);
    }

    /**
     * @param capacity The pre-defined capacity of the hash table
     */
    HashTable(int capacity) 
        : m_capacity(capacity) 
    {
        // Check for valid capacity
        if (capacity <= 0)
            throw "Illegal capacity";

        this->m_loadFactor = DEFAULT_LOAD_FACTOR;
        this->capacity = fmax(DEFAULT_CAPACITY, capacity);
        threshold = (int) (this->capacity * this->m_loadFactor);
        modificationCount = usedBuckets = keyCount = 0;
        items.resize(DEFAULT_CAPACITY);
    }

    /**
     * @param capacity The pre-defined capacity of the hash table
     * @param loadFactor The pre-defined load factor of the hash table
     */
    HashTable(int capacity, double loadFactor) 
        : m_capacity(capacity), m_loadFactor(loadFactor) 
    {
        // Check for valid capacity and load factor
        if (capacity <= 0)
            throw "Illegal capacity";
        else if (loadFactor <= 0 || isnan(loadFactor) || isinf(loadFactor))
            throw "Illegal load factor";

        this->loadFactor = loadFactor;
        this->capacity = fmax(DEFAULT_CAPACITY, capacity);
        threshold = (int) (this->capacity * this->loadFactor);
        modificationCount = usedBuckets = keyCount = 0;
        items.resize(DEFAULT_CAPACITY);
    } 

    virtual ~HashTable() 
    {

    }

    /**
     * @brief The Clear() function clears all heap allocated data in the hash table.
     */
    void Clear() 
    {
        for (int i = 0; i < m_capacity; i++)
            items.pop_back();

        keyCount = usedBuckets = 0;
        modificationCount++;
    }

    /**
     * @brief The Size() function returns the number of items currently inside the hash table
     * @return Returns the key count of the hash table
     */
    int Size() 
    {
        return keyCount;
    }

    /**
     * @brief The GetCapacity() function returns the capacity of the hash table
     * @return Returns the hash table capacity
     */
    int GetCapacity() 
    { 
        return m_capacity; 
    }

    /**
     * @brief The GetLoadFactor() function returns the load factor of the hash table
     * @return Returns the current hash table load factor
     */
    double GetLoadFactor() 
    {
        return m_loadFactor;
    }

    /**
     * @brief The IsEmpty() function returns true if the hash table is empty
     * @return Returns true if the hash table is empty
     */
    bool IsEmpty() 
    {
        return keyCount == 0;
    }

    /**
     * @brief The KeyList() function returns an index ordered list of hash table keys.
     * @return Returns a list of keys
     */
    std::list<T> KeyList() 
    {
        // Make sure the list is empty
        if (!keyList.empty()) 
        {
            while (!keyList.empty())
                keyList.pop_back();
        }

        for (int i = 0; i < m_capacity; i++) 
        {
            if (items[i].m_key != 0 && items[i].m_tombstone == false)
                keyList.emplace_back(items[i].m_key);
        }

        return keyList;
    }

    /**
     * @brief The ValueList() function returns an index ordered list of hash table values.
     * @return Returns a list of values
     */
    std::list<U> ValueList() 
    {
        // Make sure the list is empty
        if (!valueList.empty()) 
        {
            while (!valueList.empty())
                valueList.pop_back();
        }

        for (int i = 0; i < m_capacity; i++) 
        {
            if (items[i].m_key != 0 && items[i].m_tombstone == false)
                valueList.emplace_back(items[i].m_value);
        }

        return valueList;
    }

    /**
     * @brief The GetHashTableItems() function prints the hash table contents to the console by index.
     */
    void GetHashTableItems() 
    {
        keyList = KeyList();
        valueList = ValueList();

        for (keyIt = keyList.begin(), valueIt = valueList.begin(); keyIt != keyList.end(); ++keyIt, ++valueIt)
            std::cout << "[" << *keyIt << ", " << *valueIt << "] ";
    }

    /**
     * @brief The Insert() function inserts a key-value pair into the hash table. If the key already exists,
     *      the value is updated. If the table threshold has been reached, the hash table is resized.
     * @param key The key of the key-value pair to be inserted
     * @param value The value of the key-value pair to be inserted
     * @return Returns either the updated key-value pair, or the newly inserted pair
     */
    Item<T, U> Insert(T key, U value) 
    {
        if (key == 0 || !key)
            throw "Empty key";
        else if (usedBuckets >= threshold)
            ResizeTable();

        // Hash the current key to be inserted and normalize to get the index
        int offset = NormalizeIndex(keyHash(key));

        for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) 
        {
            // Check if current index was previously deleted, contains a key, or is empty
            if (items[i].m_tombstone == true) 
            {
                if (j == -1)
                    j = i;
            } 
            else if (items[i].m_key != 0) 
            {
                // The key we're trying to insert already exists, so update the value.
                if (items[i].m_key == key) 
                {
                    if (j == -1) 
                    {
                        items[i].m_value = value;
                        std::cout << "Key exists, updating value..." << std::endl;
                        modificationCount++;

                        return items[i];
                    } 
                    else 
                    {
                        items[j] = items[i];
                        items[i].m_key = 0;
                        items[i].m_value = 0;
                        items[i].m_tombstone = true;
                        modificationCount++;

                        return items[j];
                    }
                }
            } 
            else 
            {
                // Current slot is empty so a new key-value pair can be inserted.
                if (j == -1) 
                {
                    usedBuckets++;
                    keyCount++;
                    items[i].m_key = key;
                    items[i].m_value = value;
                    std::cout << "Inserted [" << key << ", " << value << "] at index " << i << std::endl;
                    modificationCount++;

                    return items[i];
                } 
                else 
                {
                    keyCount++;
                    items[j].m_key = key;
                    items[j].m_value = value;
                    std::cout << "Inserted [" << key << ", " << value << "] at index " << j << std::endl;
                    modificationCount++;

                    return items[j];
                }
            }
        }
    }

    /**
     * @brief The HasKey() function returns true if the key is contained within the hash table. The hash
     *      table is optimized along the way if needed.
     * @param key The key to be searched for
     * @return Returns true if the key exists in the hash table
     */
    bool HasKey(T key) 
    {
        if (key == 0 || !key)
            throw "Empty key";

        SetupProbing(key);
        // Hash the current key to be inserted and normalize to get the index
        int offset = NormalizeIndex(keyHash(key));

        // Start at the original hash value and probe until we find our key or an empty item,
        // in which case our item does not exist.
        for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) 
        {
            // Ignore deleted cells, but record the first index in which one is encountered
            // to perform lazy relocation later.
            if (items[i].m_tombstone == true) 
            {
                if (j == -1)
                    j = i;
            } 
            else if (items[i].m_key != 0) 
            {
                // Check if we found the key we're looking for
                if (items[i].m_key == key) 
                {
                    // Perform optimization if we've encountered a previously deleted cell
                    if (j != -1) 
                    {
                        items[j] = items[i];
                        items[i].m_key = 0;
                        items[i].m_value = 0;
                        items[i].m_tombstone = true;
                    } 

                    return true;
                }
            } 
            else 
            {
                return false;
            }
        }
    }

    /**
     * @brief The GetValue() function returns a value for a given key, if such a key exists in the hash
     *      table. The hash table is optimized along the way if needed.
     * @param key The key to be searched for
     * @return Returns the value of the key-value pair or 0 if the key doesn't exist
     */
    U GetValue(T key) 
    {
        if (key == 0 || !key)
            throw "Empty key";

        SetupProbing(key);
        // Hash the current key to be inserted and normalize to get the index
        int offset = NormalizeIndex(keyHash(key));

        // Start at the original hash value and probe until we find our key or an empty item,
        // in which case our item does not exist.
        for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) 
        {
            // Ignore deleted cells, but record the first index in which one is encountered
            // to perform lazy relocation later.
            if (items[i].m_tombstone == true) 
            {
                if (j == -1)
                    j = i;
            } 
            else if (items[i].m_key != 0) 
            {
                // Check if we found the key we're looking for
                if (items[i].m_key == key) 
                {
                    // Perform optimization if we've encountered a previously deleted cell
                    if (j != -1) 
                    {
                        items[j] = items[i];
                        items[i].m_key = 0;
                        items[i].m_value = 0;
                        items[i].m_tombstone = true;

                        return items[j].m_value;
                    } 
                    else 
                    {
                        return items[i].m_value;
                    }
                }
            } 
            else 
            {
                return 0;
            }
        }
    }

    /**
     * @brief The Remove() function removes a key-value pair from the hash table, adds a tombstone in its
     *      place, and returns the value of the pair removed.
     * @param key The key to be searched for
     * @return Returns the value removed from the hash table or 0 if the key doesn't exist
     */
    U Remove(T key) 
    {
        if (key == 0 || !key)
            throw "Empty key";

        SetupProbing(key);
        // Hash the current key to be inserted and normalize to get the index
        int offset = NormalizeIndex(keyHash(key));

        // Start at the original hash value and probe until we find our key or an empty item,
        // in which case our item does not exist.
        for (int i = offset, j = -1, x = 1; ; i = NormalizeIndex(offset + Probe(x++))) 
        {
            // Ignore deleted cells.
            if (items[i].m_tombstone == true) 
                continue;
            else if (items[i].m_key != 0) 
            {
                // Check if we found the key we're looking for
                if (items[i].m_key == key) 
                {
                    keyCount--;
                    modificationCount++;
                    int oldValue = items[i].m_value;

                    items[i].m_key = 0;
                    items[i].m_value = 0;
                    items[i].m_tombstone = true;

                    return oldValue;
                }
            } 
            else
                return 0;
        }
    }

};