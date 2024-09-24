#ifndef METRIC_FUNCTIONS_HPP
#define METRIC_FUNCTIONS_HPP

#include <vector>
#include "Graph.hpp"

// Declarations of the common functions

int totalMSTWeight(const std::vector<Edge>& mstEdges);
int longestDistance(const std::vector<Edge>& mstEdges, int n);
double averageDistance(const std::vector<std::vector<Edge>>& adj, int n);
int shortestMSTDistance(int u, int v, const std::vector<Edge>& mstEdges, int n);
void dfs(int node, const std::vector<std::vector<Edge>>& adj, std::vector<bool>& visited, std::vector<int>& dist, int& farthestNode, int& maxDist);
std::vector<std::vector<Edge>> buildAdjacencyList(const std::vector<Edge>& mstEdges, int n);

#endif // METRIC_FUNCTIONS_HPP
