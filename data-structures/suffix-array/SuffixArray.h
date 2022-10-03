#pragma once

#include <vector>
#include <string.h>
#include <algorithm>
#include "Suffix.h"

/**
 * @file SuffixArray.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Suffix Array (SA) implementation which also builds a Longest Common Prefix Array (LCP)
 *        using the Kasai Algorithm. This implementation takes in a char[] as text to build the
 *        SA and LCP, and displays the result in an easy to digest table. The SA utilizes a
 *        naive method to build, and is achieved simply by comparing two suffixes of those 
 *        populated in an unsorted vector, and sorting based on those comparisons.
 * 
 *        Time Complexity:
 *              Sorting                 O(n*k*logn)     where k is the max string length
 *              Kasai's Algorithm       O(n)            to create LCP array
 */

class SuffixArray {

    private:
        bool constructedSa = false;             /// Set to true if we have a Suffix Array
        bool constructedLcpArray = false;       /// Set to true if we have an LCP Array

        /// @brief The Kasai() function uses the Kasai algorithm to build the LCP Array.
        void Kasai() {
            std::vector<int> inv;

            if (lcp.size() != 0) {
                for (int i = 0; i < size; i++) {
                    lcp.pop_back();
                }
            }

            if (inv.size() != 0) {
                for (int i = 0; i < size; i++) {
                    inv.pop_back();
                }
            }

            lcp.resize(size);
            inv.resize(size);

            for (int i = 0; i < size; i++) {
                inv[sa[i]] = i;
            }

            for (int i = 0, len = 0; i < size; i++) {
                if (inv[i] > 0) {
                    int k = sa[inv[i] - 1];

                    while ((i + len < size) && (k + len < size) && t[i + len] == t[k + len]) {
                        len++;
                    }

                    lcp[inv[i]] = len;

                    if (len > 0) {
                        len--;
                    }
                }
            }
        }

    protected:
        int size;                           /// Length of the suffix array
        std::vector<int> sa;                /// Sorted suffix array values
        std::vector<int> lcp;               /// Longest common prefix array
        std::vector<Suffix> suffixes;       /// All possible suffixes for given text

        /**
         * @brief The BuildSuffixArray() function calls the Construct() function.
         */
        void BuildSuffixArray() {
            if (constructedSa)
                return;

            Construct(t, size);
            constructedSa = true;
        }

        /**
         * @brief The BuildLcpArray() function builds the LCP Array by building the Suffix
         * Array and then running the Kasai algorithm.
         */
        void BuildLcpArray() {
            if (constructedLcpArray)
                return;

            BuildSuffixArray();
            Kasai();
            constructedLcpArray = true;
        }

        /**
         * @brief The Construct() function builds the Suffix Array.
         * @param t The text the Suffix Array will be built with
         * @param n The length of the text input
         * @return Returns the Suffix Array
         */
        std::vector<int> Construct(char *t, int n) {
            suffixes.resize(n);

            for (int i = 0; i < n; i++) {
                suffixes[i].index = i;
                suffixes[i].suffix = (t + i);
            }

            std::sort(suffixes.begin(), suffixes.end(), Compare);

            for (int i = 0; i < n; i++)
                sa.emplace_back(suffixes[i].index);

            return sa;
        }

        /**
         * @brief The Compare() function compares two suffixes. If the first character that does
         * not match between them has a lower value in suffix a than suffix b, it returns 1, 
         * otherwise it returns 0.
         * @return Returns the result of suffix comparisons
         */
        static int Compare(Suffix& a, Suffix& b) {
            return strcmp(a.suffix, b.suffix) < 0 ? 1 : 0;
        }

        char t[];               /// Suffix Array input text

    public:
        /**
         * @brief SuffixArray constructor and destructor
         * @param text The input to build the SA and LCP with
         */
        SuffixArray(char *text) {
            if (strlen(text) == 0)
                throw "Text cannot be null";

            strcpy(this->t, text);
            this->size = strlen(text);
        }

        ~SuffixArray() {}

        /**
         * @brief The GetTextLength() function gets the length of the text input.
         * @return Returns the size of the text vector
         */
        int GetTextLength() {
            return size;
        }

        /**
         * @brief The GetSa() function calls the BuildSuffixArray() function.
         * @return Returns the sorted suffix array values
         */
        std::vector<int> GetSa() {
            BuildSuffixArray();

            return sa;
        }

        /**
         * @brief The GetLcpArray() function calls the BuildLcpArray() function.
         * @return Returns the LCP Array
         */
        std::vector<int> GetLcpArray() {
            BuildLcpArray();

            return lcp;
        }

        /**
         * @brief The Display() function displays the Suffix and LCP Arrays in an easy to read
         * format.
         */
        void Display() {
            printf("-----i-----SA-----LCP---Suffix\n");

            for (int i = 0; i < size; i++)
                printf("% 6d % 6d % 6d % 3s % s\n", i, sa[i], lcp[i], "", suffixes[i].suffix);
        }
    
};