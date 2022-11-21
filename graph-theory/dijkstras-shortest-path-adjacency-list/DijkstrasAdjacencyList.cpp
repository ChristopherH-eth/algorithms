#include "DijkstrasAdjacencyList.h"

/**
 * @file DijkstrasAdjacencyList.cpp
 * @author Original JAVA by William Fiset (william.alexandre.fiset@gmail.com)
 *      C++ conversion by 0xChristopher
 * @brief Source file for Dijkstra's Algorithm implementation with an adjacency list.
 */

/**
 * @brief DijkstrasAdjacencyList constructor and destructor
 */
DijkstrasAdjacencyList::DijkstrasAdjacencyList(int nodeCount) 
    : m_nodeCount(nodeCount)
{
    // Create graph and resize the distance, previous node, and visited vectors for efficiency
    this->graph = CreateEmptyGraph(nodeCount);
    this->dist.resize(nodeCount);
    this->prev.resize(nodeCount);
    this->visited.resize(nodeCount);

    for (int i = 0; i < nodeCount; i++)
    {
        this->dist[i] = INFINITY;                   // Set all distances to infinity
        this->prev[i] = -1;                         // Set all previous node values to -1
        this->visited[i] = false;                   // Set visited values to false until traversed
    }
}

DijkstrasAdjacencyList::~DijkstrasAdjacencyList()
{

}

/**
 * @brief The CreateEmptyGraph() function creates an empty graph.
 */
std::unordered_map<int, std::list<Edge>> DijkstrasAdjacencyList::CreateEmptyGraph(int nodeCount)
{
    std::list<Edge> emptyEdgeList;
    graph.reserve(nodeCount);

    for (int i = 0; i < nodeCount; i++)
        graph.emplace(i, emptyEdgeList);

    return graph;
}

/**
 * @brief The Compare() function compares two nodes to determine their priority in the priority queue.
 */
int DijkstrasAdjacencyList::Compare(Node node1, Node node2)
{
    if (std::abs(node1.m_value - node2.m_value) < EPS)
        return 0;
    
    return (node1.m_value - node2.m_value) > 0 ? 1 : -1;
}

/**
 * @brief The AddEdge() function adds an edge to the graph.
 */
void DijkstrasAdjacencyList::AddEdge(int from, int to, double cost)
{
    auto it = graph.find(from);
    
    if (it != graph.end())
        it->second.emplace_back(from, to, cost);
}

/**
 * @brief The GetGraph() function returns the current graph instance.
 */
std::unordered_map<int, std::list<Edge>> DijkstrasAdjacencyList::GetGraph()
{
    return graph;
}

/**
 * @brief The Dijkstras() function performs Dijkstra's shortest path algorithm.
 */
double DijkstrasAdjacencyList::Dijkstras(int start, int end)
{
    // Set the starting node distance to 0
    dist[start] = 0;

    // Keep a priority queue of the next most promising node
    std::priority_queue<Node, std::vector<Node>, std::function<int(Node, Node)>> pq(Compare);
    pq.emplace(Node(start, 0.0));

    while (!pq.empty())
    {
        Node node = pq.top();
        pq.pop();
        visited[node.m_id] = true;

        // Check if we've already found a better distance
        if (dist[node.m_id] < node.m_value)
            continue;

        // Get the edge list of the current node
        auto it = graph.find(node.m_id);
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
                prev[edge.m_to] = edge.m_from;                      // Set 'prev' of destination node to current node
                dist[edge.m_to] = newDist;                          // Set 'dist' of destination node to new best distance
                pq.emplace(Node(edge.m_to, dist[edge.m_to]));       // Add node to the priority queue
            }
        }

        // We've reached the end node; this conditional can be placed outside the while loop if
        // we don't want to stop early
        if (node.m_id == end)
            return dist[end];
    }

    // Node is unreachable
    return INFINITY;
}

/**
 * @brief The ReconstructPath() function reconstructs the shortest path from the 'start' node to the
 *      'end' node.
 */
std::list<int> DijkstrasAdjacencyList::ReconstructPath(int start, int end)
{
    if ((end < 0) || (end > m_nodeCount))
        throw "Invalid node index";
    else if ((start < 0) || (start > m_nodeCount))
        throw "Invalid node index";

    double dist = Dijkstras(start, end);
    std::list<int> path;

    // Check if the node we're trying to get to is reachable
    if (dist == INFINITY)
    {
        path.emplace_back(0);

        return path;
    }

    // Construct path backwords, then reverse it
    for (int at = end; at != -1; at = prev[at])
        path.emplace_back(at);

    path.reverse();

    return path;
}

/**
 * @brief The PrintInfo() function prints a list of nodes and their outgoing edges. This function
 *      tests algorithm implementation.
 */
void DijkstrasAdjacencyList::PrintInfo()
{
    std::cout << "\nAdjacency List:" << std::endl;

    for (auto it = graph.begin(); it != graph.end(); ++it)
        for (auto edgeIt = it->second.begin(); edgeIt != it->second.end(); ++edgeIt)
            std::cout << it->first << ": [" << edgeIt->m_from << ", " << edgeIt->m_to << ", " <<
                edgeIt->m_cost << "]" << std::endl;

    std::list<int> path = ReconstructPath(0, 5);
    std::cout << "\nPath:" << std::endl;

    for (auto it = path.begin(); it != path.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n\nDistance Array:" << std::endl;

    for (int i = 0; i < m_nodeCount; i++)
        std::cout << dist[i] << " ";
}

int main()
{
    int n = 6;                                  // Number of nodes
    DijkstrasAdjacencyList dalist(n);           // DijkstrasAdjacencyList instance

    // Populate graph
    dalist.AddEdge(0, 1, 12.5);
    dalist.AddEdge(0, 2, 5.2);
    dalist.AddEdge(1, 4, 3.3);
    dalist.AddEdge(3, 5, 2.2);
    dalist.AddEdge(2, 5, 9.2);

    dalist.PrintInfo();

    return 0;
}