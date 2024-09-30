// ActiveObjectImpl.hpp
#ifndef ACTIVEOBJECTIMPL_HPP
#define ACTIVEOBJECTIMPL_HPP

#include "ActiveObject.hpp"
#include "Pipeline.hpp" // Include your Pipeline class
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class ActiveObjectImpl : public ActiveObject {
public:
    ActiveObjectImpl(Graph& graph);
    void computeMST(const std::string& algorithmType) override;
    std::string getResults() override;
     virtual ~ActiveObjectImpl();  

private:
    void processRequests(); // To handle requests in a separate thread
    std::queue<std::string> requestQueue; // To queue requests
    std::mutex mtx;
    std::condition_variable cv;
    Pipeline pipeline; // Assuming Pipeline is implemented
    bool stopThread;
    std::thread worker; // Worker thread
};

#endif // ACTIVEOBJECTIMPL_HPP
