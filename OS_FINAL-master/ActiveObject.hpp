// ActiveObject.hpp
#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <string>
#include <future>

class ActiveObject {
public:
    virtual void computeMST(const std::string& algorithmType) = 0;
    virtual std::string getResults() = 0;
    virtual ~ActiveObject() = default;
};

#endif // ACTIVEOBJECT_HPP
