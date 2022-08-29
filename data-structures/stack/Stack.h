#pragma once

/**
 * @file Stack.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Stack class is used as a template for different stack types (see IntStack.h).
 * 
 *        Time Complexity:
 *              Operation       Average     Worst
 *              Push            O(1)        O(n)
 *              Pop             O(1)        O(1)
 *              Peek            O(1)        O(1)
 */

template <typename T>

class Stack {

    public:
        /// @see The size of the stack
        virtual int Size() {
            return 0;
        }

        /// @see Checks of the stack is empty
        virtual bool IsEmpty() {
            return 0;
        }

        /// @see Returns the element at the top of the stack
        virtual T Peek() {
            return 0;
        }

        /// @see Push elements onto the stack
        /// @param elem The value to be pushed onto the stack
        virtual void Push(T elem) {}

        /// @see Pop elements off of the stack
        virtual T Pop() {
            return 0;
        }

        /// @see Increase stack capacity
        virtual void IncreaseCapacity() {}

        /// @see Clear remaining elements from the stack
        virtual void ClearStack() {}

};
