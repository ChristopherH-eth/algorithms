#pragma once

/**
 * @file Stack.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Stack class is used as a template for different stack types (see IntStack.h).
 */

template <typename T>

class Stack {

    public:
        // Stack Constructor
        Stack() {}

        // The size of the stack
        virtual int size() {
            return 0;
        }

        // Checks of the stack is empty
        virtual bool isEmpty() {
            return 0;
        }

        // Returns the element at the top of the stack
        virtual T peek() {
            return 0;
        }

        // Push elements onto the stack
        virtual void push(T elem) {}

        // Pop elements off of the stack
        virtual T pop() {
            return 0;
        }

        // Increase stack capacity
        virtual void increaseCapacity() {}

        // Clear remaining elements from the stack
        virtual void clearStack() {}

};
