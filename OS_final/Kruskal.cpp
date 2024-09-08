#include "UnionFind.hpp"
#include "graph.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

// Function to find the Minimum Spanning Tree using Kruskal's algorithm
std::vector<std::pair<int, int>> kruskalMST(const Graph& graph) {
    std::vector<std::pair<int, std::pair<int, int>>> edges; // (weight, (src, dest))

    // Extract edges from the graph
    for (int i = 0; i < graph.getNumVertices(); ++i) {
        for (const auto& edge : graph.getAdjLists()[i]) {
            int dest = edge.first;
            int weight = edge.second;
            if (i < dest) { // To avoid adding the same edge twice in an undirected graph
                edges.push_back({weight, {i, dest}});
            }
        }
    }

    // Sort edges based on weight
    std::sort(edges.begin(), edges.end());

    UnionFind uf(graph.getNumVertices());
    std::vector<std::pair<int, int>> mst; // Minimum Spanning Tree

    // Process each edge in ascending order of weight
    for (const auto& edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        // Check if u and v are in different sets
        if (uf.find(u) != uf.find(v)) {
            // Union the sets
            uf.unionSets(u, v);
            // Add edge to MST
            mst.push_back({u, v});
        }
    }

    return mst;
}
