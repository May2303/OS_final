#ifndef MSTALGORITHMS_H
#define MSTALGORITHMS_H

#include <vector>
#include <memory>
#include "Graph.hpp"


// Abstract base class for MST algorithms
class MSTAlgorithm {
public:
    virtual ~MSTAlgorithm() = default; // Virtual destructor for proper cleanup
    virtual std::vector<Edge> play_mst(const Graph& graph) = 0;
};

// Implementation of Prim's algorithm for MST
class PrimAlgorithm : public MSTAlgorithm {
public:
    std::vector<Edge> play_mst(const Graph& graph) override;
};

// Implementation of Kruskal's algorithm for MST
class KruskalAlgorithm : public MSTAlgorithm {
public:
    std::vector<Edge> play_mst(const Graph& graph) override;
};

// Function declarations for MST algorithms
std::vector<Edge> prim(const Graph& graph);
std::vector<Edge> kruskal(const Graph& graph);

#endif // MSTALGORITHMS_H