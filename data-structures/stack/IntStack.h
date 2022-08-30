#pragma once

#include <iostream>
#include <vector>
#include "Stack.h"

/**
 * @file IntStack.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The IntStack class inherits the Stack class and elaborates on the design to create a workable stack
 *        for integers. It allows the user to add and remove elements, check the value at the top of the 
 *        stack, clear the stack and increase capacity.
 */

template <typename T>

class IntStack : public Stack<T> {

    private:
        std::vector<int> stackVector;
        int position {0}; /// Tracks the top of the stack
        int capacity {0}; /// Capacity of the stack
        int elem {0}; /// Element at given position

    public:
        /// @see IntStack Constructor
        IntStack() {}

        /// @see The size() function returns the size of the stack.
        /// @return Returns the number of elements on the stack
        int Size() override {
            return position;
        }

        /// @see The isEmpty() function returns true if the stack is empty.
        /// @return Returns true if the stack is empty
        bool IsEmpty() override {
            return position == 0;
        }

        /// @see The peek() function returns the element at the top of the stack.
        /// @return Returns the element at the top of the stack
        T Peek() override {
            if (position == 0) {
                throw "The stack is empty!";
            }

            return stackVector.back();
        }

        /// @see The push() functions adds an element (value) to the top of the stack if maxSize hasn't been reached.
        /// @param value The element to be pushed onto the stack
        void Push(T value) override {
            if (position == capacity) {
                IncreaseCapacity();
            }

            stackVector.at(position) = value;
            position++;
        }

        /// @see The pop() function removes the element from the top of the stack.
        /// @return Returns the element popped off the stack
        T Pop() override {
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

            return elem;
        }

        /// @see The increaseCapacity() function increases the capacity of the stack if max capacity
        /// is reached.
        void IncreaseCapacity() override {
            std::cout << "Maximum capacity reached; increasing stack capacity..." << std::endl;

            if (position == 0) {
                capacity += 1;
                stackVector.resize(capacity);
            } else {
                capacity *= 2;
                stackVector.resize(capacity);
            }
        }

        /// @see The clearStack() function clears all elements in the stack.
        void ClearStack() override {
            stackVector.clear();
            position = 0;
            capacity = 0;
        }

        /* Test Functions */

        int VectorSize() {
            return stackVector.size();
        }

        int GetPosition() {
            return position;
        }

        int GetCapacity() {
            return capacity;
        }
    
};
