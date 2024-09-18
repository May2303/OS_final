#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <memory>
#include "Graph.hpp"
#include "MSTAlgorithms.hpp"
#include "MetricCalculator.cpp"
#include "MSTFactory.hpp"

class Pipeline {
public:
    Pipeline(const Graph& graph);
    
    // השלב הראשון: חישוב ה-MST
    void computeMST(const std::string& algorithmType);
    
    // השלב השני: חישוב המדדים
    void calculateMetrics();
    
    // שלב לוקח את התוצאה ומחזיר אותה
    std::string getResults() const;
    
private:
    Graph graph;
    std::unique_ptr<MSTAlgorithm> mstAlgorithm;
    std::vector<Edge> mstEdges;
    int totalWeight;
    int longestDist;
    double avgDist;
    int shortestDist;
    
    void updateMetrics();
};

#endif // PIPELINE_HPP
