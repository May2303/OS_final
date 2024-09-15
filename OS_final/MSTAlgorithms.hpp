#ifndef MSTALGORITHMS_H
#define MSTALGORITHMS_H

#include <vector>
#include <memory>
using namespace std;



// Define the Edge structure
struct Edge {
    int u, v, weight;
};


// Abstract base class for MST algorithms
class MSTAlgorithm {
public:
    virtual ~MSTAlgorithm() = default; // Virtual destructor for proper cleanup
    virtual std::vector<std::pair<int, int>> play_mst(int n, const std::vector<std::vector<Edge>>& adj) = 0;
};


// Implementation of Prim's algorithm for MST
class PrimAlgorithm : public MSTAlgorithm {
public:
    std::vector<std::pair<int, int>> play_mst(int n, const std::vector<std::vector<Edge>>& adj) override;
};


// Implementation of Kruskal's algorithm for MST
class KruskalAlgorithm : public MSTAlgorithm {
public:
    std::vector<std::pair<int, int>> play_mst(int n, const std::vector<std::vector<Edge>>& adj) override;
};


// Function declarations for MST algorithms
std::vector<std::pair<int, int>> prim(int n, const std::vector<std::vector<Edge>>& adj);
std::vector<Edge> kruskal(int n, std::vector<Edge>& edges);


// New function declarations
int totalMSTWeight(const std::vector<Edge>& mstEdges);
int longestDistance(const std::vector<Edge>& mstEdges, int n);
double averageDistance(const std::vector<std::vector<Edge>>& adj, int n);
int shortestMSTDistance(int u, int v, const std::vector<Edge>& mstEdges, int n);
vector<vector<Edge>> buildAdjacencyList(const vector<Edge>& mstEdges, int n);
void dfs(int node, const vector<vector<Edge>>& adj, vector<bool>& visited, vector<int>& dist, int& farthestNode, int& maxDist);

#endif // MSTALGORITHMS_H