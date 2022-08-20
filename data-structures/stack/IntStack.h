#pragma once

#include <iostream>
#include <vector>
#include "Stack.h"

/**
 * @file IntStack.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The IntStack class inherits the Stack class and elaborates on the design to create a workable stack
 * for integers.
 */

using namespace std;

template <typename T>

class IntStack : public Stack<T> {

    private:
        vector<int> stackVector;
        int position {0}; // Tracks the top of the stack
        int capacity {0}; // Capacity of the stack
        int elem {0}; // Element at given position

    public:
        // IntStack Constructor
        IntStack() {}

        // The size() function returns the size of the stack.
        int size() override {
            return position;
        }

        // The isEmpty() function returns true if the stack is empty.
        bool isEmpty() override {
            return position == 0;
        }

        // The peek() function returns the element at the top of the stack.
        T peek() override {
            if (position == 0) {
                throw "The stack is empty!";
            }

            return stackVector.back();
        }

        // The push() functions adds an element (value) to the top of the stack if maxSize hasn't been reached.
        void push(T value) override {
            if (position == capacity) {
                increaseCapacity();
            }

            stackVector.at(position) = value;
            position++;
        }

        // The pop() function removes the element from the top of the stack.
        T pop() override {
            if (position == 0) {
                throw "The stack is empty!";
            } else if (stackVector.size() > position) {
                stackVector.resize(position);
            }

            capacity = stackVector.size();
            elem = stackVector.back();
            stackVector.pop_back();
            position--;
            capacity--;

            return (elem);
        }

        // The increaseCapacity() function increases the capacity of the stack if max capacity
        // is reached.
        void increaseCapacity() override {
            cout << "Maximum capacity reached; increasing stack capacity..." << endl;

            if (position == 0) {
                capacity += 1;
                stackVector.resize(capacity);
            } else {
                capacity *= 2;
                stackVector.resize(capacity);
            }
        }

        // The clearStack() function clears all elements in the stack.
        void clearStack() override {
            stackVector.clear();
            position = 0;
            capacity = 0;
        }

        /* Test Functions */

        int vectorSize() {
            return stackVector.size();
        }

        int getPosition() {
            return position;
        }

        int getCapacity() {
            return capacity;
        }
    
};
