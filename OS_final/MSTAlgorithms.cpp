#include "MSTAlgorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <algorithm> // For std::min, std::max

// Implementation of Prim's algorithm for MST
std::vector<Edge> PrimAlgorithm::play_mst(const Graph& graph) {
    return prim(graph); // Call the Prim's algorithm function defined elsewhere
}

// Implementation of Kruskal's algorithm for MST
std::vector<Edge> KruskalAlgorithm::play_mst(const Graph& graph) {
    // Call the kruskal function defined in kruskal.cpp to compute MST
    return kruskal(graph);
}
