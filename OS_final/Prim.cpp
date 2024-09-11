#ifndef PRIM_H
#define PRIM_H

#include "MSTAlgorithms.hpp" 
#include <queue>            
#include <vector>          
#include <limits>     

// Prim class inherits from MST and implements Prim's algorithm to find the Minimum Spanning Tree (MST)
class Prim : public MST {
public:
    // Override the calculateMST method to implement Prim's algorithm
    std::vector<std::pair<int, int>> calculateMST(const Graph& graph) const override {
        std::vector<std::pair<int, int>> mstEdges; // To store the edges of the MST
        int numVertices = graph.getNumVertices();   // Get the number of vertices in the graph
        std::vector<bool> inMST(numVertices, false); // Track vertices included in the MST
        std::vector<int> parent(numVertices, -1);     // To store the parent of each vertex in the MST
        std::vector<int> key(numVertices, std::numeric_limits<int>::max()); // Key values to pick minimum weight edge
        using pii = std::pair<int, int>; // Pair to represent (weight, vertex)

        // Comparator for the priority queue (min-heap)
        auto cmp = [](const pii& a, const pii& b) { return a.first > b.first; };
        std::priority_queue<pii, std::vector<pii>, decltype(cmp)> minHeap(cmp); // Priority queue for edges

        key[0] = 0; // Start with vertex 0
        minHeap.push({0, 0}); // Push the starting vertex into the min-heap

        // Main loop to process all vertices
        while (!minHeap.empty()) {
            int u = minHeap.top().second; // Get the vertex with the minimum key value
            minHeap.pop(); // Remove the vertex from the priority queue

            inMST[u] = true; // Mark the vertex as included in the MST

            // Iterate through all adjacent vertices of u
            for (const auto& edge : graph.getAdjLists()[u]) {
                int v = edge.first; // Adjacent vertex
                int weight = edge.second; // Weight of the edge

                // If the adjacent vertex v is not in the MST and the weight of the edge is smaller than the current key
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight; // Update the key value for vertex v
                    minHeap.push({key[v], v}); // Add the vertex to the priority queue with the updated key
                    parent[v] = u; // Update the parent of vertex v
                }
            }
        }

        // Build the MST edge list from parent information
        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                mstEdges.emplace_back(parent[i], i); // Add edge to the MST
            }
        }

        return mstEdges; // Return the list of edges in the MST
    }
};

#endif // PRIM_H
