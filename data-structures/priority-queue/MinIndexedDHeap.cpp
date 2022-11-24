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
    MinIndexedDHeap<double> ipq(2, 6);

    // Populate IPQ
    std::cout << "Populating indexed priority queue..." << std::endl;

    ipq.Insert(0, 0.0);
    ipq.Insert(2, 4.5);
    ipq.Insert(1, 5.5);
    ipq.Insert(4, 12.3);
    ipq.Insert(5, 6.6);

    std::cout << "IPQ populated! Size: " << ipq.GetSize() << std::endl;

    // Check heap invariant
    if (ipq.IsMinHeap())
        std::cout << "Satisfies heap invariant" << std::endl;
    else
        std::cout << "Doesn't satisfy heap invariant" << std::endl;

    // Test functionality
    std::cout << ipq.PollMinKeyIndex() << std::endl;
    std::cout << ipq.PeekMinValue() << std::endl;

    std::cout << "Size: " << ipq.GetSize() << std::endl;

    if (ipq.IsMinHeap())
        std::cout << "Satisfies heap invariant" << std::endl;
    else
        std::cout << "Doesn't satisfy heap invariant" << std::endl;

    // Decrease key
    std::cout << ipq.ValueOf(4) << std::endl;
    ipq.Decrease(4, 9.9);
    std::cout << ipq.ValueOf(4) << std::endl;

    // Increase key
    std::cout << ipq.ValueOf(5) << std::endl;
    ipq.Increase(5, 7.6);
    std::cout << ipq.ValueOf(5) << std::endl;

    if (ipq.IsMinHeap())
        std::cout << "Satisfies heap invariant" << std::endl;
    else
        std::cout << "Doesn't satisfy heap invariant" << std::endl;

    return 0;
}