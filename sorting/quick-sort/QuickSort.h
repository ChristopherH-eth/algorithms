#pragma once

#include <vector>

/**
 * @file QuickSort.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Quick Sort implementation using Hoare partitioning to sort a given data set.
 *        As the data set is partitioned via high and low values, along with a split point
 *        acting as a divider, data is sorted in-place, and the sorting function is called
 *        recursively as we approach smaller subsets of data.
 * 
 *        Time Complexity:
 *              Best Case       Worst Case
 *              O(n logn)       O(n^2)
 */

class QuickSort {

    private:
        /**
         * @brief The QSort() function uses Hoare partitioning to sort in-place while
         * subdividing the given dataset using a split point.
         * @param dataSet The vector of data to be sorted
         * @param lo The lowest index of the data set or subset
         * @param hi The highest index of the data set or subset
         */
        static void QSort(std::vector<int>& dataSet, int lo, int hi) {
            if (lo < hi) {
                int splitPoint = Partition(dataSet, lo, hi);
                QSort(dataSet, lo, splitPoint);
                QSort(dataSet, splitPoint + 1, hi);
            }
        }

        /**
         * @brief The Partition() function uses the pivot value (the value to compare other
         * data set members to) to either swap members or be used as the split point for 
         * the recursive callback of QSort().
         * @param dataSet The vector of data to be sorted
         * @param lo The lowest index of the data set or subset
         * @param hi The highest index of the data set or subset
         * @return Returns the index j to be used as the split point in the next recursive
         * callback
         */
        static int Partition(std::vector<int>& dataSet, int lo, int hi) {
            int pivot = dataSet[lo];
            int i = lo - 1, j = hi + 1;

            while (true) {
                do {
                    i++;
                } while (dataSet[i] < pivot);

                do {
                    j--;
                } while (dataSet[j] > pivot);

                if (i < j)
                    Swap(dataSet, i, j);
                else
                    return j;
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
         * @brief The Sort() function is the public facing function to invoke QSort().
         * @param dataSet The vector of data to be sorted
         * @return Returns the now sorted vector
         */
        std::vector<int> Sort(std::vector<int>& dataSet) {
            QSort(dataSet, 0, dataSet.size() - 1);

            return dataSet;
        }

};