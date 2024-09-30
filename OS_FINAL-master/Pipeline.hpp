#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <memory>
#include <sstream>
#include "Graph.hpp"
#include "MSTAlgorithms.hpp"
#include "MetricCalculator.hpp"
#include "MSTFactory.hpp"
#include <future>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>



class Pipeline {
public:
    Pipeline(const Graph& graph);
    
    // Stage for computing the MST
    void computeMST(const std::string& algorithmType);
    
    // Stage for calculating metrics
    void calculateMetrics();
    
    // Get results as a string
    std::string getResults() const;

    void process(const std::string& algorithmType);

private:
    Graph graph;
    std::unique_ptr<MSTAlgorithm> mstAlgorithm;
    std::vector<Edge> mstEdges;
    int totalWeight;
    int longestDist;
    double avgDist;
    int shortestDist;

     // Mutex for thread safety
    mutable std::mutex mtx;

    void calculateTotalWeight();
    void calculateLongestDistance();
    void calculateAverageDistance();
    void calculateShortestDistance(int u, int v);
        
    //void updateMetrics();
};

#endif // PIPELINE_HPP
