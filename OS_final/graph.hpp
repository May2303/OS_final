#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>

struct Edge {
    int source, dest;
    double weight;
};

class Graph {
public:
    int numVertices;
    std::vector<std::vector<Edge>> adjList;

    Graph(int n);
    void addEdge(int src, int dest, double weight);
};

#endif