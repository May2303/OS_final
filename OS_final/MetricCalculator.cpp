#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <cassert>
#include "MSTAlgorithms.hpp"
#include <iostream>
#include <ostream>



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
        adj[e.u].push_back(e); // Add edge from u to v
        // For directed graphs, do not add the reverse edge
        // adj[e.v].push_back({e.u, e.weight}); // Add reverse edge if undirected
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

double averageDistance(const vector<vector<Edge>>& adj, int n) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));

    // Initialize distances for direct edges
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0; // Distance from a node to itself is zero
        for (const Edge& e : adj[i]) {
            dist[i][e.v] = e.weight; // Distance from node i to node e.v
        }
    }

    // Floyd-Warshall algorithm to compute all pairs shortest paths
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < numeric_limits<int>::max() && dist[k][j] < numeric_limits<int>::max()) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Calculate the average distance
    double totalDistance = 0;
    int count = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (dist[i][j] < numeric_limits<int>::max()) { // Only count reachable pairs
                totalDistance += dist[i][j];
                count++;
            }
        }
    }

    return count == 0 ? 0 : totalDistance / count;
}

// Calculate the shortest distance between two vertices in the MST
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

        if (visited[node]) continue;
        visited[node] = true;

        for (const Edge& e : adj[node]) {
            if (dist[node] + e.weight < dist[e.v]) {
                dist[e.v] = dist[node] + e.weight;
                pq.push({dist[e.v], e.v});
            }
        }
    }

    return dist[v];
}
