#include <iostream>
#include <vector>
#include <thread>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <mutex>
//#include "Graph.hpp" // Include the Graph class header
//#include "MSTFactory.hpp" // Ensure this header is properly defined
#include "ActiveObjectImpl.hpp"
#include "LeaderFollowerMetrics.hpp"
//#include "MetricCalculator.hpp"



using namespace std;

Graph* graph; // Pointer to the graph
mutex graphMutex; // Mutex for thread safety
std::unique_ptr<ActiveObject> activeObject; // Active Object instance
std::unique_ptr<LeaderFollowerMetrics> lfThreadPool; // Leader-Follower pool instance
bool usePipeline = true; // Default to using pipeline pattern

void handleClient(int clientSocket) {
    char buffer[1024] = {0}; // Buffer to read client data
    string command; // Command from client
     unique_ptr<MSTAlgorithm> algo; // Define algo here


    while (true) {
        // Read data from the client
        int valread = read(clientSocket, buffer, 1024);
        if (valread <= 0) {
            cout << "Client disconnected" << endl;
            close(clientSocket);
            return;
        }

        // Null-terminate the buffer to process as a string
        buffer[valread] = '\0';
        stringstream ss(buffer);
        ss >> command; // Extract the command from the stringstream

        if (command == "Newgraph") {
            // Handle initialization of a new graph
            int n, m; // Number of vertices and edges
            ss >> n >> m; // Read the number of vertices and edges

            lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety

            graph = new Graph(n); // Create a new graph
            cout << "New graph initialized with n = " << n << " and m = " << m << endl;

        } else if (command == "SetPattern") {
            std::string pattern;
            ss >> pattern;
            if (pattern == "Pipeline") {
                usePipeline = true;
                std::string response = "Using pipeline pattern.\n";
                send(clientSocket, response.c_str(), response.length(), 0);
            } else if (pattern == "LF") {
                usePipeline = false;
                std::string response = "Using Leader-Follower pattern.\n";
                send(clientSocket, response.c_str(), response.length(), 0);
            }

        // } else if (command == "MST") {
        //     // Handle Minimum Spanning Tree computation
        //     string algoType;
        //     ss >> algoType; // Read the type of MST algorithm

        //     // Use the factory to create the algorithm object
        //     algo = MSTFactory::createAlgorithm(algoType);
        //     if (!algo) {
        //         string error = "Invalid MST algorithm\n";
        //         send(clientSocket, error.c_str(), error.length(), 0);
        //         continue; // Continue to handle next client request
        //     }

        //     vector<Edge> mstEdges;
        //     {
        //         lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
        //         mstEdges = algo->play_mst(*graph);
        //     }

        //     // Prepare and send the MST result to the client
        //     stringstream response;
        //     response << "mst:\n";
        //     for (const auto& edge : mstEdges) {
        //         response << edge.u << " " << edge.v << " " << edge.weight << "\n";
        //     }
        //     send(clientSocket, response.str().c_str(), response.str().length(), 0);

        // } 
        } else if (command == "MST") {
            // Handle Minimum Spanning Tree computation
            std::string algoType;
            ss >> algoType; // Read the type of MST algorithm

            // Use the factory to create the algorithm object
            algo = MSTFactory::createAlgorithm(algoType);
            if (!algo) {
                std::string error = "Invalid MST algorithm\n";
                send(clientSocket, error.c_str(), error.length(), 0);
                continue; // Continue to handle the next client request
            }

            if (usePipeline) { 

                activeObject = std::make_unique<ActiveObjectImpl>(*graph);
                // Check if activeObject is initialized
                if (!activeObject) {
                    std::string error = "ActiveObject is not initialized.\n";
                    send(clientSocket, error.c_str(), error.length(), 0);
                    continue; // Handle next request
                }
               

                // Use the pipeline active object to queue MST computation
                activeObject->computeMST(algoType); // Queue the request in pipeline
                std::string response = "MST request is being processed using the Pipeline.\n";
                send(clientSocket, response.c_str(), response.length(), 0);

            } else {
                lfThreadPool= std::make_unique<LeaderFollowerMetrics>(*graph);
                if (!lfThreadPool) {
                    std::cerr << "Error: LF Thread Pool not initialized" << std::endl;
                    return;
                }

                // Use the Leader-Follower thread pool to compute the MST
                lfThreadPool->computeMST(algoType); // Handle the request in the LF thread pool
                std::string response = "MST request is being processed using Leader-Follower.\n";
                send(clientSocket, response.c_str(), response.length(), 0);
            }
        }else if (command == "Newedge") {
            // Handle adding a new edge
            int u, v, w;
            ss >> u >> v >> w; // Read edge details
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                graph->addEdge(u, v, w); // Add edge to graph
            }
            cout << "Added new edge: (" << u << ", " << v << ") with weight " << w << endl;

        } else if (command == "Removeedge") {
            // Handle removing an edge
            int u, v;
            ss >> u >> v; // Read edge details
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                graph->removeEdge(u, v); // Remove edge from graph
            }
            cout << "Removed edge: (" << u << ", " << v << ")" << endl;

        } else if (command == "GetResults") {
            std::string results;
            if (usePipeline) {
                results = activeObject->getResults(); // Get results from Active Object
            } else {
                results = lfThreadPool->getResults(); // Get results from Leader-Follower
            }
            send(clientSocket, results.c_str(), results.length(), 0);
            
        
        } else {
            // Handle invalid command
            string error = "Invalid command\n";
            send(clientSocket, error.c_str(), error.length(), 0);
        }
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        return -1;
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET; // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Any address
    serverAddr.sin_port = htons(8080); // Port number

    // Bind the socket to the address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed" << endl;
        return -1;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, 3) < 0) {
        cerr << "Listen failed" << endl;
        return -1;
    }

    cout << "Server listening on port 8080..." << endl;

    while (true) {
        // Accept a new client connection
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            cerr << "Accept failed" << endl;
            continue;
        }

        cout << "New client connected" << endl;

        // Spawn a new thread to handle the client
        thread(handleClient, clientSocket).detach();
    }

    // Cleanup
    close(serverSocket);
    return 0;
}
