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

#include <iostream>
#include <fstream>
#include <queue>
#include "edge.h"
#include "graph.h"
#include "util.h"
#include "ufind.cpp"
#include "heap.cpp"

using namespace std;
//typedef pair<double, vector<Edge> > MST;

// default constructor, creates an empty graph
Graph::Graph()
{
    vCount_ = 0;
    eCount_ = 0;
}

// generates a random graph of given density, with random weights between low and high
Graph::Graph(int size, double density, double low, double high)
{
    vCount_ = 0;
    eCount_ = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (prob() < density)
            {
                double weight = low + (prob() * (high - low));
                add(i, j, weight);
            }
        }
    }
}

// reads a graph from a file
Graph::Graph(char* filename) {
  vCount_ = 0;
  eCount_ = 0;
  ifstream file(filename);
  int size, u, v;
  double weight;
  file >> size;
  while (file >>u >>v >>weight) { 
    add(u,v,weight);
  }
}
// number of vertices
int Graph::V()
{
    return vCount_;
}

// number of edges
int Graph::E()
{
    return eCount_;
}

// adds an edge from x to y with the given weight
// also addes a symmetric edge from y to x
void Graph::add(int x, int y, double weight)
{
    if (x == y)
        // ignore self-loops
        return;

    Edge e(x, y, weight);
    int m = max(x, y);
    if (m >= vCount_)
    {
        adjacencies_.resize(m + 1);
        vCount_ = m + 1;
    }
    adjacencies_[x].push_back(e);
    adjacencies_[y].push_back(e);
    // edges are counted once though they stored in each direction
    eCount_++;
}

// deletes edge from x to y, in both directions
void Graph::del(int x, int y)
{
    for (unsigned int i = 0; i < adjacencies_[x].size(); ++i)
    {
        if (adjacencies_[x][i].from() == y || adjacencies_[x][i].to() == y)
        {
            adjacencies_[x].erase(adjacencies_[x].begin() + i);
            eCount_--;
        }
    }
    for (unsigned int i = 0; i < adjacencies_[y].size(); ++i)
    {
        if (adjacencies_[y][i].from() == x || adjacencies_[y][i].to() == x)
        {
            adjacencies_[y].erase(adjacencies_[y].begin() + i);
        }
    }
}

// Is there an edge from x to y?
bool Graph::adjacent(int x, int y)
{
    if (x == y)
        return false;
    for (unsigned int i = 0; i < adjacencies_[x].size(); i++)
    {
        if (adjacencies_[x][i].from() == y || adjacencies_[x][i].to() == y)
            return true;
    }
    return false;
}

MST Graph::mst() 
{
  vector<Edge> tree;
  double cost = 0;
  priority_queue<Edge, std::vector<Edge>, EdgeComparator> edges;
  ufind components(vCount_);

  for (int i = 0; i < vCount_; i++) {
    vector<Edge> v = adjacencies_[i];
    for (int j = 0; j < v.size(); j++) {
      edges.push(v[j]);
    }
  }


  // assumes graph is connected - will attempt to pop empty vector
  // otherwise
  while (tree.size() < vCount_ - 1) {
    Edge next = edges.top(); edges.pop();
    while (components.sameGroup(next.to(), next.from())) {
      next = edges.top(); edges.pop();
    }

    tree.push_back(next);
    components.merge(next.to(), next.from());
    cost += next.get_weight();
  }

  MST foo(cost, tree);
  return foo;
}

// returns vector of vertices that are neighbors of x
vector<int> Graph::neighbours(int x)
{
    vector<int> v;
    for (unsigned int i = 0; i < adjacencies_[x].size(); i++)
    {
        Edge e = adjacencies_[x][i];
        int other = e.from() == x ? e.to() : e.from();
        v.push_back(other);
    }
    return v;
}


// returns the cost/weight of the path from x to y
// returns the first of the 2 paths it finds (x to y or y to x)
double Graph::get_edge_value(int x, int y)
{
    for (unsigned int i = 0; i < adjacencies_[x].size(); ++i)
    {
        if ((adjacencies_[x][i].from() == x && adjacencies_[x][i].to() == y) ||
            (adjacencies_[x][i].from() == y && adjacencies_[x][i].to() == x))
        {
            return adjacencies_[x][i].get_weight();
        }
    }

    // edge not found, return negative value since all edge costs are assumed positive
    return -1;
}

// sets the cost/weight of the path from x to y
// sets the cost of both x to y and y to x
void Graph::set_edge_value(int x, int y, double weight)
{
    // update x -> y
    for (unsigned int i = 0; i < adjacencies_[x].size(); ++i)
    {
        if ((adjacencies_[x][i].from() == x && adjacencies_[x][i].to() == y) ||
            (adjacencies_[x][i].from() == y && adjacencies_[x][i].to() == x))
        {
            adjacencies_[x][i].set_weight(weight);
        }
    }

    // update y -> x
    for (unsigned int i = 0; i < adjacencies_[y].size(); ++i)
    {
        if ((adjacencies_[y][i].from() == x && adjacencies_[y][i].to() == y) ||
            (adjacencies_[y][i].from() == y && adjacencies_[y][i].to() == x))
        {
            adjacencies_[y][i].set_weight(weight);
        }
    }
}

