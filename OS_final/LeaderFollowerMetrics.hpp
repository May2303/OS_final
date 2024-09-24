#ifndef LEADERFOLLOWERMETRICS_HPP
#define LEADERFOLLOWERMETRICS_HPP

#include "Graph.hpp"
#include "MSTAlgorithms.hpp"
#include "MetricCalculator.hpp"
#include "MSTFactory.hpp"
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <iostream>

class LeaderFollowerMetrics {
public:
    LeaderFollowerMetrics(const Graph& graph, int numThreads = 4);

    // Retrieve the results after calculations are completed
    std::string getResults() const;

    // Destructor to join all threads
    ~LeaderFollowerMetrics();
    
    // New method for computing the MST
    void computeMST(const std::string& algoType);

private:
    std::vector<Edge> mstEdges;  // Store MST edge
    Graph graph;
    int totalWeight;
    int longestDist;
    double avgDist;
    int shortestDist;

    std::mutex mtx; // Mutex for task queue synchronization
    std::condition_variable cv;
    std::queue<std::function<void()>> tasks; // Task queue

    
    std::vector<std::thread> workers;  // Vector of worker threads
    bool stop;  // Flag to stop threads

    // Private methods to calculate various metrics
    void calculateTotalWeight();
    void calculateLongestDistance();
    void calculateAverageDistance();
    void calculateShortestDistance(int u, int v);

    // Worker thread function
    void workerThread();

    // Helper to enqueue tasks
    void enqueueTask(const std::function<void()>& task);

    

};

#endif // LEADERFOLLOWERMETRICS_HPP
