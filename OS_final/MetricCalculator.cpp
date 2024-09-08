#include "MetricCalculator.hpp"
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>
#include <cmath>

// Calculate total weight of the MST
int MetricCalculator::calculateTotalWeight(const MST& mst) {
    int totalWeight = 0;
  /*  for (const auto& edge : mst.getEdges()) {
        int weight;
        std::tie(std::ignore, std::ignore, weight) = edge;
        totalWeight += weight;
    }
    */
    return totalWeight;
}

// Calculate longest distance between any two vertices using BFS/DFS
int MetricCalculator::calculateLongestDistance(const Graph& graph, const MST& mst) {
    // Implementation of longest distance calculation
    // e.g., BFS from each node to find the farthest node
    return 0; // Placeholder
}

// Calculate average distance between all pairs of nodes
double MetricCalculator::calculateAverageDistance(const Graph& graph) {
    int numVertices = graph.getNumVertices();
    double totalDistance = 0;
    int count = 0;

    // Compute all pairs shortest paths, e.g., using Floyd-Warshall
    // or Dijkstra's from each node, then compute average

    return count > 0 ? totalDistance / count : 0;
}

// Calculate shortest distance between two nodes in MST
int MetricCalculator::calculateShortestDistanceInMST(const Graph& graph, const MST& mst, int u, int v) {
    // Find the shortest path in MST using DFS or BFS
    return 0; // Placeholder
}
