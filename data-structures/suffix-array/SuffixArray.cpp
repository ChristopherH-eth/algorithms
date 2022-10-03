#include <iostream>
#include <vector>
#include "SuffixArray.h"

/**
 * @file SuffixArray.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the SuffixArray class
 */

char text[] = "transcendence";          /// String to be sorted into Suffix/LCP Array
std::vector<int> sa;                    /// Vector for Suffix Array storage

int main() {
    SuffixArray suffixArray(text);

    /// @brief Sort data into Suffix Array
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sa = suffixArray.GetLcpArray();
    
    if (sa.size() != 0) {
        std::cout << "Data set sorted! Printing values...\n{ ";

        for (int i = 0; i < sa.size(); i++)
            std::cout << sa[i] << " ";

        std::cout << "}" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Print Suffix Array and LCP Array table
    std::cout << "------------------------------------------------------" << std::endl;
    suffixArray.Display();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}