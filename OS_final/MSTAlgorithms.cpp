#include "MSTAlgorithms.hpp"
#include <vector>
#include <algorithm> // For std::min, std::max
#include <memory>


// Implementation of Prim's algorithm for MST
std::vector<std::pair<int, int>> PrimAlgorithm::play_mst(int n, const std::vector<std::vector<Edge>>& adj) {
    return prim(n, adj); // Call the Prim's algorithm function defined elsewhere
}

// Implementation of Kruskal's algorithm for MST
std::vector<std::pair<int, int>> KruskalAlgorithm::play_mst(int n, const std::vector<std::vector<Edge>>& adj) {
    std::vector<Edge> edgeList;

    // Convert adjacency list to a list of edges
    for (int i = 1; i <= n; ++i) {
        for (const Edge& e : adj[i]) {
            if (i < e.v) {
                edgeList.push_back({i, e.v, e.weight});
            }
        }
    }

    // play_mst MST using Kruskal's algorithm
    std::vector<Edge> mstEdges = kruskal(n, edgeList);

    // Convert edge list to a list of pairs for the result
    std::vector<std::pair<int, int>> mstPairs;
    for (const Edge& e : mstEdges) {
        mstPairs.emplace_back(e.u, e.v);
    }
    return mstPairs;
}