/*
 * Edge - ADT representation of a weighted edge
 *
 * Author: Sky King (skyking@gmail.com)
 *
 */
#ifndef _EDGE_H
#define _EDGE_H

#include <iostream>

using namespace std;

/*
 * Edge class represents a connection between vertex v and w
 * with the given weight
 */
class Edge
{
public:

    Edge(int v, int w, double weight) :
            v_(v), w_(w), weight_(weight) { }

    // start edge
    int from() { return v_; }

    // end edge
    int to() { return w_; }

    // get cost from v to w
    double get_weight() { return weight_; }

    // set cost from v to w
    void set_weight(double weight) { weight_ = weight; }

    friend bool operator==(const Edge e1, const Edge e2) {
        return e1.weight_ == e2.weight_;
    }

    friend bool operator!=(const Edge e1, const Edge e2) {
        return !(e1.weight_ == e2.weight_);
    }

    friend bool operator<(const Edge e1, const Edge e2) {
        return e1.weight_ < e2.weight_;
    }

    friend bool operator<=(const Edge e1, const Edge e2) {
        return e1.weight_ <= e2.weight_;
    }

    friend bool operator>(const Edge e1, const Edge e2) {
        return e1.weight_ > e2.weight_;
    }

    friend bool operator>=(const Edge e1, const Edge e2) {
        return e1.weight_ >= e2.weight_;
    }

    // prints an edge
    friend ostream& operator<<(ostream& out, Edge e) {
        out << e.v_ << "->" << e.w_ << " (" << e.weight_ << ")";
        return out;
    }

private:
    int v_;         // start
    int w_;         // end
    double weight_;  // cost
};

struct EdgeComparator
{
    bool operator()(Edge& lhs, Edge& rhs) {
        return lhs.get_weight() > rhs.get_weight();
    }
};

#endif // _EDGE_H
