#include "LeaderFollowerMetrics.hpp"
#include <sstream>
#include <limits>
#include <vector>
LeaderFollowerMetrics::LeaderFollowerMetrics(const Graph& graph, int numThreads)
    : graph(graph), stop(false), totalWeight(0), longestDist(0), avgDist(0), shortestDist(0) 
{
    // Start worker threads without computing the MST
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(&LeaderFollowerMetrics::workerThread, this);
    }
}


void LeaderFollowerMetrics::enqueueTask(const std::function<void()>& task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(task);
    }
    cv.notify_one();  // Notify one waiting thread
}

void LeaderFollowerMetrics::computeMST(const std::string& algoType) {
    // Log the start of the MST computation
    std::cout << "Leader-Follower: Starting MST computation using " << algoType << std::endl;

    // Create an MST algorithm instance using the factory
    std::unique_ptr<MSTAlgorithm> algo = MSTFactory::createAlgorithm(algoType);
    if (!algo) {
        std::cerr << "Invalid MST algorithm type: " << algoType << std::endl;
        return;
    }

    {
        // Lock the graph to ensure thread-safety during MST calculation
        //std::cout << "Leader-Follower: Locking the graph for MST computation." << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        mstEdges = algo->play_mst(graph);  // Compute the MST
        std::cout << "Leader-Follower: MST computation completed." << std::endl;
    }

    // Once the MST is computed, enqueue metric calculations
    std::cout << "Leader-Follower: Enqueuing metric calculations." << std::endl;
    enqueueTask([this]() { 
        std::cout << "Leader-Follower: Calculating total MST weight." << std::endl;
        calculateTotalWeight(); 
        std::cout << "Leader-Follower: Total weight calculation completed." << std::endl;
    });
    enqueueTask([this]() { 
        std::cout << "Leader-Follower: Calculating longest distance in MST." << std::endl;
        calculateLongestDistance(); 
        std::cout << "Leader-Follower: Longest distance calculation completed." << std::endl;
    });
    enqueueTask([this]() { 
        std::cout << "Leader-Follower: Calculating average distance in MST." << std::endl;
        calculateAverageDistance(); 
        std::cout << "Leader-Follower: Average distance calculation completed." << std::endl;
    });
    enqueueTask([this]() { 
        std::cout << "Leader-Follower: Calculating shortest distance in MST." << std::endl;
        calculateShortestDistance(1, 2);  // Example shortest distance
        std::cout << "Leader-Follower: Shortest distance calculation completed." << std::endl;
    });

    std::cout << "Leader-Follower: All tasks have been enqueued." << std::endl;
}



void LeaderFollowerMetrics::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !tasks.empty() || stop; });

            if (stop && tasks.empty()) return;  // Stop thread when no tasks
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();  // Execute the task
    }
}


void LeaderFollowerMetrics::calculateTotalWeight() {
    totalWeight = totalMSTWeight(mstEdges);
}

void LeaderFollowerMetrics::calculateLongestDistance() {
    longestDist = longestDistance(mstEdges, graph.getNumVertices());
}

void LeaderFollowerMetrics::calculateAverageDistance() {
    avgDist = averageDistance(mstEdges, graph.getNumVertices());
}

void LeaderFollowerMetrics::calculateShortestDistance(int u, int v) {
    shortestDist = shortestMSTDistance(u, v, mstEdges, graph.getNumVertices());
}

std::string LeaderFollowerMetrics::getResults() const {
    std::stringstream ss;

    // Print the MST edges
    ss << "MST Edges:\n";
    for (const auto& edge : mstEdges) {
        ss << "Edge from " << edge.u << " to " << edge.v << " with weight " << edge.weight << "\n";
    }

    ss << "Total weight of MST: " << totalWeight << "\n";
    ss << "Longest distance in MST: " << longestDist << "\n";
    ss << "Average distance between vertices: " << avgDist << "\n";
    ss << "Shortest distance between vertices in MST: " << shortestDist << "\n";
    return ss.str();
}

LeaderFollowerMetrics::~LeaderFollowerMetrics() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();  // Wake up all threads to exit
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

