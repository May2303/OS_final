#ifndef MST_FACTORY_H
#define MST_FACTORY_H

#include "MST.hpp"

class MSTFactory {
public:
    static MST* createMST(const Graph& graph, std::string algorithm);
};

#endif