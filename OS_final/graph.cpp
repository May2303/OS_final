#include "graph.hpp"
#include <iostream>
#include <stdexcept>

Graph::Graph(int vertices) : numVertices(vertices), adjLists(vertices), vertexWeights(vertices, 0) {
    // Initialize the graph with the given number of vertices.
    // Each vertex starts with an empty adjacency list.
}

void Graph::addEdge(int src, int dest, int weight) {
    // Ensure the source and destination vertices are within valid range
    if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    
    // Add a directed edge from src to dest with the given weight
    adjLists[src].emplace_back(dest, weight);
    // No reverse edge is added as this is a directed graph
}

void Graph::setVertexWeight(int vertex, int weight) {
    // Ensure the vertex index is within valid range
    if (vertex < 0 || vertex >= numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    
    // Set the weight of the specified vertex
    vertexWeights[vertex] = weight;
}

int Graph::getVertexWeight(int vertex) const {
    // Ensure the vertex index is within valid range
    if (vertex < 0 || vertex >= numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    
    // Return the weight of the specified vertex
    return vertexWeights[vertex];
}

void Graph::printGraph() const {
    // Print the adjacency list representation of the graph
    for (int i = 0; i < numVertices; ++i) {
        // Print vertex index and its weight
        std::cout << "Vertex " << i << " (Weight: " << vertexWeights[i] << "):";
        
        // Print all edges and their weights for the current vertex
        for (const auto& edge : adjLists[i]) {
            std::cout << " -> (" << edge.first << ", " << edge.second << ")";
        }
        std::cout << std::endl;
    }
}

int Graph::getNumVertices() const {
    // Return the number of vertices in the graph
    return numVertices;
}

const std::vector<std::list<std::pair<int, int>>>& Graph::getAdjLists() const {
    // Return a constant reference to the adjacency lists
    return adjLists;
}
