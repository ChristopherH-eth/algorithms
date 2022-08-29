#include <iostream>
#include <vector>
#include "DoublyLinkedList.h"

/**
 * @file DoublyLinkedList.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Doubly Linked List functionality examples.
 */

std::vector<int> firstValues = {2, 6, 9, 11, 3};
std::vector<int> lastValues = {3, 4, 12, 5, 7};
int index = 4;
int elem = 15;
int value = 16;

int main() {
    DoublyLinkedList<int> list;

    /// @see Add elements to list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Populating list..." << std::endl;

    for (int i = 0; i < firstValues.size(); i++) {
        std::cout << "Adding (" << firstValues[i] << ")" << std::endl;
        list.AddFirst(firstValues[i]);
    }

    for (int i = 0; i < lastValues.size(); i++) {
        std::cout << "Adding (" << lastValues[i] << ")" << std::endl;
        list.AddLast(lastValues[i]);
    }
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Display list, head, tail, and size
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Add item by index
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Adding " << elem << " to index " << index << std::endl;
    list.AddAt(index, elem);
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Remove head of list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at the head of the list..." << std::endl;
    list.RemoveFirst();
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Remove tail of list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at the tail of the list..." << std::endl;
    list.RemoveLast();
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Remove item by index
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at index " << index << std::endl;
    list.RemoveAt(index);
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Check contains item by value
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking if list contains " << value << std::endl;
    
    if (list.Contains(value)) {
        std::cout << "True!" << std::endl;
    } else {
        std::cout << "False!" << std::endl;
    }

    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;

    /// @see Remove item by value
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node of value " << value << std::endl;
    list.RemoveByValue(value);
    std::cout << "Head: " << list.PeekFirst() << std::endl;
    std::cout << "Tail: " << list.PeekLast() << std::endl;
    std::cout << "List size: " << list.ListSize() << std::endl;
    list.PrintList();
    std::cout << "------------------------------------------------------" << std::endl;
};