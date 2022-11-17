#include "FindSubstrings.h"

/**
 * @file FindSubstrings.cpp
 * @author 0xChristopher
 * @brief Funcional implementation of the Substrings algorithm
 */

/**
 * @brief The FindSubstrings() function takes in a string, finds every unique substring, and counts the
 *      number of times each substring occurs within the string.
 */
std::map<std::string, int> Substrings::FindSubstrings(std::string& S, int& totalSubstrings)
{
    std::map<std::string, int> ssMap = {};          // Map of substrings and their number of occurences
    int len = S.length();                           // The length of the given string

    // Iterate over the string starting from each letter
    for (int i = 0; i < len; i++)
    {
        // Iterate over each additional letter until we reach the length of the string
        for (int j = 1; j <= len ; j++)
        {
            std::string ss = S.substr(i, j);
                
            // Check if we already have a key in our map for a given substring
            auto exists = ssMap.find(ss);

            // If it doesn't exist, find the number of occurences in the string
            if (exists == ssMap.end())
            {
                int occurences = 0;
                int ssLen = ss.length();

                // Iterate over the string, so long as we don't exceed the length of the string, given our 
                // substring's length as we compare
                for (int k = 0; k < len; k++)
                {
                    // Break if we're out of bounds
                    if (ssLen + k > len)
                        break;

                    std::string match = S.substr(k, ssLen);

                    // Check if our current substring matches the substring we're comparing it to
                    if (match == ss)
                        occurences++;
                }

                // Add the substring and number of occurences to the map
                ssMap.emplace(ss, occurences);
                totalSubstrings++;
            }
        }
    }

    return ssMap;
}

/**
 * @brief The Display() function prints the contents of the substrings map along with the total number
 *      of substrings.
 */
void Substrings::Display(std::map<std::string, int>& substrings, int totalSubstrings)
{
    std::cout << "Results:" << std::endl;

    // Prints:
    // 4: a
    // 1: ab
    // 1: abo
    // 1: aboa
    // etc...
    for (auto it = substrings.begin(); it != substrings.end(); ++it)
        std::cout << it->second << ": " << it->first << std::endl;

    std::cout << "\nTotal number of substrings: " << totalSubstrings << std::endl;
}

int main ()
{
    int totalSubstrings = 0;                    // Total number of substrings
    std::string S = "banana boat";              // String to be analyzed
    Substrings sub = Substrings();              // Substrings instance

    // Remove spaces from the string if they exist
    S.erase(std::remove(S.begin(), S.end(), ' '), S.end());

    // Get map of substrings and their number of occurences
    std::map<std::string, int> substrings = sub.FindSubstrings(S, totalSubstrings);

    // Display result
    sub.Display(substrings, totalSubstrings);

    return 0;
}