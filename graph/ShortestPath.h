/*
 * ShortestPath ADT: Implements Djikstra's algorithm to find the shortest path
 * between two nodes in a graph
 *
 * Author: Sky King (skyking@gmail.com)
 *
 *
 */

#include <vector>

#include "graph"

using namespace std;

class ShortestPath
{
    // list of vertices in G(V,E)
    vector<int> vertices(Graph g, vector<int> v);
    // find shortest path between u-w and returns the sequence of vertices
    // representing shorest path u-v1-v2-…-vn-w.
    vector<int> path(Graph g, int u, int w);
    // return the path cost associated with the shortest path.
    float path_size(int u, int w);
};
