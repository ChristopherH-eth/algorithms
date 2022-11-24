#pragma once

#include <vector>
#include <math.h>

/**
 * @file MinIndexedDHeap.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief This file implements a template of a D-ary Heap data structure, used in creating an Indexed
 *      Priority Queue (IPQ). While similar to a binary heap, the D-ary heap allows for faster 'decrease
 *      priority' operations, by having a wider breadth by 'x' degree versus having a larger depth which a
 *      binary heap would have with the same number of nodes. This makes the D-ary heap useful when used
 *      in particular algorithms such as Dijkstra's Algorithm, where the number of decrease key operations
 *      vastly outnumbers the amount of delete key operations.
 * 
 *      Time Complexity: Decrease Key: O(log_d(n)) where 'd' is the degree and 'n' is the number of nodes
 *                       Get Min: O(d * log_d(n))
 */

template <typename T>

class MinIndexedDHeap
{

    // Check instantiation type (valid: double, float, int)
    static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value || 
        std::is_same<T, int>::value, "Invalid type");

    private:
    int size = 0;                           // Number of elements in the heap
    int n = 0;                              // Maximum number of elements in the heap
    int d = 0;                              // The degree of every node in the heap
    std::vector<int> children;              // Vector to track child indices of each node
    std::vector<int> parents;               // Vector to track parent indices of each node

    /**
     * @brief The IsNotEmptyOrThrow() function raises an exception if an attempt to access an element in the
     *      priority queue is made while it is empty.
     */
    void IsNotEmptyOrThrow()
    {
        if (IsEmpty())
            throw "Priority queue underflow";
    }

    /**
     * @brief The KeyExistsAndValueNotNullOrThrow() function checks that both the key index exists in the 
     *      priority queue, and that the value of the element is not null; otherwise, it raises and
     *      exception.
     * @param ki The key index of the element
     * @param value The value of the element
     */
    void KeyExistsAndValueNotNullOrThrow(int ki, T value)
    {
        KeyExistsOrThrow(ki);
        ValueNotNullOrThrow(value);
    }

    /**
     * @brief The KeyExistsOrThrow() function raises an exception if a key index does not exist in the
     *      priority queue.
     * @param ki The key index to be checked
     */
    void KeyExistsOrThrow(int ki)
    {
        if (!Contains(ki))
            throw "Index does not exist: {0}", ki;
    }

    /**
     * @brief TheValueNotNullOrThrow() function checks that the value of a particular element is not null,
     *      otherwise it raises an exception.
     * @param value The value of the element.
     */
    void ValueNotNullOrThrow(T value)
    {
        if (value == (T) -1)
            throw "Value cannot be null";
    }

    /**
     * @brief The KeyInBoundsOrThrow() function checks if a key index is valid relative to the predetermined
     *      size of the priority queue, and raises an exception if it is not.
     * @param ki The key index to be checked
     */
    void KeyInBoundsOrThrow(int ki)
    {
        if ((ki < 0) || (ki >= n))
            throw "Key index out of bounds: {0}", ki;
    }

    /**
     * @brief The Sink() function 'sinks' nodes in the heap until the heap invariant is satisfied.
     * @param i The index of the node to sink
     */
    void Sink(int i)
    {
        for (int j = MinChild(i); j != -1; )
        {
            Swap(i, j);
            i = j;
            j = MinChild(i);
        }
    }

    /**
     * @brief The Swim() function 'swims' nodes in the heap until the heap invariant is satisfied.
     * @param i The index of the node to swim
     */
    void Swim(int i)
    {
        while (LessIndex(i, parents[i]))
        {
            Swap(i, parents[i]);
            i = parents[i];
        }
    }

    /**
     * @brief The Swap() function swaps nodes between two indices.
     * @param i The index of the first node to swap
     * @param j The index of the second node to swap
     */
    void Swap(int i, int j)
    {
        pm[im[j]] = i;
        pm[im[i]] = j;

        int tmp = im[i];

        im[i] = im[j];
        im[j] = tmp;
    }

    /**
     * @brief The MinChild() function finds the minimum child node given the parent at index 'i'.
     * @param i The index of the parent node
     * @return Returns the index of the minimum child
     */
    int MinChild(int i)
    {
        // Determine if the heap has less nodes than the degree per node
        int index = -1;
        int from = children[i];
        int to = fmin(size, from + d);

        // Iterate over all children of the parent
        for (int j = from; j < to; j++)
            if (LessIndex(j, i))
                index = i = j;

        return index;
    }

    /**
     * @brief The LessIndex() function compares two values at given indices and returns true if the first 
     *      value is less than the second.
     * @param i The index of the first value to compare
     * @param j The index of the second value to compare
     * @return
     */
    bool LessIndex(int i, int j)
    {
        return (values[im[i]] - values[im[j]]) < 0 ? true : false;
    }

    /**
     * @brief The Less() function compares two values and returns true if the first value is less than the
     *      second.
     * @param value1 The first value to compare
     * @param value2 The second value to compare
     * @return
    */
    bool Less(T value1, T value2)
    {
        return (value1 - value2) < 0 ? true : false;
    }

    /**
     * @brief The IsMinHeap() function recursively checks the heap to ensure it satisfies the heap
     *      invariant.
     * @param i The index of the node at the top of the heap
     * @return Returns true if the heap invariant is satisfied 
     */
    bool IsMinHeap(int i)
    {
        int from = children[i];
        int to = fmin(size, from + d);

        // Recursively check all child nodes
        for (int j = from; j < to; j++)
        {
            if (!LessIndex(i, j))
                return false;

            if (!IsMinHeap(j))
                return false;
        }

        // Heap invariant is satisfied
        return true;
    }

    public:
    // The position map (pm) maps key indices (ki) to where that key's position is represented in the 
    // priority queue, in the domain [0, size)
    std::vector<int> pm;

    // The inverse map (im) stores the indices of the keys in the range [0, size) which make up the pq
    // NOTE: 'im' and 'pm' are inverses of each other, such that pm[im[i]] = im[pm[i]] = i
    std::vector<int> im;

    // The values associated with the keys; indexed by key indices (ki)
    std::vector<T> values; 

    /**
     * @brief The constructor and destructor for MinIndexedDHeap
     * @param degree The degree of every node in the heap
     * @param maxSize The maximum number of element in the heap
     */
    MinIndexedDHeap(int degree, int maxSize)
    {
        if (maxSize <= 0)
            throw "Max size less than or equal to zero";

        this->d = fmax(2, degree);
        this->n = fmax(d + 1, maxSize);

        // Resize vectors for efficiency
        this->pm.resize(maxSize);
        this->im.resize(maxSize);
        this->values.resize(maxSize);
        this->parents.resize(maxSize);
        this->children.resize(maxSize);

        // Initialize vectors
        for (int i = 0; i < n; i++)
        {
            this->pm[i] = -1;
            this->im[i] = -1;
            this->values[i] = (T) -1;
            this->parents[i] = (i - 1) / d;
            this->children[i] = i * d + 1;
        }
    }

    ~MinIndexedDHeap()
    {

    }

    /**
     * @brief The GetSize() function retrieves the size of the indexed priority queue (ipq).
     * @return Returns 'size'
     */
    int GetSize()
    {
        return size;
    }

    /**
     * @brief The IsEmpty() function checks if the heap is empty.
     * @return Returns true if the heap is empty
     */
    bool IsEmpty()
    {
        return size == 0;
    }

    /**
     * @brief The Contains() function checks if the heap contains a specific key index.
     * @param ki The key index to be checked
     * @return Returns true if the key index exists in the priority queue
     */
    bool Contains(int ki)
    {
        KeyInBoundsOrThrow(ki);

        return pm[ki] != -1;
    }

    /**
     * @brief The PeekMinKeyIndex() retrieves the index of the top element in the priority queue.
     * @return Returns the index of the top element
     */
    int PeekMinKeyIndex()
    {
        IsNotEmptyOrThrow();

        return im[0];
    }

    /**
     * @brief The PollMinKeyIndex() function removes the element with the minimum key index from the 
     *      priority queue and returns it.
     * @return Returns the minimum key index
     */
    int PollMinKeyIndex()
    {
        int minKi = PeekMinKeyIndex();
        Delete(minKi);

        return minKi;
    }

    /**
     * @brief The PeekMinValue() function retrieves and returns the value of the element at the top of the
     *      priority queue and returns it.
     * @return Returns the value at the top of the priority queue
     */
    T PeekMinValue()
    {
        IsNotEmptyOrThrow();

        return (T) values[im[0]];
    }

    /**
     * @brief The PollMinValue() function retrieves the value of the element at the top of the priority
     *      queue and removes said element.
     * @return Returns the value of the element at the top of the priority queue
    */
    T PollMinValue()
    {
        T minValue = PeekMinValue();
        Delete(PeekMinKeyIndex());

        return minValue;
    }

    /**
     * @brief The ValueOf() function returns the value of an element via its key index.
     * @param ki The key index of the element
     * @return Returns the value of the element
     */
    T ValueOf(int ki)
    {
        KeyExistsOrThrow(ki);

        return (T) values[ki];
    }

    /**
     * @brief The Insert() function inserts an element into the priority queue.
     * @param ki The key index of the element
     * @param value The value of the element
     */
    void Insert(int ki, T value)
    {
        if (Contains(ki))
            throw "Index already exists: {0}", ki;

        ValueNotNullOrThrow(value);
        pm[ki] = size;
        im[size] = ki;
        values[ki] = value;

        // Update priority queue
        Swim(size++);
    }

    /**
     * @brief The Delete() function removes an element from the priority queue by its key index and updates
     *      the priority queue.
     * @param ki The key index of the element
     * @return Returns the value of the removed element
     */
    T Delete(int ki)
    {
        KeyExistsOrThrow(ki);
        int i = pm[ki];

        // Update the priority queue
        Swap(i, --size);
        Sink(i);
        Swim(i);

        // Store the value to be removed
        T value = (T) values[ki];

        // Reduce vector size
        values[ki] = -1;
        pm[ki] = -1;
        im[size] = -1;

        return value;
    }

    /**
     * @brief The Update() function updates a value at a specific key index in the priority queue.
     * @param ki The key index at which the value will be updated
     * @param value The updated value
     * @return Returns the old value
     */
    T Update(int ki, T value)
    {
        KeyExistsAndValueNotNullOrThrow(ki, value);
        int i = pm[ki];

        // Store the old value and update it
        T oldValue = (T) values[ki];
        values[ki] = value;

        // Update the priority queue
        Sink(i);
        Swim(i);

        return oldValue;
    }

    /**
     * @brief The Decrease() function strictly decreases the value associated with a given key index.
     * @param ki The key index at which the value is decreased
     * @param value The new value
     */
    void Decrease(int ki, T value)
    {
        KeyExistsAndValueNotNullOrThrow(ki, value);

        // Check if the new value is less than the current value
        if (Less(value, values[ki]))
        {
            values[ki] = value;
            Swim(pm[ki]);
        }
    }

    /**
     * @brief The Increase() function strictly increases the value associated with a given key index.
     * @param ki The key index at which the value is increased
     * @param value The new value
     */
    void Increase(int ki, T value)
    {
        KeyExistsAndValueNotNullOrThrow(ki, value);

        // Check if the new value is greater than the current value
        if (Less(values[ki], value))
        {
            values[ki] = value;
            Sink(pm[ki]);
        }
    }

    /**
     * @brief The IsMinHeap() function is the public facing function to check if the heap's current state
     *      satisfies the heap invariant.
     * @return Returns true if the heap invariant is satisfied
     */
    bool IsMinHeap()
    {
        return IsMinHeap(0);
    }

};