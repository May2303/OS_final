#ifndef MST_H
#define MST_H

#include "graph.hpp"

class MST {
public:
    virtual double getTotalWeight() = 0;
    virtual double getLongestDistance() = 0;
    virtual double getAverageDistance() = 0;
    virtual double getShortestDistance() = 0;
};

#endif