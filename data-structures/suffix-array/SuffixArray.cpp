#include <iostream>
#include <vector>
#include <string>

#include "SuffixArray.h"

/**
 * @file SuffixArray.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Functional demonstration of the SuffixArray class
 */

/**
 * @brief SuffixArray constructor with char array as input
 */
SuffixArray::SuffixArray(char *text) 
{
    if (strlen(text) == 0)
        throw "Text cannot be null";

    strcpy(this->t, text);
    this->size = strlen(text);
}

/**
 * @brief SuffixArray constructor with string as input
 */
SuffixArray::SuffixArray(std::string& sText) 
{
    const char* text = sText.c_str();

    if (strlen(text) == 0)
        throw "Text cannot be null";

    strcpy(this->t, text);
    this->size = strlen(text);
}

SuffixArray::~SuffixArray() 
{

}

/**
 * @brief The Kasai() function uses the Kasai algorithm to build the LCP Array.
 */
void SuffixArray::Kasai() 
{
    std::vector<int> inv;

    if (lcp.size() != 0) 
    {
        for (int i = 0; i < size; i++)
            lcp.pop_back();
    }

    if (inv.size() != 0) {
        for (int i = 0; i < size; i++)
            inv.pop_back();
    }

    lcp.resize(size);
    inv.resize(size);

    for (int i = 0; i < size; i++)
        inv[sa[i]] = i;

    for (int i = 0, len = 0; i < size; i++) {
        if (inv[i] > 0) {
            int k = sa[inv[i] - 1];

            while ((i + len < size) && (k + len < size) && t[i + len] == t[k + len])
                len++;

            lcp[inv[i]] = len;

            if (len > 0)
                len--;
        }
    }
}

/**
 * @brief The BuildSuffixArray() function calls the Construct() function.
 */
void SuffixArray::BuildSuffixArray() 
{
    if (constructedSa)
        return;

    Construct(t, size);
    constructedSa = true;
}

/**
 * @brief The BuildLcpArray() function builds the LCP Array by building the Suffix
 *      Array and then running the Kasai algorithm.
 */
void SuffixArray::BuildLcpArray() 
{
    if (constructedLcpArray)
        return;

    BuildSuffixArray();
    Kasai();
    constructedLcpArray = true;
}

/**
 * @brief The Construct() function builds the Suffix Array.
 */
std::vector<int> SuffixArray::Construct(char *t, int n) 
{
    suffixes.resize(n);

    for (int i = 0; i < n; i++) 
    {
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
 *      not match between them has a lower value in suffix a than suffix b, it returns 1, 
 *      otherwise it returns 0.
 */
int SuffixArray::Compare(Suffix& a, Suffix& b) 
{
    return strcmp(a.suffix, b.suffix) < 0 ? 1 : 0;
}

/**
 * @brief The GetTextLength() function gets the length of the text input.
 */
int SuffixArray::GetTextLength() 
{
    return size;
}

/**
 * @brief The GetSa() function calls the BuildSuffixArray() function.
 */
std::vector<int> SuffixArray::GetSa() 
{
    BuildSuffixArray();

    return sa;
}

/**
 * @brief The GetLcpArray() function calls the BuildLcpArray() function.
 */
std::vector<int> SuffixArray::GetLcpArray() 
{
    BuildLcpArray();

    return lcp;
}

/**
 * @brief The DisplayTable() function displays the Suffix and LCP Arrays in an easy to read
 *      format.
 */
void SuffixArray::DisplayTable() 
{
    printf("-----i-----SA-----LCP---Suffix\n");

    for (int i = 0; i < size; i++)
        printf("% 6d % 6d % 6d % 3s % s\n", i, sa[i], lcp[i], "", suffixes[i].suffix);
}

/**
 * @brief The DisplaySA() function displays the Suffix Array in an easy to read format.
 */
void SuffixArray::DisplaySA()
{
    for (int i = 0; i < size; i++)
        printf("%d: %s\n", sa[i], suffixes[i].suffix);
}

int main() 
{
    char text[] = "transcendence";          // Char array to be sorted into Suffix/LCP Array
    std::string sText = "follow";           // String to be sorted into Suffix/LCP Array
    std::vector<int> sa;                    // Vector for Suffix Array storage

    SuffixArray suffixArray(sText);

    // Sort data into Suffix Array
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Sorting data set..." << std::endl;
    sa = suffixArray.GetLcpArray();
    
    if (sa.size() != 0) 
    {
        std::cout << "Data set sorted! Printing values...\n{ ";

        for (int i = 0; i < sa.size(); i++)
            std::cout << sa[i] << " ";

        std::cout << "}" << std::endl;
    }

    std::cout << "------------------------------------------------------" << std::endl;

    // Print Suffix Array
    std::cout << "------------------------------------------------------" << std::endl;
    suffixArray.DisplaySA();
    std::cout << "------------------------------------------------------" << std::endl;

    // Print Suffix Array and LCP Array table
    std::cout << "------------------------------------------------------" << std::endl;
    suffixArray.DisplayTable();
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}