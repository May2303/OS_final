#ifndef MST_FACTORY_H
#define MST_FACTORY_H

#include "MST.hpp"
#include "Prim.cpp"
#include "Kruskal.cpp"

enum class MSTAlgorithm {
    PRIM,
    KRUSKAL
};

class MSTFactory {
public:
    static std::unique_ptr<MST> createMST(MSTAlgorithm algo) {
        switch (algo) {
            case MSTAlgorithm::PRIM:
                return std::make_unique<Prim>();
            case MSTAlgorithm::KRUSKAL:
                return std::make_unique<Kruskal>();
            default:
                throw std::invalid_argument("Unknown MST algorithm");
        }
    }
};

#endif // MST_FACTORY_H
