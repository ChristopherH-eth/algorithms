#pragma once

/**
 * @file Edge.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief The Edge struct allows for the creation of Edges to be added to the graph adjacency list, which
 *      can later be processed through Dijkstra's Algorithm. Each Edge object keeps track of the Nodes 'to'
 *      and 'from', along with the weight or 'cost' between them, as they represent directional edges.
 */

struct Edge
{

    friend class DijkstrasAdjacencyList;

    private:
    int m_from = 0;                 // Id of the node at the start of the directed edge
    int m_to = 0;                   // Id of the node at the end of the directed edge
    double m_cost = 0.0;            // Edge weight

    public:
    /**
     * @brief Edge constructor and destructor
     * @param from Id of the node at the start of the directed edge
     * @param to Id of the node at the start of the directed edge
     * @param cost The weight of the edge
     */
    Edge(int from, int to, double cost)
        : m_from(from), m_to(to), m_cost(cost)
    {

    }

    ~Edge()
    {

    }
    
};