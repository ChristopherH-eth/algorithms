#pragma once

#include <vector>
#include <stdlib.h>

/**
 * @file QuickSort3.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief 3-Way Quick Sort implementation based on the Dutch National Flag algorithm. This method is
 *        preferred over a normal quick sort if the data set to be sorted has multiple occurances
 *        of the same values. Where a normal quick sort would recursively sort these values, the 3-Way
 *        Quick Sort processes all occurences of the pivot, while using a random pivot value within the
 *        bounds of the data set, to improve time complexity.
 * 
 *        Time Complexity: O(n logn)
 */

class QuickSort3 {

    private:
        /**
         * @brief The Partition3() function partitions the the data set such that all elements whose
         * value is equal to the pivot are grouped together.
         * @param dataSet The vector of data to be sorted
         * @param lo The lowest index of the data set or subset
         * @param hi The highest index of the data set or subset
         * @return Returns a vector m containing j and k index midpoints to be used in recursive 
         * RandomizedQuickSort() calls and further partitioning as needed.
         */
        static std::vector<int> Partition3(std::vector<int>& dataSet, int lo, int hi) {
            int j, k;

            if (hi - lo <= 1) {
                if (dataSet[hi] < dataSet[lo])
                    Swap(dataSet, lo, hi);

                j = lo;
                k = hi;
                std::vector<int> m = {j, k};

                return m;
            }

            int mid = lo;
            int p = dataSet[hi];

            while (mid <= hi) {
                if (dataSet[mid] < p) {
                    Swap(dataSet, lo, mid);
                    lo++;
                    mid++;
                } else if (dataSet[mid] == p) {
                    mid++;
                } else {
                    Swap(dataSet, mid, hi);
                    hi--;
                }
            }

            j = lo - 1;
            k = mid;
            std::vector<int> m = {j, k};

            return m;
        }

        /**
         * @brief The RandomizedQuickSort() function chooses a pivot value at random, improving
         * time complexity.
         * @param dataSet The vector of data to be sorted
         * @param lo The lowest index of the data set or subset
         * @param hi The highest index of the data set or subset
         */
        static void RandomizedQuickSort(std::vector<int>& dataSet, int lo, int hi) {
            if (lo >= hi)
                return;

            int k = (rand() % (hi - lo + 1) + lo);
            int t = dataSet[lo];
            dataSet[lo] = dataSet[k];
            dataSet[k] = t;

            std::vector<int> m = Partition3(dataSet, lo, hi);
            RandomizedQuickSort(dataSet, lo, m[0]);
            RandomizedQuickSort(dataSet, m[1], hi);
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
         * @brief The Sort() function is the public facing function to invoke RandomizedQuickSort().
         * @param dataSet The vector of data to be sorted
         * @return Returns the now sorted vector
         */
        std::vector<int> Sort(std::vector<int>& dataSet) {
            RandomizedQuickSort(dataSet, 0, dataSet.size() - 1);

            return dataSet;
        }

};