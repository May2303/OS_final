#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MSTAlgorithms.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <limits>
using namespace std;



TEST_CASE("Testing totalMSTWeight function") {
    // Test case 1: Empty MST
    vector<Edge> mst1;
    CHECK(totalMSTWeight(mst1) == 0);

    // Test case 2: Single edge in MST
    vector<Edge> mst2 = {{1, 2, 10}};
    CHECK(totalMSTWeight(mst2) == 10);

    // Test case 3: Multiple edges in MST
    vector<Edge> mst3 = {{1, 2, 5}, {2, 3, 10}, {3, 4, 20}};
    CHECK(totalMSTWeight(mst3) == 35);

    // Test case 4: Negative edge weights
    vector<Edge> mst4 = {{1, 2, -5}, {2, 3, 15}};
    CHECK(totalMSTWeight(mst4) == 10);

    // Test case 5: Zero weights
    vector<Edge> mst5 = {{1, 2, 0}, {2, 3, 0}, {3, 4, 0}};
    CHECK(totalMSTWeight(mst5) == 0);
}


TEST_CASE("Testing dfs function") {
    // Helper to create a test adjacency list
    vector<Edge> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 4, 4}};
    vector<vector<Edge>> adj = buildAdjacencyList(edges, 4);
    
    // Test case 1: DFS on a simple connected tree
    vector<int> dist(5, 0);
    vector<bool> visited(5, false);
    int farthestNode = 0, maxDist = 0;
    dfs(0, adj, visited, dist, farthestNode, maxDist);
    CHECK(farthestNode == 4);
    CHECK(maxDist == 10);

    // Test case 2: DFS on a graph from a different starting node
    fill(visited.begin(), visited.end(), false);
    fill(dist.begin(), dist.end(), 0);
    farthestNode = 0;
    maxDist = 0;
    dfs(2, adj, visited, dist, farthestNode, maxDist);
    CHECK(farthestNode == 4);
    CHECK(maxDist == 7);

    // Test case 3: DFS on a single node tree
    vector<vector<Edge>> adjSingle = {{}, {}};
    fill(visited.begin(), visited.end(), false);
    fill(dist.begin(), dist.end(), 0);
    farthestNode = 0;
    maxDist = 0;
    dfs(0, adjSingle, visited, dist, farthestNode, maxDist);
    CHECK(farthestNode == 0);
    CHECK(maxDist == 0);
}
TEST_CASE("Testing longestDistance function") {
    // Test case 1: Simple graph with one path
    vector<Edge> mst1 = {{1, 2, 10}, {2, 3, 20}};
    CHECK(longestDistance(mst1, 3) == 30);

    // Test case 2: Directed cycle
    vector<Edge> mst2 = {{1, 2, 5}, {2, 3, 10}, {3, 1, 15}};
    CHECK(longestDistance(mst2, 3) == 20); // Correct expected result

    // Test case 3: Directed acyclic graph (DAG) with longest path
    vector<Edge> mst3 = {{1, 2, 2}, {2, 3, 5}, {1, 3, 10}};
    CHECK(longestDistance(mst3, 3) == 10);

    // Test case 4: Non-connected graph
    vector<Edge> mst4 = {{1, 2, 5}};
    CHECK(longestDistance(mst4, 3) == 5);

    // Test case 5: Zero-weight edges
    vector<Edge> mst5 = {{1, 2, 0}, {2, 3, 0}};
    CHECK(longestDistance(mst5, 3) == 0);
}


vector<vector<Edge>> buildAdjacencyList(const vector<Edge>& mstEdges, int n);

