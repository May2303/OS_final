#include "MSTAlgorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <algorithm> // For std::min, std::max

// Implementation of Prim's algorithm for MST
std::vector<std::pair<int, int>> PrimAlgorithm::play_mst(const Graph& graph) {
    return prim(graph); // Call the Prim's algorithm function defined elsewhere
}

// Implementation of Kruskal's algorithm for MST
std::vector<std::pair<int, int>> KruskalAlgorithm::play_mst(const Graph& graph) {
    std::vector<Edge> edgeList;

    // Convert adjacency list to a list of edges
    auto adj = graph.getAdjacencyList();
    int n = graph.getNumVertices();
    
    for (int i = 1; i <= n; ++i) {
        for (const Edge& e : adj[i]) {
            if (i < e.v) { // Ensure each edge is added only once
                edgeList.push_back({i, e.v, e.weight});
            }
        }
    }

    // Compute the MST using Kruskal's algorithm
    std::vector<Edge> mstEdges = kruskal(graph);

    // Convert edge list to a list of pairs for the result
    std::vector<std::pair<int, int>> mstPairs;
    for (const Edge& e : mstEdges) {
        mstPairs.emplace_back(e.u, e.v);
    }
    return mstPairs;
}

// Implementation of Prim's algorithm
std::vector<std::pair<int, int>> prim(const Graph& graph) {
    int n = graph.getNumVertices();
    auto adj = graph.getAdjacencyList();
    // Your Prim's algorithm implementation
}

// Implementation of Kruskal's algorithm
std::vector<Edge> kruskal(const Graph& graph) {
    int n = graph.getNumVertices();
    auto adj = graph.getAdjacencyList();
    std::vector<Edge> edges;

    // Convert adjacency list to a list of edges
    for (int i = 1; i <= n; ++i) {
        for (const Edge& e : adj[i]) {
            if (i < e.v) {
                edges.push_back({i, e.v, e.weight});
            }
        }
    }

    // Your Kruskal's algorithm implementation
    return edges;
}
