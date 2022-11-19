#pragma once

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
 * @brief 
 */

/// TODO: Adopt template format or move function definitions to source file

class DijkstrasAdjacencyList
{

    private:
    constexpr static double EPS = 1e-6;                         // Epsilon value for comparing doubles
    int m_nodeCount = 0;                                        // Number of nodes in the graph
    std::vector<double> dist;                                   // Distance between nodes
    std::vector<int> prev;                                      // Used to reconstruct the shorted path
    std::unordered_map<int, std::list<Edge>> graph;             // Adjacency list of graph

    /**
     * @brief The CreateEmptyGraph() function creates an empty graph.
     * @param nodeCount The number of nodes in the graph
     * @return Returns the empty graph
     */
    std::unordered_map<int, std::list<Edge>> CreateEmptyGraph(int nodeCount)
    {
        std::list<Edge> emptyEdgeList;

        for (int i = 0; i < nodeCount - 1; i++)
            graph.emplace(i, emptyEdgeList);

        return graph;
    }

    /**
     * @brief The Compare() function compares two nodes to determine their priority in the priority queue.
     * @param node1 First node in comparison
     * @param node2 Second node in comparison
     * @return Returns '1' if the value of node1 is greater than node2, otherwise it returns '-1'
     */
    static int Compare(Node node1, Node node2)
    {
        if (std::abs(node1.m_value - node2.m_value) < EPS)
            return 0;
        
        return (node1.m_value - node2.m_value) > 0 ? 1 : -1;
    }

    public:
    /**
     * @brief DijkstrasAdjacencyList constructor and destructor
     * @param nodeCount The number of nodes in the graph
     */
    DijkstrasAdjacencyList(int nodeCount) 
        : m_nodeCount(nodeCount)
    {
        this->graph = CreateEmptyGraph(nodeCount);
        this->dist.resize(nodeCount);
        this->prev.resize(nodeCount);
    }

    ~DijkstrasAdjacencyList()
    {

    }

    /**
     * @brief The AddEdge() function adds an edge to the graph.
     * @param to Id of the node at the end of the directed edge
     * @param cost The edge weight
     */
    void AddEdge(int from, int to, double cost)
    {
        auto it = graph.find(from);
        
        if (it != graph.end())
            it->second.emplace_back(from, to, cost);
        // else
        // {
        //     std::list<Edge> edgeList;
        //     edgeList.emplace_back(from, to, cost);
        //     graph.emplace(from, edgeList);
        // }
    }

    /**
     * @brief The GetGraph() function returns the current graph instance.
     */
    std::unordered_map<int, std::list<Edge>> GetGraph()
    {
        return graph;
    }

    /**
     * @brief The Dijkstras() function
     * @param start Id of the starting node
     * @param end Id of the ending node
     * @return Returns the shortest distance from the start node to the end node
     */
    double Dijkstras(int start, int end)
    {
        // Maintain an array of the minimum distance to each node, with the starting node set to 0
        for (int i = 0; i < m_nodeCount; i++)
            dist[i] = INFINITY;

        dist[start] = 0;

        // Keep a priority queue of the next most promising node
        std::priority_queue<Node, std::vector<Node>, std::function<int(Node, Node)>> pq(Compare);
        pq.emplace(Node(start, 0.0));

        // Vector used to track visited nodes
        std::vector<bool> visited;
        visited.resize(m_nodeCount);

        while (!pq.empty())
        {
            Node node = pq.top();
            pq.pop();
            visited[node.m_id] = true;

            if (dist[node.m_id] < node.m_value)
                continue;

            // Get the edge list of the current node
            auto it = graph.find(node.m_id);

            // Check if the edge list is empty
            if (it == nullptr)
                continue;

            std::list<Edge> edges = it->second;

            for (auto edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt)
            {
                Edge edge = *edgeIt;

                // Check if we've already visited this node
                if (visited[edge.m_to])
                    continue;

                // Try to relax the current edge
                double newDist = dist[edge.m_from] + edge.m_cost;

                if (newDist < dist[edge.m_to])
                {
                    prev[edge.m_to] = edge.m_from;
                    dist[edge.m_to] = newDist;
                    pq.emplace(Node(edge.m_to, dist[edge.m_to]));
                }
            }

            // We've reached the end node
            if (node.m_id == end)
                return dist[end];
        }

        // Node is unreachable
        return INFINITY;
    }

    /**
     * @brief The ReconstructPath() function reconstructs the shortest path from the 'start' node to the
     *      'end' node.
     * @param start The starting node
     * @param end The ending node
     * @return Returns a list of nodes forming the shortest path from 'start' to 'end'
     */
    std::list<int> ReconstructPath(int start, int end)
    {
        if ((end < 0) || (end >= m_nodeCount))
            throw "Invalid node index";
        else if ((start < 0) || (start >= m_nodeCount))
            throw "Invalid node index";

        double dist = Dijkstras(start, end);
        std::list<int> path;

        if (dist == INFINITY)
        {
            path.emplace_back(NULL);

            return path;
        }

        /// TODO: Update termination value for loop
        for (int at = end; at != 0; at = prev[at])
            path.emplace_back(at);

        path.reverse();

        return path;
    }

    /**
     * @brief The PrintInfo() function prints a list of nodes and their outgoing edges.
     */
    void PrintInfo()
    {
        std::cout << "\nAdjacency List:" << std::endl;

        for (auto it = graph.begin(); it != graph.end(); ++it)
            for (auto edgeIt = it->second.begin(); edgeIt != it->second.end(); ++edgeIt)
                std::cout << it->first << ": [" << edgeIt->m_from << ", " << edgeIt->m_to << ", " <<
                    edgeIt->m_cost << "]" << std::endl;

        std::list<int> path = ReconstructPath(0, 4);
        std::cout << "\nPath:" << std::endl;

        for (auto it = path.begin(); it != path.end(); ++it)
            std::cout << *it << " ";

        std::cout << "\nDistance Array:" << std::endl;

        for (int i = 0; i < m_nodeCount; i++)
            std::cout << dist[i] << " ";
    }

};