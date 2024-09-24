
#include "ActiveObjectImpl.hpp"
#include <iostream>

ActiveObjectImpl::ActiveObjectImpl(Graph& graph) : pipeline(graph), stopThread(false) {
    worker = std::thread(&ActiveObjectImpl::processRequests, this);
}

void ActiveObjectImpl::computeMST(const std::string& algorithmType) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Request for MST algorithm " << algorithmType << " enqueued." << std::endl;
    requestQueue.push(algorithmType); // Add request to the queue
    cv.notify_one(); // Notify the worker thread
}


void ActiveObjectImpl::processRequests() {
    while (!stopThread) {
        std::string algorithmType;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !requestQueue.empty() || stopThread; });
            if (stopThread) return;
            algorithmType = requestQueue.front();
            requestQueue.pop();
            std::cout << "Processing request for MST algorithm: " << algorithmType << std::endl;
        }

        // Process the request through the pipeline
        pipeline.process(algorithmType);
        std::cout << "MST and metrics calculation for " << algorithmType << " completed." << std::endl;
    }
}

std::string ActiveObjectImpl::getResults() {
    std::lock_guard<std::mutex> lock(mtx);
    return pipeline.getResults(); // Get results from pipeline
}

// Destructor to join the thread
ActiveObjectImpl::~ActiveObjectImpl() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopThread = true;
    }
    cv.notify_one(); // Notify the worker thread to stop
    worker.join(); // Wait for the thread to finish
}
