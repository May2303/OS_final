#ifndef MST_H
#define MST_H

#include "graph.hpp"
#include <vector>

class MST {
public:
    virtual ~MST() = default;
    virtual std::vector<std::pair<int, int>> calculateMST(const Graph& graph) const = 0;
};

#endif // MST_H
