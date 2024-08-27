#include "graph.hpp"

Graph::Graph(int n) {
    numVertices = n;
    adjList.resize(n);
}

void Graph::addEdge(int src, int dest, double weight) {
    Edge edge = {src, dest, weight};
    adjList[src].push_back(edge);
}