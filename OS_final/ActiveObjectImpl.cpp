
#include "ActiveObjectImpl.hpp"
#include <iostream>

// Constructor for ActiveObjectImpl, initializing the pipeline and starting the worker thread
ActiveObjectImpl::ActiveObjectImpl(Graph& graph) :
    pipeline(graph),          // Initialize the pipeline with the provided graph
    stopThread(false) {       // Set stopThread to false initially
    worker = std::thread(&ActiveObjectImpl::processRequests, this); // Start the worker thread
}

// Method to compute the Minimum Spanning Tree (MST) using the specified algorithm
void ActiveObjectImpl::computeMST(const std::string& algorithmType) {
    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex for thread-safe access
    std::cout << "Request for MST algorithm " << algorithmType << " enqueued." << std::endl;
    requestQueue.push(algorithmType); // Add request to the queue
    cv.notify_one(); // Notify the worker thread that a new request is available
}

// Method that processes requests from the queue
void ActiveObjectImpl::processRequests() {
    while (!stopThread) { // Keep processing until stopThread is true
        std::string algorithmType;
        {
            std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
            // Wait until there is a request or the thread is signaled to stop
            cv.wait(lock, [this] { return !requestQueue.empty() || stopThread; });
            if (stopThread) return; // Exit if signaled to stop
            algorithmType = requestQueue.front(); // Get the next request
            requestQueue.pop(); // Remove the request from the queue
            std::cout << "Processing request for MST algorithm: " << algorithmType << std::endl;
        }

        // Process the request through the pipeline
        pipeline.process(algorithmType);
        std::cout << "MST and metrics calculation for " << algorithmType << " completed." << std::endl;
    }
}

// Method to retrieve results from the pipeline
std::string ActiveObjectImpl::getResults() {
    std::lock_guard<std::mutex> lock(mtx); // Lock the mutex for thread-safe access
    return pipeline.getResults(); // Get results from the pipeline
}

// Destructor to clean up resources
ActiveObjectImpl::~ActiveObjectImpl() {
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        stopThread = true; // Set the stop flag to true
    }
    cv.notify_one(); // Notify the worker thread to stop
    worker.join(); // Wait for the worker thread to finish