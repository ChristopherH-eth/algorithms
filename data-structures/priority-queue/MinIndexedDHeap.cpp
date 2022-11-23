#include <iostream>

#include "MinIndexedDHeap.h"

/**
 * @file MinIndexedDHeap.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Source file for min indexed priority queue using a D-ary heap.
 */

int main()
{
    MinIndexedDHeap<int> ipq(2, 6);

    std::cout << "Populating indexed priority queue..." << std::endl;

    ipq.Insert(0, 0.0);
    ipq.Insert(2, 4.5);
    ipq.Insert(1, 5.5);
    ipq.Insert(4, 12.3);
    ipq.Insert(5, 6.6);

    std::cout << "IPQ populated!" << std::endl;

    return 0;
}