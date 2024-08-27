#ifndef METRIC_CALCULATOR_H
#define METRIC_CALCULATOR_H

#include "MST.hpp"

class MetricCalculator {
public:
    static double calculateTotalWeight(const MST& mst);
    static double calculateLongestDistance(const MST& mst);
    static double calculateAverageDistance(const MST& mst);
    static double calculateShortestDistance(const MST& mst);
};

#endif