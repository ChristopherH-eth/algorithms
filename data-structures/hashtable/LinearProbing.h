#pragma once

#include "HashTableOpenAddressing.h"

/**
 * @file LinearProbing.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The LinearProbing class is derived from the HashTable class, and provides override 
 *        functions to a HashTable in order for it to adopt a linear probing scheme (source file
 *        is HashTableOpenAddressing.h).
 */

class LinearProbing : public HashTable {
    
    private:
        /** 
        * @see The Linear Constant can be any positive number, and it will be used such that a given
        * hash table will be adjusted by GCD(capacity, LINEAR_CONSTANT) = 1 so each bucket can
        * be probed.
        */
        static int const LINEAR_CONSTANT = 17;

    protected:
        /**
         * @see The following three functions override corresponding functions in the base class to
         * implement the Linear Probing scheme.
         * @param key The key to probe for
         */
        void SetupProbing(int key) override {
            return;
        }

        /**
         * @see The Probe() function determines the next bucket to probe for the key
         * @param x The given probing iteration
         * @return Returns the quotient of the LINEAR_CONSTANT and the current iteration x
         */
        int Probe(int x) override {
            return LINEAR_CONSTANT * x;
        }

        /// @see The AdjustCapacity() function adjusts the capacity of the hash table such that
        /// the GCD (greatest common denominator) of the LINEAR_CONSTANT and the capacity is 1.
        void AdjustCapacity() override {
            while (GCD(LINEAR_CONSTANT, capacity) != 1) {
                capacity++;
            }

            return;
        }

    public:
        /// @see HashTable constructors for Open Addressing via Linear Probing
        LinearProbing() {
            HashTable();
        }

        /// @param capacity The capacity of the hash table
        LinearProbing(int) {
            HashTable(capacity);
        }

        /// @param capacity The capacity of the hash table
        /// @param loadFactor The acceptable hash table load before table resizing
        LinearProbing(int capacity, double loadFactor) {
            HashTable(capacity, loadFactor);
        }

};