#pragma once

#include "HashTableOpenAddressing.h"

/**
 * @file LinearProbing.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The LinearProbing class provides override functions to a HashTable in order for it to adopt a linear
 *        probing scheme.
 */

class LinearProbing : public HashTable {
    
    protected:
        static int const LINEAR_CONSTANT = 17;

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

};