#pragma once

/**
 * @file Stack.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief The Stack class is used as an interface for different stack types (see IntStack.h).
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
        /// @brief Stack constructor and destructor
        Stack() {}

        virtual ~Stack() {}

        /// @brief The size of the stack
        virtual int Size() = 0;

        /// @brief Checks of the stack is empty
        virtual bool IsEmpty() = 0;

        /// @brief Returns the element at the top of the stack
        virtual T Peek() = 0;

        /// @brief Push elements onto the stack
        /// @param elem The value to be pushed onto the stack
        virtual void Push(T elem) = 0;

        /// @see Pop elements off of the stack
        virtual T Pop() = 0;

        /// @brief Increase stack capacity
        virtual void IncreaseCapacity() = 0;

        /// @brief Clear remaining elements from the stack
        virtual void ClearStack() = 0;

};
