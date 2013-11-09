#include <vector>
#include "edge.h"

using namespace std;

class MST {
  public: 
    MST(double costIn, vector<Edge> treeIn) {
      cost = costIn;
      tree = treeIn;
    }

    double cost;
    vector<Edge> tree;
    
    friend ostream& operator<< (ostream& out, MST m) {
      out << "Minimum spanning tree of cost " << m.cost << ":\n";
      for (int i = 0; i < m.tree.size(); i++) {
        out << m.tree[i] << endl;
      }
      return out;
    }
};

#ifdef TESTMST
int main() {
  vector<Edge> bar;
  for (int i = 0; i < 4; i++) {
    Edge e(i, i, (double)i + 0.3);
    bar.push_back(e);
  }
  MST foo(43.0, bar);
  cout << foo;
}
#endif
