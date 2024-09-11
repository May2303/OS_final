#include <memory>
#include <vector>
#include <string>
#include "MSTAlgorithms.hpp"

using namespace std;

// Define Edge structure (assumed to be defined elsewhere in your code)
struct Edge {
    int u, v, weight;
};

// Abstract base class for MST algorithms
class MSTAlgorithm {
public:
    // Pure virtual function to compute the MST
    // Subclasses must implement this function
    virtual vector<pair<int, int>> compute(int n, const vector<vector<Edge>>& adj) = 0;
};



// Implementation of Prim's algorithm for MST
class PrimAlgorithm : public MSTAlgorithm {
public:
    // Override the compute method to use Prim's algorithm
    vector<pair<int, int>> compute(int n, const vector<vector<Edge>>& adj) override {
        return prim(n, adj); // Call the Prim's algorithm function (assumed to be defined elsewhere)
    }
};



// Implementation of Kruskal's algorithm for MST
class KruskalAlgorithm : public MSTAlgorithm {
public:
    // Override the compute method to use Kruskal's algorithm
    vector<pair<int, int>> compute(int n, const vector<vector<Edge>>& adj) override {
        vector<Edge> edgeList;

        // Convert adjacency list to a list of edges
        for (int i = 1; i <= n; ++i) {
            for (const Edge& e : adj[i]) {
                // Ensure each edge is added only once by checking i < e.to
                if (i < e.v) {
                    edgeList.push_back({i, e.v, e.weight});
                }
            }
        }

        // Compute MST using Kruskal's algorithm
        vector<Edge> mstEdges = kruskal(n, edgeList); // Call Kruskal's algorithm function (assumed to be defined elsewhere)

        // Convert edge list to a list of pairs for the result
        vector<pair<int, int>> mstPairs;
        for (const Edge& e : mstEdges) {
            mstPairs.emplace_back(e.u, e.v);
        }
        return mstPairs;
    }
};



// Factory class to create MST algorithm objects
class MSTFactory {
public:
    // Static method to create an MST algorithm instance based on the given type
    static unique_ptr<MSTAlgorithm> createAlgorithm(const string& type) {
        if (type == "Prim") {
            return make_unique<PrimAlgorithm>(); // Return a unique_ptr to a PrimAlgorithm instance
        } else if (type == "Kruskal") {
            return make_unique<KruskalAlgorithm>(); // Return a unique_ptr to a KruskalAlgorithm instance
        }
        return nullptr; // Return nullptr if the type is invalid
    }
};
