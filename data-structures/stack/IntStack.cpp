#include <iostream>
#include "IntStack.h"

/**
 * @file IntStack.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Basic utilization of a custom stack class; in this case, used with integers.
 */

using namespace std;

int elem {0};

int main() {
    IntStack<int> stack;

    cout << "Checking Vector size: " << stack.VectorSize() << endl;

    /// @see Add elements to the stack.
    while (stack.Size() < 5) {
        cout << "Pushing " << elem << " onto the stack..." << endl;
        stack.Push(elem);
        elem++;
    }

    /// @see Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.Size() << endl;
    cout << "Checking if stack is empty: " << stack.IsEmpty() << endl;
    cout << "Checking Vector size: " << stack.VectorSize() << endl;

    /// @see Pop all elements off the stack
    while (!stack.IsEmpty()) {
        cout << "Popping an element (" << stack.Pop() << ") off the stack..." << endl;
    }

    /// @see Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.Size() << endl;
    cout << "Checking if stack is empty: " << stack.IsEmpty() << endl;
    cout << "Checking Vector size: " << stack.VectorSize() << endl;

    /// @see Try to pop and element off an empty stack.
    try {
        cout << "Trying to pop an element that doesn't exist..." << stack.Pop() << endl;
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    /// @see Check position and capacity.
    cout << "Current Position in Stack: " << stack.GetPosition() <<
    "\nCurrent Capacity of Stack: " << stack.GetCapacity() << endl;

    /// @see Add more elements to the stack.
    while (stack.Size() < 10) {
        cout << "Pushing " << elem << " onto the stack..." << endl;
        stack.Push(elem);
        elem++;
    }

    /// @see Clear the stack.
    cout << "Clearing the stack..." << endl;
    stack.ClearStack();

    /// @see Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.Size() << endl;
    cout << "Checking if stack is empty: " << stack.IsEmpty() << endl;
    cout << "Checking Vector size: " << stack.VectorSize() << endl;

}