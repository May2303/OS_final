#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <cassert>
#include "MetricCalculator.hpp"
#include <iostream>
#include <ostream>

#include <string>  

using namespace std;

// Calculate the total weight of the MST
int totalMSTWeight(const vector<Edge>& mstEdges) {
    int totalWeight = 0;
    for (const Edge& e : mstEdges) {
        totalWeight += e.weight;
    }
    return totalWeight;
}

vector<vector<Edge>> buildAdjacencyList(const vector<Edge>& mstEdges, int n) {
    vector<vector<Edge>> adj(n + 1); // +1 because nodes are 1-indexed
    for (const Edge& e : mstEdges) {
        adj[e.u].push_back(e);           // Add edge from u to v
        adj[e.v].push_back({e.v, e.u, e.weight}); // Add reverse edge for undirected graph
    }
    return adj;
}



// Helper function to perform DFS and find the longest path
void dfs(int node, const vector<vector<Edge>>& adj, vector<bool>& visited, vector<int>& dist, int& farthestNode, int& maxDist) {
    visited[node] = true;
    for (const Edge& e : adj[node]) {
        if (!visited[e.v]) {
            dist[e.v] = dist[node] + e.weight;
            if (dist[e.v] > maxDist) {
                maxDist = dist[e.v];
                farthestNode = e.v;
            }
            dfs(e.v, adj, visited, dist, farthestNode, maxDist);
        }
    }
}

int longestDistance(const vector<Edge>& mstEdges, int n) {
    vector<vector<Edge>> adj = buildAdjacencyList(mstEdges, n);
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, 0);
    int farthestNode = 1; // Start from node 1
    int maxDist = 0;

    // Find the farthest node from node 1
    dfs(1, adj, visited, dist, farthestNode, maxDist);

    // Reset visited and dist arrays
    fill(visited.begin(), visited.end(), false);
    fill(dist.begin(), dist.end(), 0);

    // Find longest distance from the previously found farthest node
    maxDist = 0;
    dfs(farthestNode, adj, visited, dist, farthestNode, maxDist);

    return maxDist;
}

double averageDistance(const vector<Edge>& adj, int n) {
    double totalDistance = 0;
    int count = 0;

    // Calculate the shortest distance between every pair of vertices (i, j) where i < j
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int shortestDist = shortestMSTDistance(i, j, adj, n);  // Directly use adj (MST edge list)
            if (shortestDist < numeric_limits<int>::max()) {
                totalDistance += shortestDist;
                count++;
            }
        }
    }

    return count == 0 ? 0 : totalDistance / count;
}



int shortestMSTDistance(int u, int v, const vector<Edge>& mstEdges, int n) {
    vector<vector<Edge>> adj = buildAdjacencyList(mstEdges, n);
    
    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<bool> visited(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        // If this node has been visited, skip processing
        if (visited[node]) continue;
        visited[node] = true;

        // Process each adjacent edge
        for (const Edge& e : adj[node]) {
            // Only consider the edge if the target node hasn't been visited
            if (!visited[e.v] && dist[node] + e.weight < dist[e.v]) {
                dist[e.v] = dist[node] + e.weight;
                pq.push({dist[e.v], e.v});
            }
        }
    }

    // Return the shortest distance or max int if unreachable
    return dist[v] == numeric_limits<int>::max() ? -1 : dist[v];
}
