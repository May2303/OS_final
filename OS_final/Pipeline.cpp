#include "Pipeline.hpp"

Pipeline::Pipeline(const Graph& graph) : graph(graph), totalWeight(0), longestDist(0), avgDist(0.0), shortestDist(0) {}

void Pipeline::computeMST(const std::string& algorithmType) {
    mstAlgorithm = MSTFactory::createAlgorithm(algorithmType);
    if (mstAlgorithm) {
        auto mstPairs = mstAlgorithm->play_mst(graph);
        // Convert pairs to edges
        mstEdges.clear();
        for (const auto& pair : mstPairs) {
            mstEdges.push_back({pair.first, pair.second, 0}); // Assuming weight will be updated later
        }
    }
}

void Pipeline::calculateMetrics() {
    if (mstEdges.empty()) {
        return;
    }
    
    totalWeight = totalMSTWeight(mstEdges);
    longestDist = longestDistance(mstEdges, graph.getNumVertices());
    avgDist = averageDistance(graph.getAdjacencyList(), graph.getNumVertices());
    
    // Example vertices for shortest distance calculation
    int u = 1, v = 2;
    shortestDist = shortestMSTDistance(u, v, mstEdges, graph.getNumVertices());
}
/*
std::string Pipeline::getResults() const {
    std::stringstream ss;
    ss << "Total weight of MST: " << totalWeight << "\n";
    ss << "Longest distance in MST: " << longestDist << "\n";
    ss << "Average distance between vertices: " << avgDist << "\n";
    ss << "Shortest distance between vertices in MST: " << shortestDist << "\n";
    return ss.str();
}
*/

void Pipeline::updateMetrics() {
    // Update metrics based on the MST edges
    calculateMetrics();
}
