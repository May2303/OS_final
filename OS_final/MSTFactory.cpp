#include "MSTFactory.hpp"
#include <memory>

// Define the createAlgorithm method
std::unique_ptr<MSTAlgorithm> MSTFactory::createAlgorithm(const std::string& type) {
    if (type == "Prim") {
        return std::make_unique<PrimAlgorithm>();
    } else if (type == "Kruskal") {
        return std::make_unique<KruskalAlgorithm>();
    }
    return nullptr;
}
