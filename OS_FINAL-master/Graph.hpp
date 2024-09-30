#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

// Define the Edge structure
struct Edge {
    int u, v, weight;
};

// Define the Graph class
class Graph {
public:
    // Constructor
    Graph(int numVertices);
    
    // Add an edge to the graph
    void addEdge(int u, int v, int weight);
    
    // Get the adjacency list of the graph
    const std::vector<std::vector<Edge>>& getAdjacencyList() const;
    
    // Get the number of vertices
    int getNumVertices() const;

    // Remove an edge between u and v
    void removeEdge(int u, int v);

private:
    int numVertices;  // Number of vertices
    std::vector<std::vector<Edge>> adjList;  // Adjacency list representation
};

#endif // GRAPH_HPP
