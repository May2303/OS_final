#ifndef MSTALGORITHMS_H
#define MSTALGORITHMS_H

#include <vector>

// Define the Edge structure
struct Edge {
    int u, v, weight;
};

// Function declarations for MST algorithms
std::vector<std::pair<int, int>> prim(int n, const std::vector<std::vector<Edge>>& adj);
std::vector<Edge> kruskal(int n, std::vector<Edge>& edges);

// New function declarations
int totalMSTWeight(const std::vector<Edge>& mstEdges);
int longestDistance(const std::vector<Edge>& mstEdges, int n);
double averageDistance(const std::vector<std::vector<Edge>>& adj, int n);
int shortestMSTDistance(int u, int v, const std::vector<Edge>& mstEdges, int n);

#endif // MSTALGORITHMS_H
