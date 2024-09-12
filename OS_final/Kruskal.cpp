#include <iostream>     
#include <vector>      
#include <algorithm>   
#include "MSTAlgorithms.hpp" 
#include <numeric>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int u, v, weight; // The vertices connected by the edge and its weight

    // Overload the less-than operator for sorting edges based on their weights
    bool operator<(const Edge& e) const {
        return weight < e.weight; // Compare edges by weight
    }
};

// Find the representative (or root) of the set containing vertex u
int findParent(int u, vector<int>& parent) {
    if (parent[u] != u) {
        // Path compression: make the tree flatter for efficiency
        parent[u] = findParent(parent[u], parent);
    }
    return parent[u]; // Return the root of the set
}


// Union the sets containing vertices u and v
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent); // Find root of u
    int rootV = findParent(v, parent); // Find root of v

    if (rootU != rootV) {
        // Union by rank: attach the smaller tree under the larger tree
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU; // Attach rootV's tree under rootU's tree
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV; // Attach rootU's tree under rootV's tree
        } else {
            parent[rootV] = rootU; // Arbitrarily choose rootU as new root
            rank[rootU]++; // Increase the rank of the new root
        }
    }
}


// Kruskal's algorithm to find the Minimum Spanning Tree (MST)
vector<Edge> kruskal(int n, vector<Edge>& edges) {
    vector<Edge> mstEdges; // To store the edges of the MST
    vector<int> parent(n + 1), rank(n + 1, 0); // Initialize parent and rank for Union-Find

    iota(parent.begin(), parent.end(), 0); // Initialize parent array to self (each node is its own parent)
    sort(edges.begin(), edges.end()); // Sort all edges in non-decreasing order of their weight

    // Process each edge in sorted order
    for (const Edge& e : edges) {
        int u = e.u, v = e.v; // Get vertices of the edge
        if (findParent(u, parent) != findParent(v, parent)) {
            // If u and v are not in the same set, include this edge in the MST
            unionSets(u, v, parent, rank); // Union the sets containing u and v
            mstEdges.push_back(e); // Add edge to MST
        }
    }

    return mstEdges; // Return the edges of the MST
}
