#include "Pipeline.hpp"

Pipeline::Pipeline(const Graph& graph) : graph(graph), totalWeight(0), longestDist(0), avgDist(0.0), shortestDist(0) {}

void Pipeline::process(const std::string& algorithmType) {
    // Step 1: Compute MST
    std::cout << "Stage 1: Computing MST using " << algorithmType << "..." << std::endl;
    computeMST(algorithmType);
    std::cout << "MST computation done." << std::endl;

    
    // Step 2: Calculate metrics in parallel
     std::cout << "Stage 2: Calculating metrics in parallel..." << std::endl;
    calculateMetrics();
    std::cout << "Metrics calculation completed." << std::endl;

    // Step 3: Return results
    // We can return results directly or store them for later retrieval
    std::string results = getResults();
    std::cout << "Stage 3: Results are ready for retrieval." << std::endl;

    std::cout << results; // or send this to the client
}

void Pipeline::computeMST(const std::string& algorithmType) {
    mstAlgorithm = MSTFactory::createAlgorithm(algorithmType);
    if (!mstAlgorithm) {
        throw std::runtime_error("Invalid MST algorithm type.");
    }

    std::cout << "Using " << algorithmType << " algorithm to compute MST..." << std::endl;
    auto mstPairs = mstAlgorithm->play_mst(graph);
    if (mstPairs.empty()) {
        throw std::runtime_error("MST computation failed.");
    }

    mstEdges.clear();
    for (const Edge& edge : mstPairs) {
        mstEdges.push_back({edge.u, edge.v, edge.weight});
    }
}


void Pipeline::calculateMetrics() {
    if (mstEdges.empty()) {
        throw std::runtime_error("No MST edges to calculate metrics.");
    }

    // Launch tasks to calculate metrics concurrently
    auto futureTotalWeight = std::async(std::launch::async, &Pipeline::calculateTotalWeight, this);
    auto futureLongestDistance = std::async(std::launch::async, &Pipeline::calculateLongestDistance, this);
    auto futureAverageDistance = std::async(std::launch::async, &Pipeline::calculateAverageDistance, this);
    
    // Example vertices for shortest distance calculation
    int u = 1, v = 2;
    auto futureShortestDistance = std::async(std::launch::async, &Pipeline::calculateShortestDistance, this, u, v);

    // Wait for all futures to complete
    futureTotalWeight.get();
    futureLongestDistance.get();
    futureAverageDistance.get();
    futureShortestDistance.get();
}


std::string Pipeline::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::stringstream ss;
    ss << "Total weight of MST: " << totalWeight << "\n";
    ss << "Longest distance in MST: " << longestDist << "\n";
    ss << "Average distance between vertices: " << avgDist << "\n";
    ss << "Shortest distance between vertices in MST: " << shortestDist << "\n";
    return ss.str();
}
// Implementations of metric calculation methods
void Pipeline::calculateTotalWeight() {
    int localTotalWeight = totalMSTWeight(mstEdges); // Calculate without locking
    std::lock_guard<std::mutex> lock(mtx);
    totalWeight = localTotalWeight; // Update shared state
}

void Pipeline::calculateLongestDistance() {
    int localLongestDist = longestDistance(mstEdges, graph.getNumVertices());
    std::lock_guard<std::mutex> lock(mtx);
    longestDist = localLongestDist;
}

void Pipeline::calculateAverageDistance() {
    double localAvgDist = averageDistance(graph.getAdjacencyList(), graph.getNumVertices());
    std::lock_guard<std::mutex> lock(mtx);
    avgDist = localAvgDist;
}

void Pipeline::calculateShortestDistance(int u, int v) {
    int localShortestDist = shortestMSTDistance(u, v, mstEdges, graph.getNumVertices());
    std::lock_guard<std::mutex> lock(mtx);
    shortestDist = localShortestDist;
}
