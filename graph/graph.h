/*
 * Graph - ADT representation of a undirected graph
 *
 * Author: Sky King (skyking@gmail.com)
 *
 * Edges duplicated internally so an edge between v and w is
 * represented as both edge(v, w) and edge(w, v)
 * Loops are explicitly forbidden from being created
 *
 */

#ifndef _GRAPH_H
#define _GRAPH_H

/*
 * Graph - ADT representation of a undirected graph
 *
 * Edges duplicated internally so an edge between v and w is
 * represented as both edge(v, w) and edge(w, v)
 * Loops are explicitly forbidden from being created
 *
 */

#include <iostream>
#include <vector>
#include <ctime>

#include "edge.h"

using namespace std;

class Graph
{
public:

    // default constructor, creates and empty graph
    Graph();
    // generates a random graph of given density, with random weights between low and high
    Graph(int size, double density, double low, double high);
    // reads a graph from a file
    Graph(char* filename);
    // number of vertices
    int V();
    // number of edges
    int E();
    // adds an edge from x to y with the given weight
    void add(int x, int y, double weight);
    // deletes edge from x to y, in both directions
    void del(int x, int y);
    // Is there an edge from x to y?
    bool adjacent(int x, int y);
    // returns vector of vertices that are neighbors of x
    vector<int> neighbours(int x);

    // Get/Set node value not implemented for now.
    //void get_node_value(int x);
    //void set_node_value(intt x, char* a);

    // returns the cost/weight of the path from x to y
    double get_edge_value(int x, int y);
    // sets the cost/weight of the path from x to y
    void set_edge_value(int x, int y, double weight);

    ostream& operator<<(ostream& out);

    friend ostream& operator<<(ostream& out, Graph g)
    {
        out << "Graph has " << g.vCount_ << " vertices and " << g.eCount_
                << " edges\n";
        for (int i = 0; i < g.vCount_; i++)
        {
            out << "edge " << i << ": ";
            for (unsigned int j = 0; j < g.adjacencies_[i].size(); j++)
            {
                out << g.adjacencies_[i][j] << "  ";
            }
            out << "\n";
        }
        return out;
    }

private:
    int vCount_;                             // vertex count
    int eCount_;                             // edge count
    vector<vector<Edge> > adjacencies_;    // vector of edges from 0..N

};

#endif // _GRAPH_H
