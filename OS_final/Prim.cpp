#ifndef PRIM_H
#define PRIM_H

#include "MST.hpp"
#include <queue>
#include <vector>
#include <limits>

class Prim : public MST {
public:
    std::vector<std::pair<int, int>> calculateMST(const Graph& graph) const override {
        std::vector<std::pair<int, int>> mstEdges;
        int numVertices = graph.getNumVertices();
        std::vector<bool> inMST(numVertices, false);
        std::vector<int> parent(numVertices, -1);
        std::vector<int> key(numVertices, std::numeric_limits<int>::max());
        using pii = std::pair<int, int>; // Pair for (weight, vertex)

        auto cmp = [](const pii& a, const pii& b) { return a.first > b.first; };
        std::priority_queue<pii, std::vector<pii>, decltype(cmp)> minHeap(cmp);

        key[0] = 0;
        minHeap.push({0, 0}); // Start with vertex 0

        while (!minHeap.empty()) {
            int u = minHeap.top().second;
            minHeap.pop();

            inMST[u] = true;

            for (const auto& edge : graph.getAdjLists()[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    minHeap.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < numVertices; ++i) {
            if (parent[i] != -1) {
                mstEdges.emplace_back(parent[i], i);
            }
        }

        return mstEdges;
    }
};

#endif // PRIM_H
