#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

class UnionFind {
public:
    UnionFind(int size);
    
    // Finds the root of the set containing element x
    int find(int x);

    // Unites the sets containing elements x and y
    void unionSets(int x, int y);

private:
    std::vector<int> parent; // parent[i] is the parent of node i
    std::vector<int> rank;   // rank[i] is the rank of the tree rooted at i
};

#endif // UNIONFIND_H
