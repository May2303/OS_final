#include <iostream>     
#include <vector>      
#include <algorithm>   
#include "MSTAlgorithms.hpp" 
#include <numeric>


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
std::vector<std::pair<int, int>> KruskalAlgorithm::play_mst(int n, const std::vector<std::vector<Edge>>& adj) {
    std::vector<Edge> edgeList;

    // Convert adjacency list to a list of edges
    for (int i = 0; i < n; ++i) {
        for (const Edge& e : adj[i]) {
            if (i < e.v) {
                edgeList.push_back(e);
            }
        }
    }

    std::vector<Edge> mstEdges;
    std::vector<int> parent(n);
    std::vector<int> rank(n, 0);

    // Initialize Union-Find data structure
    std::iota(parent.begin(), parent.end(), 0); // parent[i] = i

    // Sort all edges in non-decreasing order of their weight
    std::sort(edgeList.begin(), edgeList.end());

    // Process each edge in sorted order
    for (const Edge& e : edgeList) {
        int u = e.u;
        int v = e.v;
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSets(u, v, parent, rank);
            mstEdges.push_back(e);
        }
    }

    // Convert edge list to a list of pairs for the result
    std::vector<std::pair<int, int>> mstPairs;
    for (const Edge& e : mstEdges) {
        mstPairs.emplace_back(e.u, e.v);
    }
    
    return mstPairs;
}
