#ifndef MSTFACTORY_HPP
#define MSTFACTORY_HPP

#include <memory>
#include <string>
#include "MSTAlgorithms.hpp" // Include the header where MSTAlgorithm and derived classes are declared

class MSTFactory {
public:
    // Static method to create an MST algorithm instance based on the given type
    static std::unique_ptr<MSTAlgorithm> createAlgorithm(const std::string& type);
};

#endif // MSTFACTORY_HPP

