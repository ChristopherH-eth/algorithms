#include <iostream>
#include <vector>
#include "MergeSort.h"

/**
 * @file MergeSort.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the MergeSort class
 */

std::vector<int> dataSet = {44, 3, 22, 36, 11, 77, 98, -2, 9};
std::vector<int> sortedData;

int main() {
    MergeSort _mergeSort;

    /// @see Sort data set via merge sort
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sortedData = _mergeSort.Sort(dataSet);
    
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