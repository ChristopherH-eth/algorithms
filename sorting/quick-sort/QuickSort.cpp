#include <iostream>
#include "QuickSort.h"

/**
 * @file QuickSort.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the QuickSort class
 */

std::vector<int> dataSet = {16, 2, -5, 1, -13, 3, 9, 22, 8, 15, 12};        /// Original data set
std::vector<int> sortedData;                                                /// Sorted data set

int main() {
    QuickSort quickSort;

    /// @brief Sort data set via quick sort
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sortedData = quickSort.Sort(dataSet);
    
    if (sortedData.size() != 0) {
        std::cout << "Data set sorted! Printing values...\n{ ";

        for (int i = 0; i < sortedData.size(); i++)
            std::cout << sortedData[i] << " ";

        std::cout << "}" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}