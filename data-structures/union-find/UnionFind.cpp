#include <iostream>
#include "UnionFind.h"

/**
 * @file UnionFind.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief Functional demonstration of the Union Find (Disjoint Set)
 */

static int size = 10;                           /// The size of the Union Find
int set[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};     /// The elements within the Union Find

int main() {
    UnionFind unionFind(size);

    /// @brief Check that the Union Find has been initialized
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Union Find size: " << unionFind.Size() << std::endl;
    std::cout << "Number of components: " << unionFind.Components() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Unify components
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Unifying components..." << std::endl;

    unionFind.Unify(set[1], set[7]);
    unionFind.Unify(set[2], set[7]);
    unionFind.Unify(set[0], set[5]);
    unionFind.Unify(set[6], set[8]);
    
    std::cout << "Union Find size: " << unionFind.Size() << std::endl;
    std::cout << "Number of components: " << unionFind.Components() << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Find the component root of a particular member
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "The root of the component that " << set[7] << " belongs to is: " << 
        unionFind.Find(set[7]) << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    /// @brief Check component size
    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Size of component that contains 3: " << unionFind.ComponentSize(set[2]) << std::endl;
    std::cout << "Size of component that contains 6: " << unionFind.ComponentSize(set[5]) << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    std::cin.get();
}