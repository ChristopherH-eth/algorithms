#pragma once

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

#include "Suffix.h"

/**
 * @file SuffixArray.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Suffix Array (SA) implementation which also builds a Longest Common Prefix Array (LCP)
 *      using the Kasai Algorithm. This implementation takes in a char[] as text to build the
 *      SA and LCP, and displays the result in an easy to digest table. The SA utilizes a
 *      naive method to build, and is achieved simply by comparing two suffixes of those 
 *      populated in an unsorted vector, and sorting based on those comparisons.
 * 
 *      Time Complexity:
 *              Sorting                 O(n*k*logn)     where k is the max string length
 *              Kasai's Algorithm       O(n)            to create LCP array
 */

class SuffixArray 
{

    private:
        bool constructedSa = false;             // Set to true if we have a Suffix Array
        bool constructedLcpArray = false;       // Set to true if we have an LCP Array

        /**
         * @brief The Kasai() function uses the Kasai algorithm to build the LCP Array.
         */
        void Kasai();

    protected:
        int size;                               // Length of the suffix array
        std::string t;                          // Suffix Array input text
        std::vector<int> sa;                    // Sorted suffix array values
        std::vector<int> lcp;                   // Longest common prefix array
        std::vector<Suffix> suffixes;           // All possible suffixes for given text

        /**
         * @brief The BuildSuffixArray() function calls the Construct() function.
         */
        void BuildSuffixArray();

        /**
         * @brief The BuildLcpArray() function builds the LCP Array by building the Suffix
         *      Array and then running the Kasai algorithm.
         */
        void BuildLcpArray();

        /**
         * @brief The Construct() function builds the Suffix Array.
         * @param t The text the Suffix Array will be built with
         * @param n The length of the text input
         * @return Returns the Suffix Array
         */
        std::vector<int> Construct(std::string& t, int n);

        /**
         * @brief The Compare() function compares two suffixes. If the first character that does
         *      not match between them has a lower value in suffix a than suffix b, it returns 1, 
         *      otherwise it returns 0.
         * @return Returns the result of suffix comparisons
         */
        static int Compare(Suffix& a, Suffix& b);

    public:
        /**
         * @brief SuffixArray constructor with char array as input
         * @param text The input to build the SA and LCP with
         */
        SuffixArray(const char* text);

        /**
         * @brief SuffixArray constructor with string as input
         * @param sText The input to build the SA and LCP with
         */
        SuffixArray(std::string& sText);

        ~SuffixArray();

        /**
         * @brief The GetTextLength() function gets the length of the text input.
         * @return Returns the size of the text vector
         */
        int GetTextLength();

        /**
         * @brief The GetSa() function calls the BuildSuffixArray() function.
         * @return Returns the sorted suffix array values
         */
        std::vector<int> GetSa();

        /**
         * @brief The GetLcpArray() function calls the BuildLcpArray() function.
         * @return Returns the LCP Array
         */
        std::vector<int> GetLcpArray();

        /**
         * @brief The DisplayTable() function displays the Suffix and LCP Arrays in an easy to read
         *      format.
         */
        void DisplayTable();

        /**
         * @brief The DisplaySA() function displays the Suffix Array in an easy to read format.
         */
        void DisplaySA();
    
};