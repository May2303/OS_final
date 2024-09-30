#include "MSTAlgorithms.hpp" 
#include <queue>            
#include <vector>          
#include <limits>     
std::vector<Edge> prim(const Graph& graph){
    int n = graph.getNumVertices(); // Get the number of vertices from the graph
    const auto& adj = graph.getAdjacencyList(); // Get the adjacency list

    std::vector<Edge> mstEdges; // To store the edges of the MST
    std::vector<bool> inMST(n + 1, false); // Track vertices included in the MST
    std::vector<int> parent(n + 1, -1); // To store the parent of each vertex in the MST
    std::vector<int> key(n + 1, std::numeric_limits<int>::max()); // Key values for minimum weight edge
    using pii = std::pair<int, int>; // Pair to represent (weight, vertex)

    // Comparator for the priority queue (min-heap)
    auto cmp = [](const pii& a, const pii& b) { return a.first > b.first; };
    std::priority_queue<pii, std::vector<pii>, decltype(cmp)> minHeap(cmp); // Priority queue for edges

    key[1] = 0; // Start with vertex 1 (assuming vertices are 1-indexed)
    minHeap.push({0, 1}); // Push the starting vertex into the min-heap

    // Main loop to process all vertices
    while (!minHeap.empty()) {
        int u = minHeap.top().second; // Get the vertex with the minimum key value
        minHeap.pop(); // Remove the vertex from the priority queue

        inMST[u] = true; // Mark the vertex as included in the MST

        // Iterate through all adjacent vertices of u
        for (const Edge& edge : adj[u]) {
            int v = edge.v; // Adjacent vertex
            int weight = edge.weight; // Weight of the edge

            // If the adjacent vertex v is not in the MST and the weight is smaller than the current key
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight; // Update the key value for vertex v
                minHeap.push({key[v], v}); // Add the vertex to the priority queue with the updated key
                parent[v] = u; // Update the parent of vertex v
            }
        }
    }

    // Build the MST edge list from parent information
    for (int i = 2; i <= n; ++i) { // Starting from 2 since 1 is the root
        if (parent[i] != -1) {
            mstEdges.push_back({parent[i], i, key[i]}); // Add edge to the MST
        }
    }

    return mstEdges; // Return the list of edges in the MST
}
