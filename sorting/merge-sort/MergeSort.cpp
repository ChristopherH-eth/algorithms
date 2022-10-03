#include <iostream>
#include <vector>
#include "MergeSort.h"

/**
 * @file MergeSort.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the MergeSort class
 */

std::vector<int> dataSet = {44, 3, 22, 36, 11, 77, 98, -2, 9};          /// Original data set
std::vector<int> sortedData;                                            /// Sorted data set

int main() {
    MergeSort mergeSort;

    /// @brief Sort data set via merge sort
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sortedData = mergeSort.Sort(dataSet);
    
    if (sortedData.size() != 0) {
        std::cout << "Data set sorted! Printing values...\n{ ";

        for (int i = 0; i < sortedData.size(); i++)
            std::cout << sortedData[i] << " ";

        std::cout << "}" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();

}