#pragma once

/**
 * @file Suffix.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Suffix struct to be used in creating a Suffix Array.
 */

struct Suffix 
{

    friend class SuffixArray;

    private:
        int index;          // Index of the suffix in the array
        char *suffix;       // Suffix text
    
};