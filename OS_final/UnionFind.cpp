#include "UnionFind.hpp"

// Constructor initializes the parent and rank vectors
UnionFind::UnionFind(int size) : parent(size), rank(size, 0) {
    for (int i = 0; i < size; ++i) {
        parent[i] = i; // Each node is its own parent
    }
}

int UnionFind::find(int x) {
    if (parent[x] != x) {
        // Path compression heuristic
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        // Union by rank heuristic
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
