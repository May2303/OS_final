// ActiveObjectImpl.hpp
#ifndef ACTIVEOBJECTIMPL_HPP
#define ACTIVEOBJECTIMPL_HPP

#include "ActiveObject.hpp"
#include "Pipeline.hpp" 
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

// Concrete implementation of the ActiveObject abstract class
class ActiveObjectImpl : public ActiveObject {
public:
    // Constructor that takes a Graph reference
    ActiveObjectImpl(Graph& graph);

    // Override the computeMST function from ActiveObject
    void computeMST(const std::string& algorithmType) override;

    // Override the getResults function from ActiveObject
    std::string getResults() override;

    // Virtual destructor for proper cleanup of derived class
    virtual ~ActiveObjectImpl();  

private:
    // Function to handle requests in a separate thread
    void processRequests(); 

    // Queue to hold requests for processing
    std::queue<std::string> requestQueue; 

    // Mutex for ensuring thread-safe access to shared data
    std::mutex mtx; 

    // Condition variable to synchronize between threads
    std::condition_variable cv; 

    // Pipeline object for processing tasks
    Pipeline pipeline; 

    // Flag to signal when to stop the worker thread
    bool stopThread; 

    // Worker thread for processing requests
    std::thread worker; 
};

#endif // ACTIVEOBJECTIMPL_HPP
