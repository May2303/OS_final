#include "Graph.hpp"
#include <algorithm>  // For std::remove_if

// Constructor
Graph::Graph(int numVertices) : numVertices(numVertices), adjList(numVertices + 1) {}

// Add an edge to the graph
void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back({u, v, weight});
    adjList[v].push_back({v, u, weight});  // For undirected graph
}

// Get the adjacency list of the graph
const std::vector<std::vector<Edge>>& Graph::getAdjacencyList() const {
    return adjList;
}

// Get the number of vertices
int Graph::getNumVertices() const {
    return numVertices;
}

// Remove an edge between u and v
void Graph::removeEdge(int u, int v) {
    // Remove edge from adjacency list for u
    adjList[u].erase(std::remove_if(adjList[u].begin(), adjList[u].end(),
        [v](const Edge& e) { return e.v == v; }), adjList[u].end());
    
    // Remove edge from adjacency list for v
    adjList[v].erase(std::remove_if(adjList[v].begin(), adjList[v].end(),
        [u](const Edge& e) { return e.u == u; }), adjList[v].end());
}
