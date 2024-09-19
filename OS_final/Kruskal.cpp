#include "MSTAlgorithms.hpp"
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

// Helper function to find the representative (or root) of the set containing vertex u
int findParent(int u, std::vector<int>& parent) {
    if (parent[u] != u) {
        parent[u] = findParent(parent[u], parent); // Path compression
    }
    return parent[u];
}

// Helper function to union the sets containing vertices u and v
void unionSets(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Define the compute method for Kruskal's algorithm
std::vector<Edge> KruskalAlgorithm::play_mst(const Graph& graph) {
    std::vector<Edge> edgeList;
    const auto& adj = graph.getAdjacencyList();
    int n = graph.getNumVertices();

    // Convert adjacency list to a list of edges
    for (int i = 1; i <= n; ++i) { // Assuming vertices are 1-indexed
        for (const Edge& e : adj[i]) {
            if (i < e.v) { // To avoid adding both directions of an undirected edge
                edgeList.push_back(e);
            }
        }
    }

    std::vector<Edge> mstEdges;
    std::vector<int> parent(n + 1);
    std::vector<int> rank(n + 1, 0);

    // Initialize Union-Find data structure
    std::iota(parent.begin(), parent.end(), 0); // parent[i] = i

    // Sort all edges in non-decreasing order of their weight
    std::sort(edgeList.begin(), edgeList.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // Process each edge in sorted order
    for (const Edge& e : edgeList) {
        int u = e.u;
        int v = e.v;
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSets(u, v, parent, rank);
            mstEdges.push_back(e);
        }
    }

    return mstEdges; // Return the list of edges in the MST
}
