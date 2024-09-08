#ifndef METRICCALCULATOR_HPP
#define METRICCALCULATOR_HPP

#include "graph.hpp"
#include "MST.hpp"

class MetricCalculator {
public:
    static int calculateTotalWeight(const MST& mst);
    static int calculateLongestDistance(const Graph& graph, const MST& mst);
    static double calculateAverageDistance(const Graph& graph);
    static int calculateShortestDistanceInMST(const Graph& graph, const MST& mst, int u, int v);
};

#endif // METRICCALCULATOR_HPP