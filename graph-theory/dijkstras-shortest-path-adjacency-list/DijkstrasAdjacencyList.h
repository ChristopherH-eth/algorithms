#pragma once

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <math.h>
#include <queue>
#include <functional>

#include "../dijkstras-shortest-path-adjacency-list/Edge.h"
#include "../dijkstras-shortest-path-adjacency-list/Node.h"

/**
 * @file DijkstrasAdjacencyList.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief The DijkstrasAdjancencyList class implements Dijkstra's shortest path algorithm. It finds the
 *      shortest path from a given start node to a given end node if such a path is possible. In this
 *      implementation, the algorithm stops early if the end node is found before exploring every node
 *      in the graph.
 * 
 *      Time Complexity: O(V+E)
 */

class DijkstrasAdjacencyList
{

    private:
    constexpr static double EPS = 1e-6;                         // Epsilon value for comparing doubles
    int m_nodeCount = 0;                                        // Number of nodes in the graph
    std::vector<double> dist;                                   // Minimum distance between nodes
    std::vector<int> prev;                                      // Used to reconstruct the shorted path
    std::vector<bool> visited;                                  // Keep track of visited nodes
    std::unordered_map<int, std::list<Edge>> graph;             // Adjacency list of graph

    /**
     * @brief The CreateEmptyGraph() function creates an empty graph.
     * @param nodeCount The number of nodes in the graph
     * @return Returns the empty graph
     */
    std::unordered_map<int, std::list<Edge>> CreateEmptyGraph(int nodeCount);

    /**
     * @brief The Compare() function compares two nodes to determine their priority in the priority queue.
     * @param node1 First node in comparison
     * @param node2 Second node in comparison
     * @return Returns '1' if the value of node1 is greater than node2, otherwise it returns '-1'
     */
    static int Compare(Node node1, Node node2);

    public:
    /**
     * @brief DijkstrasAdjacencyList constructor and destructor
     * @param nodeCount The number of nodes in the graph
     */
    DijkstrasAdjacencyList(int nodeCount);

    ~DijkstrasAdjacencyList();

    /**
     * @brief The AddEdge() function adds an edge to the graph.
     * @param to Id of the node at the end of the directed edge
     * @param cost The edge weight
     */
    void AddEdge(int from, int to, double cost);

    /**
     * @brief The GetGraph() function returns the current graph instance.
     */
    std::unordered_map<int, std::list<Edge>> GetGraph();

    /**
     * @brief The Dijkstras() function performs Dijkstra's shortest path algorithm.
     * @param start Id of the starting node
     * @param end Id of the ending node
     * @return Returns the shortest distance from the start node to the end node
     */
    double Dijkstras(int start, int end);

    /**
     * @brief The ReconstructPath() function reconstructs the shortest path from the 'start' node to the
     *      'end' node.
     * @param start The starting node
     * @param end The ending node
     * @return Returns a list of nodes forming the shortest path from 'start' to 'end'
     */
    std::list<int> ReconstructPath(int start, int end);

    /**
     * @brief The PrintInfo() function prints a list of nodes and their outgoing edges. This function
     *      tests algorithm implementation.
     */
    void PrintInfo();

};