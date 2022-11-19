#pragma once

/**
 * @file Node.h
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief The Node struct is used to create Node helper objects that act as placeholders for node id
 *      and distance information.  For instance, when a Node is added to the priority queue, it is typically
 *      added with the id of the next best Node, along with its distance from the previous Node to it when
 *      calculating the shortest path.
 */

struct Node
{

    friend class DijkstrasAdjacencyList;

    private:
    int m_id = 0;                   // Index of a given node
    double m_value = 0.0;           // Distance value from a particular node

    public:
    /**
     * @brief Node constructor and destructor
     * @param id Node index
     * @param value Node distance from a particular node value
     */
    Node(int id, double value)
        : m_id(id), m_value(value)
    {

    }

    ~Node()
    {

    }

};