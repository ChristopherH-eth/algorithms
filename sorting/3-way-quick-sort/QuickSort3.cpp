#include <iostream>
#include "QuickSort3.h"

/**
 * @file QuickSort3.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the QuickSort3 class
 */

std::vector<int> dataSet = {16, 2, 12, 12, 3, -5, 1, -13, 3, 9, 22, 8, 16, 15, 12};
std::vector<int> sortedData;

int main() {
    QuickSort3 quickSort3;

    /// @see Sort data set via quick sort
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sortedData = quickSort3.Sort(dataSet);
    
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