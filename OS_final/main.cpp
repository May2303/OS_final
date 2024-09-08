#include "graph.hpp"
#include "MSTFactory.cpp"
#include <iostream>

int main() {
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    std::cout << "Graph:\n";
    graph.printGraph();

    std::unique_ptr<MST> mst = MSTFactory::createMST(MSTAlgorithm::KRUSKAL);
    std::vector<std::pair<int, int>> mstEdges = mst->calculateMST(graph);

    std::cout << "MST Edges (Kruskal):\n";
    for (const auto& edge : mstEdges) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }

    return 0;
}
