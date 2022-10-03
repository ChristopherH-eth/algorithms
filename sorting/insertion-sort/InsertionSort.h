#pragma once

#include <vector>

/**
 * @file InsertionSort.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Insertion Sort implementation which sorts a given data set by comparing i to i - 1 values
 *        and swapping them if i - 1 is greater. While this method can be useful for smaller data sets,
 *        when sorting larger groups of data, it may be best to use something such as merge sort.
 * 
 *        Time Complexity:
 *              Operation       Best Case       Worst Case
 *              Comparisons     O(n)            O(n^2)
 *              Swaps           O(1)            O(n^2)
 */

class InsertionSort {

    private:
        /**
         * @brief The _InsertionSort() function sorts a data set using the insertion sort algorithm.
         * @param dataSet The vector of data to be sorted
         * @return Returns if dataSet is empty
         */
        static void ISort(std::vector<int>& dataSet) {
            if (dataSet.size() == 0)
                return;

            for (int i = 1; i < dataSet.size(); i++) {
                for (int j = i; j > 0 && dataSet[j] < dataSet[j - 1]; j--) {
                    /// Swapping will occur until dataSet[i] >= dataSet [i - 1]
                    Swap(dataSet, j - 1, j);
                }
            }
        }

        /**
         * @brief The Swap() function swaps two data set members such that the smaller value (j)
         * comes before the larger value (i) in the set.
         * @param dataSet The vector of data to be sorted
         * @param i The larger value in the pair to be swapped
         * @param j The smaller value in the pair to be swapped
         */
        static void Swap(std::vector<int>& dataSet, int i, int j) {
            int tmp = dataSet[i];
            dataSet[i] = dataSet[j];
            dataSet[j] = tmp;
        }

    public:
        /**
         * @brief The Sort() function is the public facing function to invoke _InsertionSort().
         * @param dataSet The vector of data to be sorted
         * @return Returns the now sorted vector
         */
        std::vector<int> Sort(std::vector<int>& dataSet) {
            ISort(dataSet);

            return dataSet;
        }

};