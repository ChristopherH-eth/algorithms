#include <iostream>
#include "InsertionSort.h"

/**
 * @file InsertionSort.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the InsertionSort class
 */

std::vector<int> dataSet = {16, 2, 5, 1, 13, 3, 9};
std::vector<int> sortedData;

int main() {
    InsertionSort insertionSort;

    /// @see Sort data set via insertion sort
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sortedData = insertionSort.Sort(dataSet);
    
    if (sortedData.size() != 0) {
        std::cout << "Data set sorted! Printing values...\n{ ";

        for (int i = 0; i < sortedData.size(); i++) {
            std::cout << sortedData[i] << " ";
        }

        std::cout << "}" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}