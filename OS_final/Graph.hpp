#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <algorithm> 

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

    void removeEdge(int u, int v);

private:
    int numVertices;  // Number of vertices
    std::vector<std::vector<Edge>> adjList;  // Adjacency list representation
};

// Implementation of the Graph class methods

Graph::Graph(int numVertices) : numVertices(numVertices), adjList(numVertices + 1) {}

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back({u, v, weight});
    adjList[v].push_back({v, u, weight});  // For undirected graph
}

const std::vector<std::vector<Edge>>& Graph::getAdjacencyList() const {
    return adjList;
}

int Graph::getNumVertices() const {
    return numVertices;
}

void Graph::removeEdge(int u, int v) {
    // Remove edge from adjacency list for u
    adjList[u].erase(std::remove_if(adjList[u].begin(), adjList[u].end(),
        [v](const Edge& e) { return e.v == v; }), adjList[u].end());
    
    // Remove edge from adjacency list for v
    adjList[v].erase(std::remove_if(adjList[v].begin(), adjList[v].end(),
        [u](const Edge& e) { return e.u == u; }), adjList[v].end());
}

#endif // GRAPH_HPP
