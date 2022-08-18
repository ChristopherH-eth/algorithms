#include <iostream>
#include "IntStack.h"

/**
 * @file IntStack.cpp
 * @author 0xChristopher
 * @brief Basic utilization of a custom stack class; in this case, used with integers.
 */

using namespace std;

int elem {0};

int main() {
    IntStack<int> stack;

    cout << "Checking Vector size: " << stack.vectorSize() << endl;

    // Add elements to the stack.
    while (stack.size() < 5) {
        cout << "Pushing " << elem << " onto the stack..." << endl;
        stack.push(elem);
        elem++;
    }

    // Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.size() << endl;
    cout << "Checking if stack is empty: " << stack.isEmpty() << endl;
    cout << "Checking Vector size: " << stack.vectorSize() << endl;

    // Pop all elements off the stack
    while (!stack.isEmpty()) {
        cout << "Popping an element (" << stack.pop() << ") off the stack..." << endl;
    }

    // Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.size() << endl;
    cout << "Checking if stack is empty: " << stack.isEmpty() << endl;
    cout << "Checking Vector size: " << stack.vectorSize() << endl;

    // Try to pop and element off an empty stack.
    try {
        cout << "Trying to pop an element that doesn't exist..." << stack.pop() << endl;
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    // Check position and capacity.
    cout << "Current Position in Stack: " << stack.getPosition() <<
    "\nCurrent Capacity of Stack: " << stack.getCapacity() << endl;

    // Add more elements to the stack.
    while (stack.size() < 10) {
        cout << "Pushing " << elem << " onto the stack..." << endl;
        stack.push(elem);
        elem++;
    }

    // Clear the stack.
    cout << "Clearing the stack..." << endl;
    stack.clearStack();

    // Return the size of the stack and check if it's empty.
    cout << "The size of the stack is: " << stack.size() << endl;
    cout << "Checking if stack is empty: " << stack.isEmpty() << endl;
    cout << "Checking Vector size: " << stack.vectorSize() << endl;

    return 0;
}