#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <thread>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <mutex>
#include "MSTFactory.cpp"

using namespace std;

// Global variables (consider thread safety if using multiple threads)

int n = 0, m = 0; // Number of vertices and edges
vector<Edge> edges; // List of edges
vector<vector<Edge>> adj; // Adjacency list representation of the graph
mutex graphMutex; // Mutex for thread safety


void handleClient(int clientSocket) {
    char buffer[1024] = {0}; // Buffer to read client data
    string command; // Command from client

    while (true) {
        // Read data from the client
        int valread = read(clientSocket, buffer, 1024);
        if (valread <= 0) {
            // If no data is read or client disconnects, close the socket and return
            cout << "Client disconnected" << endl;
            close(clientSocket);
            return;
        }

        // Null-terminate the buffer to process as a string
        buffer[valread] = '\0';
        command = buffer;
        stringstream ss(command);
        ss >> command; // Extract the command from the stringstream

        if (command == "Newgraph") {
            // Handle initialization of a new graph
            lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
            ss >> n >> m; // Read the number of vertices and edges
            edges.clear(); // Clear the existing edge list
            adj.assign(n + 1, vector<Edge>()); // Resize adjacency list to hold n vertices
            cout << "New graph initialized with n = " << n << " and m = " << m << endl;

        } else if (command == "MST") {
            // Handle Minimum Spanning Tree computation
            string algoType;
            ss >> algoType; // Read the type of MST algorithm

            auto algo = MSTFactory::createAlgorithm(algoType); // Create the algorithm object
            if (!algo) {
                // If the algorithm type is invalid, send an error message
                string error = "Invalid MST algorithm\n";
                send(clientSocket, error.c_str(), error.length(), 0);
                continue; // Continue to handle next client request
            }

            vector<Edge> mstEdges;
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                mstEdges = kruskal(n, edges); // Compute the MST using Kruskal's algorithm
            }

            // Prepare and send the MST result to the client
            stringstream response;
            response << "mst:\n";
            for (const auto& edge : mstEdges) {
                response << edge.u << " " << edge.v << " " << edge.weight << "\n";
            }
            send(clientSocket, response.str().c_str(), response.str().length(), 0);

        } else if (command == "Newedge") {
            // Handle adding a new edge
            int u, v, w;
            ss >> u >> v >> w; // Read edge details
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                edges.push_back({u, v, w}); // Add edge to edge list
                adj[u].push_back({v, w}); // Add edge to adjacency list
                adj[v].push_back({u, w}); // For undirected graph, add edge in both directions
            }
            cout << "Added new edge: (" << u << ", " << v << ") with weight " << w << endl;

        } else if (command == "Removeedge") {
            // Handle removing an edge
            int u, v;
            ss >> u >> v; // Read edge details
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                // Remove edge from edge list
                edges.erase(remove_if(edges.begin(), edges.end(), [u, v](const Edge& e) {
                    return (e.u == u && e.v == v) || (e.u == v && e.v == u);
                }), edges.end());

                // Remove edge from adjacency list
                adj[u].erase(remove_if(adj[u].begin(), adj[u].end(), [v](const Edge& e) { return e.v == v; }), adj[u].end());
                adj[v].erase(remove_if(adj[v].begin(), adj[v].end(), [u](const Edge& e) { return e.u == u; }), adj[v].end());
            }
            cout << "Removed edge: (" << u << ", " << v << ")" << endl;

        } else if (command == "GetData") {
            // Handle GetData command to retrieve and send metrics
            vector<Edge> mstEdges;
            {
                lock_guard<mutex> lock(graphMutex); // Lock the mutex for thread safety
                mstEdges = kruskal(n, edges); // Compute the MST
            }

            // Compute metrics
            int totalWeight = totalMSTWeight(mstEdges);
            int longestDist = longestDistance(mstEdges, n);
            double avgDist = averageDistance(adj, n);
            // Choose specific vertices for distance calculation
            int u = 1, v = 2; // Example vertices; modify as needed
            int shortestDist = shortestMSTDistance(u, v, mstEdges, n);

            // Prepare and send the results to the client
            stringstream response;
            response << "Total weight of MST: " << totalWeight << "\n";
            response << "Longest distance in MST: " << longestDist << "\n";
            response << "Average distance between vertices: " << avgDist << "\n";
            response << "Shortest distance between vertices " << u << " and " << v << " in MST: " << shortestDist << "\n";

            send(clientSocket, response.str().c_str(), response.str().length(), 0);

        } else {
            // Handle invalid command
            string error = "Invalid command\n";
            send(clientSocket, error.c_str(), error.length(), 0);
        }
    }
}
