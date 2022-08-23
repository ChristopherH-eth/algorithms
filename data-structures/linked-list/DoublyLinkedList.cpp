#include <iostream>
#include <vector>
#include "DoublyLinkedList.h"

/**
 * @file DoublyLinkedList.cpp
 * @author 0xChristopher
 * @brief Doubly Linked List functionality examples.
 */

std::vector<int> firstValues = {2, 6, 9, 11, 3};
std::vector<int> lastValues = {3, 4, 12, 5, 7};
int index = 4;
int elem = 15;
int value = 16;

int main() {
    DoublyLinkedList<int> list;

    // Add elements to list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Populating list..." << std::endl;

    for (int i = 0; i < firstValues.size(); i++) {
        std::cout << "Adding (" << firstValues[i] << ")" << std::endl;
        list.addFirst(firstValues[i]);
    }

    for (int i = 0; i < lastValues.size(); i++) {
        std::cout << "Adding (" << lastValues[i] << ")" << std::endl;
        list.addLast(lastValues[i]);
    }
    std::cout << "------------------------------------------------------" << std::endl;

    // Display list, head, tail, and size
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Add item by index
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Adding " << elem << " to index " << index << std::endl;
    list.addAt(index, elem);
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove head of list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at the head of the list..." << std::endl;
    list.removeFirst();
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove tail of list
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at the tail of the list..." << std::endl;
    list.removeLast();
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove item by index
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node at index " << index << std::endl;
    list.removeAt(index);
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Check contains item by value
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Checking if list contains " << value << std::endl;
    
    if (list.contains(value)) {
        std::cout << "True!" << std::endl;
    } else {
        std::cout << "False!" << std::endl;
    }

    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;

    // Remove item by value
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Removing node of value " << value << std::endl;
    list.removeByValue(value);
    std::cout << "Head: " << list.peekFirst() << std::endl;
    std::cout << "Tail: " << list.peekLast() << std::endl;
    std::cout << "List size: " << list.listSize() << std::endl;
    list.printList();
    std::cout << "------------------------------------------------------" << std::endl;
};