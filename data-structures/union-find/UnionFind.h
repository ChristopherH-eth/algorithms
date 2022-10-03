#pragma once

#include <vector>

/**
 * @file UnionFind.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *         C++ conversion by 0xChristopher
 * @brief This Union Find (Disjoint Set) implementation is used to store a collection of
 *        disjoint, non-overlapping sets. Once initialized, a user can find the component
 *        a particular member belongs to, check if two elements belong to the same set, check
 *        the current number of components, check the size of each component, as well as unify
 *        two components that do not already belong to the same set. Additionally, when finding
 *        the root of a component, path compression will be performed to optimize future lookups.
 * 
 *        Time Complexity (Without Path Compression): O(n)
 *        Time Complexity (With Path Compression): O(a(n)) 
 */

class UnionFind {

    private:
        int m_size;                     /// The number of elements in the Union Find
        int numComponents;              /// The number of components in the union find
        int root, root1, root2;         /// Component roots
        std::vector<int> sz;            /// Tracks the size of each component
        std::vector<int> id;            /// id[i] points to the parent of i; if id[i] = i, then its root is itself

    public:
        /**
         * @brief Union Find constructor and destructor
         * @param size The number of elements in the Union Find
         */
        UnionFind(int size)
            : m_size(size) {
            if (size <= 0)
                throw "Size 0 or less";

            numComponents = size;
            sz.resize(size);
            id.resize(size);

            for (int i = 0; i < size; i++) {
                id[i] = i; /// Its root is itself
                sz[i] = 1; /// Each component is originally size 1
            }
        }

        ~UnionFind() {}

        /**
         * @brief The Find() function finds the root of which component 'p' belongs to.
         * @param p The element of a given component
         * @return Returns the root of the provided element
         */
        int Find(int p) {
            root = p;

            while (root != id[root])
                root = id[root];

            /// Compress the path back up to the root
            while (p != root) {
                int next = id[p];
                id[p] = root;
                p = next;
            }

            return root;
        }

        /**
         * @brief The Connected() function checks if two elements belong to the same component.
         * @param p The element of a given component
         * @param q The element of a given component
         * @return Returns true if p and q share the same root
         */
        bool Connected(int p, int q) {
            return Find(p) == Find(q);
        }

        /**
         * @brief The ComponentSize() function returns the size of a given component.
         * @param p The element of a given component
         * @return Returns the size of the component p belongs to
         */
        int ComponentSize(int p) {
            return sz[Find(p)];
        }

        /**
         * @brief The Size() function returns the size of the Union Find.
         * @return Returns the number of elements in the union find
         */
        int Size() {
            return m_size;
        }

        /**
         * @brief The Components() function returns the number of components in the Union Find.
         * @return Returns the number of components in the union find
         */
        int Components() {
            return numComponents;
        }

        /**
         * @brief The Unify() function attempts to unify two components at the larger component's
         * root, reducing the total number of components by 1.
         */
        void Unify(int p, int q) {
            /// Check if these elements are already in the same group
            if (Connected(p, q))
                return;

            root1 = Find(p);
            root2 = Find(q);

            /// Merge the smaller component into the larger one
            if (sz[root1] < sz[root2]) {
                sz[root2] += sz[root1];
                id[root1] = root2;
                sz[root1] = 0;
            } else {
                sz[root1] += sz[root2];
                id[root2] = root1;
                sz[root2] = 0;
            }

            numComponents--;
        }        

};