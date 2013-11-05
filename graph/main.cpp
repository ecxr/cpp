/*
 * Main: test suite and monte carlo simulator for a weighted undirectional graph
 *
 * Author: Sky King (skyking@gmail.com)
 *
 */

#include <iostream>
#include <unistd.h>
#include <queue>
#include <vector>
#include <fstream>

#include "edge.h"
#include "graph.h"
#include "util.h"
#include "heap.cpp"

using namespace std;

// Test function for testing the Edge ADT
void test_edges()
{
    Edge e1 = Edge(0, 1, 1);
    Edge e2 = Edge(0, 2, 2);
    Edge e3 = Edge(1, 0, 1);
    Edge e4 = Edge(1, 2, 3);
    Edge e5 = Edge(2, 0, 2);
    Edge e6 = Edge(2, 1, 3);

    vector<vector<Edge> > edges(3);
    edges[0].push_back(e1);
    edges[0].push_back(e2);
    edges[1].push_back(e3);
    edges[1].push_back(e4);
    edges[2].push_back(e5);
    edges[2].push_back(e6);

    for (unsigned int i = 0; i < edges.size(); ++i)
    {
        for (unsigned int j = 0; j < edges[i].size(); ++j)
        {
            cout << edges[i][j] << endl;
        }
    }
}

// Test function for testing the graph ADT
void test_graph()
{
    Graph g = Graph();
    for (int i = 0; i < 6; i++)
    {
        g.add(i, i * 3 % 2, (double) i * 7 / 3);
    }

    cout << g;
    cout << "Deleting edge from 3 to 1" << endl;
    g.del(3, 1);
    cout << g;

    cout << "neighbors of edge 0 are: ";

    vector<int> n = g.neighbours(0);
    for (int i : n)
    {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < g.V(); i++)
    {
        for (int j = 0; j < g.V(); j++)
        {
            cout << g.adjacent(i, j) << " ";
        }
        cout << endl;
    }
}

void test_heap()
{
    Edge e1 = Edge(0, 1, 1);
    Edge e2 = Edge(0, 2, 2);
    Edge e3 = Edge(1, 0, 1);
    Edge e4 = Edge(1, 2, 3);
    Edge e5 = Edge(2, 0, 2);
    Edge e6 = Edge(2, 1, 3);
    Edge values[6] = {e1,e2,e3,e4,e5,e6};

    priority_queue<Edge, std::vector<Edge>, EdgeComparator> pq;

    for (int i = 0; i < 6; i++) {
      cout << "inserting " << values[i] << "\n";
      pq.push(values[i]);
    }

    while (!pq.empty())
    {
      cout << "extracted " << pq.top() << "\n";
      pq.pop();
    }
}
/*
void test_heap2()
{
    MinHeap<Edge> h;
    Edge e1 = Edge(0, 1, 1);
    Edge e2 = Edge(0, 2, 2);
    Edge e3 = Edge(1, 0, 1);
    Edge e4 = Edge(1, 2, 3);
    Edge e5 = Edge(2, 0, 2);
    Edge e6 = Edge(2, 1, 3);
    Edge values[6] = {e1,e2,e3,e4,e5,e6};

    for (int i = 0; i < 6; i++) {
      cout << "inserting " << values[i] << "\n";
      h.insert(values[i]);
      cout << h;
    }

    for (int i = 0; i < 6; i++) {
      cout << "extracted " << h.getMin() << "\n" << h;
    }
}
*/

void test_file()
{
    ifstream infile("mst_data.txt");
    int size, u, v, weight;

    infile >> size;
    cout << "size: size" << endl;
    while (infile >> u >> v >> weight)
    {
        cout << u << "->" << v << " (" << weight << ")" << endl;
    }
}

// Runs a monte carlo simulation, for nTests, creating a random graph with the given nodes and density, each
// edge with a cost between costLow and costHigh
void monte_carlo(int nTests, int nodes, double density, double costLow,
        double costHigh)
{
    srand(time(0));
    double total_edges = 0.0;
    for (int i = 0; i < nTests; ++i)
    {
        Graph g(nodes, density, costLow, costHigh);
        //cout << "Graph: " << i << " Nodes: " << g.V() << " Edges: " << g.E()
        //        << endl;
        total_edges += g.E();
    }

    cout << "Average number of edges for a graph with " << nodes << " nodes and a density of " <<
            density << " is " << static_cast<double>(total_edges / nTests) << endl;
}

// Main entry point
// Runs a few tests and then launches monte carlo simulations
int main(void)
{
    test_edges();
    test_graph();
    test_heap();
    test_file();
    //test_heap2();

    cout    << "10 tests of 50 nodes with density of 20% with weight between 1.0 and 10.0"
            << endl;
    monte_carlo(10, 50, 0.20, 1.0, 10.0);

    cout << endl;

    cout    << "10 tests of 50 nodes with density of 40% with weight between 1.0 and 10.0"
            << endl;
    monte_carlo(10, 50, 0.40, 1.0, 10.0);

    return 0;
}
