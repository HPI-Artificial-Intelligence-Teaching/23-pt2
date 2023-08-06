/******************************************************************************
 *
 *  An immutable weighted edge.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdexcept>
#include <limits>

using namespace std;

// Implements an immutable weighted edge
class Edge {
    int v;
    int w;
    double edge_weight;

   public:
    // constructor
    Edge(int _v=0, int _w=0, double _edge_weight=numeric_limits<double>::infinity()) : v(_v), w(_w), edge_weight(_edge_weight) {}

    // copy constructor
    Edge(const Edge& e) : v(e.v), w(e.w), edge_weight(e.edge_weight) {}

    // move constructor
    Edge(Edge&& e) : v(e.v), w(e.w), edge_weight(e.edge_weight) {}

    // copy assignment
    Edge& operator=(const Edge& e) {
        v = e.v;
        w = e.w;
        edge_weight = e.edge_weight;
        return (*this);
    }

    // move assignment
    Edge& operator=(Edge&& e) {
        v = e.v;
        w = e.w;
        edge_weight = e.edge_weight;
        return (*this);
    }

    // destructor
    ~Edge() {}

    // returns the weight of the edge
    double weight() const {
        return (edge_weight);
    }

    // returns the tail vertex of this edge
    int from() const {
        return (v);
    }

    // returns the head vertex of this edge
    int to() const {
        return (w);
    }

    // returns either endpoint of this edge
    int either() const {
        return (v);
    }

    // returns the endpoint of this edge that is different from the given vertex
    int other(const int vertex) const {
        if (vertex == v)
            return w;
        else if (vertex == w)
            return v;
        else
            throw logic_error("Illegal endpoint");
    }

    // compares two edges
    bool operator==(const Edge& e) { return (edge_weight == e.edge_weight); }
    bool operator!=(const Edge& e) { return (edge_weight != e.edge_weight); }
    bool operator<(const Edge& e) { return (edge_weight < e.edge_weight); }
    bool operator<=(const Edge& e) { return (edge_weight <= e.edge_weight); }
    bool operator>(const Edge& e) { return (edge_weight > e.edge_weight); }
    bool operator>=(const Edge& e) { return (edge_weight >= e.edge_weight); }
};

#endif