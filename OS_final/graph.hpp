#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <utility> // for std::pair
#include <stdexcept>

class Graph {
public:
    // Constructor to initialize the graph with a specified number of vertices
    Graph(int vertices);

    // Adds a weighted directed edge from src to dest
    void addEdge(int src, int dest, int weight);

    // Sets the weight of a specific vertex
    void setVertexWeight(int vertex, int weight);

    // Gets the weight of a specific vertex
    int getVertexWeight(int vertex) const;

    // Prints the graph's adjacency list representation
    void printGraph() const;

    // Returns the number of vertices in the graph
    int getNumVertices() const;

    // Returns a constant reference to the adjacency lists of the graph
    const std::vector<std::list<std::pair<int, int>>>& getAdjLists() const;

private:
    int numVertices;  // Number of vertices in the graph
    std::vector<std::list<std::pair<int, int>>> adjLists; // Adjacency list where each pair contains a destination vertex and edge weight
    std::vector<int> vertexWeights; // Vertex weights
};

#endif // GRAPH_H
