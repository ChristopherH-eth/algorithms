#include <iostream>

#include "DijkstrasAdjacencyList.h"

/**
 * @file DijkstrasAdjacencyList.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Source file for Dijkstra's Algorithm implementation with an adjacency list.
 */

int n = 6;              // Number of nodes

int main()
{
    DijkstrasAdjacencyList dalist(n);

    // Populate graph
    dalist.AddEdge(0, 1, 12.5);
    dalist.AddEdge(0, 2, 5.2);
    dalist.AddEdge(1, 4, 3.3);
    dalist.AddEdge(3, 5, 2.2);
    dalist.AddEdge(2, 5, 9.2);

    dalist.PrintInfo();
}