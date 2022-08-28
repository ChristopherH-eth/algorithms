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
        * The Linear Constant can be any positive number, and it will be used such that a given
        * hash table will be adjusted by GCD(capacity, LINEAR_CONSTANT) = 1 so each bucket can
        * be probed.
        */
        static int const LINEAR_CONSTANT = 17;

    protected:
        // The following three functions override corresponding functions in the base class to
        // implement the Linear Probing scheme.
        void SetupProbing(int key) override {
            return;
        }

        int Probe(int x) override {
            return LINEAR_CONSTANT * x;
        }

        void AdjustCapacity() override {
            while (GCD(LINEAR_CONSTANT, capacity) != 1) {
                capacity++;
            }

            return;
        }

    public:
        // HashTable constructors for Open Addressing via Linear Probing
        LinearProbing() {
            HashTable();
        }

        LinearProbing(int) {
            HashTable(capacity);
        }

        LinearProbing(int capacity, double loadFactor) {
            HashTable(capacity, loadFactor);
        }

};