#include <iostream>
#include "IntStack.h"

/**
 * @file IntStack.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Basic utilization of a custom stack class; in this case, used with integers.
 */

int elem {0};

int main() {
    IntStack<int> stack;

    std::cout << "Checking Vector size: " << stack.VectorSize() << std::endl;

    /// @brief Add elements to the stack.
    while (stack.Size() < 5) {
        std::cout << "Pushing " << elem << " onto the stack..." << std::endl;
        stack.Push(elem);
        elem++;
    }

    /// @brief Return the size of the stack and check if it's empty.
    std::cout << "The size of the stack is: " << stack.Size() << std::endl;
    std::cout << "Checking if stack is empty: " << stack.IsEmpty() << std::endl;
    std::cout << "Checking Vector size: " << stack.VectorSize() << std::endl;

    /// @brief Pop all elements off the stack
    while (!stack.IsEmpty()) {
        std::cout << "Popping an element (" << stack.Pop() << ") off the stack..." << std::endl;
    }

    /// @brief Return the size of the stack and check if it's empty.
    std::cout << "The size of the stack is: " << stack.Size() << std::endl;
    std::cout << "Checking if stack is empty: " << stack.IsEmpty() << std::endl;
    std::cout << "Checking Vector size: " << stack.VectorSize() << std::endl;

    /// @brief Try to pop and element off an empty stack.
    try {
        std::cout << "Trying to pop an element that doesn't exist..." << stack.Pop() << std::endl;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    /// @brief Check position and capacity.
    std::cout << "Current Position in Stack: " << stack.GetPosition() <<
    "\nCurrent Capacity of Stack: " << stack.GetCapacity() << std::endl;

    /// @brief Add more elements to the stack.
    while (stack.Size() < 10) {
        std::cout << "Pushing " << elem << " onto the stack..." << std::endl;
        stack.Push(elem);
        elem++;
    }

    /// @brief Clear the stack.
    std::cout << "Clearing the stack..." << std::endl;
    stack.ClearStack();

    /// @brief Return the size of the stack and check if it's empty.
    std::cout << "The size of the stack is: " << stack.Size() << std::endl;
    std::cout << "Checking if stack is empty: " << stack.IsEmpty() << std::endl;
    std::cout << "Checking Vector size: " << stack.VectorSize() << std::endl;

}