#pragma once

#include <vector>

/**
 * @file MergeSort.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Merge Sort implementation which sorts a data set by first dividing it into two separate
 *        vectors (data sub-sets). Each element in the two data sub-sets is divided into single 
 *        elements, which are then compared to elements adjacent to themselves, sorted and merged
 *        into one contiguous data set.
 * 
 *        Time Complexity: O(n logn)
 */

class MergeSort {

    private:
        /**
         * @see The Merge() function merges two sorted vectors into a larger sorted vector.
         * @param dataSet1 The first sorted vector
         * @param dataSet2 The second sorted vector
         * @return Returns the merged vector
         */
        static std::vector<int> Merge(std::vector<int> dataSet1, std::vector<int> dataSet2) {
            int n1 = dataSet1.size(), n2 = dataSet2.size();
            int n = n1 + n2, i1 = 0, i2 = 0;
            std::vector<int> dataSet;
            dataSet.resize(n);

            for (int i = 0; i < n; i++) {
                if (i1 == n1) { /// Check if we've iterrated through n1 completely
                    dataSet[i] = dataSet2[i2++];
                } else if (i2 == n2) { /// Check if we've iterrated through n2 completely
                    dataSet[i] = dataSet1[i1++];
                } else { /// Find the element with the least value between the data sub-sets
                    if (dataSet1[i1] < dataSet2[i2]) {
                        dataSet[i] = dataSet1[i1++];
                    } else {
                        dataSet[i] = dataSet2[i2++];
                    }
                }
            }

            return dataSet;
        }

    public:
        /**
         * @see The _MergeSort() function recursively sorts two sub-vectors if the data set > 1.
         * @param dataSet The original data set to be sorted
         * @return Returns the merged result of the two sorted vectors
         */
        static std::vector<int> Sort(std::vector<int> dataSet) {
            int n = dataSet.size();

            /// Check if we have a single element
            if (n <= 1) {
                return dataSet;
            }

            std::vector<int> left;
            std::vector<int> right;

            for (int i = 0; i < n / 2; i++) {
                left.push_back(dataSet[i]);
            }

            for (int i = n / 2; i < n; i++) {
                right.push_back(dataSet[i]);
            }

            /// Split the data set and recursively sort
            left = Sort(left);
            right = Sort(right);

            /// Merge both sorted vectors
            return Merge(left, right);
        }

};