TEST_CASE("Testing buildAdjacencyList function") {
    // Test case 1: Empty MST
    vector<Edge> mst1;
    vector<vector<Edge>> adj1 = buildAdjacencyList(mst1, 1); // 1 node
    CHECK(adj1.size() == 2); // 1 node + 1 index (0) = 2

    // Test case 2: Single edge
    vector<Edge> mst2 = {{1, 2, 10}};
    vector<vector<Edge>> adj2 = buildAdjacencyList(mst2, 2);
    CHECK(adj2[1].size() == 1);
    CHECK(adj2[2].size() == 0); // Directed graph, no reverse edge
    CHECK(adj2[1][0].v == 2);
    CHECK(adj2[1][0].weight == 10);

    // Test case 3: Multiple edges
    vector<Edge> mst3 = {{1, 2, 5}, {2, 3, 10}};
    vector<vector<Edge>> adj3 = buildAdjacencyList(mst3, 3);
    CHECK(adj3[1].size() == 1);
    CHECK(adj3[2].size() == 1);
    CHECK(adj3[3].size() == 0);
    
    CHECK(adj3[1][0].v == 2);
    CHECK(adj3[1][0].weight == 5);
    CHECK(adj3[2][0].v == 3);
    CHECK(adj3[2][0].weight == 10);

    // Test case 4: Non-connected vertices
    vector<Edge> mst4 = {{1, 2, 5}};
    vector<vector<Edge>> adj4 = buildAdjacencyList(mst4, 4); // 4 nodes
    CHECK(adj4[3].empty());
    CHECK(adj4[4].empty());

    // Test case 5: Zero-weight edges
    vector<Edge> mst5 = {{1, 2, 0}, {2, 3, 0}};
    vector<vector<Edge>> adj5 = buildAdjacencyList(mst5, 3);
    CHECK(adj5[1][0].weight == 0);
    CHECK(adj5[2][0].weight == 0);
    CHECK(adj5[1][0].v == 2);
    CHECK(adj5[2][0].v == 3);
}

TEST_CASE("Testing shortestMSTDistance function") {
    // Test case 1: Single edge
    vector<Edge> mst1 = {{1, 2, 10}};
    CHECK(shortestMSTDistance(1, 2, mst1, 2) == 10);

    // Test case 2: Line-shaped MST
    vector<Edge> mst2 = {{1, 2, 5}, {2, 3, 10}, {3, 4, 20}};
    CHECK(shortestMSTDistance(1, 4, mst2, 4) == 35);

    // Test case 3: Star-shaped MST
    vector<Edge> mst3 = {{1, 2, 1}, {1, 3, 1}, {1, 4, 1}};
    CHECK(shortestMSTDistance(2, 3, mst3, 4) == numeric_limits<int>::max());
    CHECK(shortestMSTDistance(1, 2, mst3, 4) == 1);

    // Test case 4: Non-connected vertices
    vector<Edge> mst4 = {{1, 2, 5}};
    CHECK(shortestMSTDistance(1, 3, mst4, 3) == numeric_limits<int>::max());

    // Test case 5: Negative-weight edges
    vector<Edge> mst5 = {{1, 2, -10}, {2, 3, -20}};
    CHECK(shortestMSTDistance(1, 3, mst5, 3) == -30);
}

TEST_CASE("Testing averageDistance function") {
    // Test case 1: Simple directed graph
    vector<Edge> edges1 = {{1, 2, 5}, {2, 3, 10}, {1, 3, 15}};
    vector<vector<Edge>> adj1 = buildAdjacencyList(edges1, 3);
    CHECK(averageDistance(adj1, 3) == doctest::Approx(10.0));

    // Test case 2: Graph with no paths (disconnected graph)
    vector<Edge> edges2 = {{1, 2, 5}};
    vector<vector<Edge>> adj2 = buildAdjacencyList(edges2, 3);
    CHECK(averageDistance(adj2, 3) == doctest::Approx(5.0)); // Only one path

    // Test case 3: Graph with zero-weight edges
    vector<Edge> edges3 = {{1, 2, 0}, {2, 3, 0}};
    vector<vector<Edge>> adj3 = buildAdjacencyList(edges3, 3);
    CHECK(averageDistance(adj3, 3) == doctest::Approx(0.0)); // All distances are zero

    // Test case 4: Graph with negative weights (not suitable for Floyd-Warshall)
    vector<Edge> edges4 = {{1, 2, -2}, {2, 3, -3}};
    vector<vector<Edge>> adj4 = buildAdjacencyList(edges4, 3);
    CHECK(averageDistance(adj4, 3) == doctest::Approx(-5.0/2)); // Negative weight scenario

    // Test case 5: Single node graph
    vector<Edge> edges5;
    vector<vector<Edge>> adj5 = buildAdjacencyList(edges5, 1);
    CHECK(averageDistance(adj5, 1) == 0.0); // No distances to calculate
}