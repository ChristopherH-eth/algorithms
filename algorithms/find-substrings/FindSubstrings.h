#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

/**
 * @file FindSubstrings.h
 * @author 0xChristopher
 * @brief This algorithm is used to find all substrings of a given strings and the number of time they occur
 *      within said string. First, any spaces from the string in case the string in question is a phrase
 *      and not just a word, which is done prior to executing the algorithm. Upon entering the algorithm, it
 *      looks at each letter of the string, then each letter occuring thereafter, adding each one to the
 *      initial letter. A check is performed to see if a possible substring has already been computed, and
 *      if it has, the algorithm skips it.
 * 
 *      On each iteration for new substrings, it then compares the current substring in-place to a substring 
 *      of matching size until the boundary of the string is reached. On each match, the 'occurences' 
 *      variable is updated, and after all possible matches are checked, the substring is added to the map 
 *      which is then returned at the end of the function.
 * 
 *      Time Complexity: O(n*m*k) where n is the number of letters in the string, m is the remaining letters
 *          in the string to create substrings with, and k is the number of comparisons per substring.
 *      Space Complexity: O(n)
 */

class Substrings
{

    public:
    /**
     * @brief The FindSubstrings() function takes in a string, finds every unique substring, and counts the
     *      number of times each substring occurs within the string.
     * @param S The string to have its substrings computed
     * @param totalSubstrings Keeps track of the total number of substrings
     * @return Returns the map of substrings and their number of occurences
     */
    std::map<std::string, int> FindSubstrings(std::string& S, int& totalSubstrings);

    /**
     * @brief The Display() function prints the contents of the substrings map along with the total number
     *      of substrings.
     * @param S The string to have its substrings computed
     * @param totalSubstrings Keeps track of the total number of substrings
     */
    void Display(std::map<std::string, int>& substrings, int totalSubstrings);

};