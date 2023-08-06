/******************************************************************************
 *
 * A directed graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at
 *https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __STRUCT_DIGRAPH_H__
#define __STRUCT_DIGRAPH_H__

#include <string>

#include "vlib/edge.h"
#include "vlib/redblack_bst.h"
#include "vlib/weighted_digraph.h"

using namespace std;

// Implements a class representing a directed graph, where the vertex names are
// arbitrary strings
template <typename Node>
class WeightedStructDigraph {
    RedBlackBST<Node, int>* st;  // struct -> index
    Node* keys;                  // index  -> struct
    EdgeWeightedDigraph* graph;  // the underlying graph

   public:
    // vertex array constructor
    template <size_t N>
    WeightedStructDigraph(const Node (&nodes)[N]) {
        st = new RedBlackBST<Node, int>();
        for (auto i = 0; i < N; i++) {
            st->put(nodes[i], i);
        }
        keys = new Node[N];
        for (auto i = 0; i < N; i++) {
            keys[i] = nodes[i];
        }
        graph = new EdgeWeightedDigraph(N);
    };

    // vector constructor
    WeightedStructDigraph(const Bag<Node>& nodes) {
        st = new RedBlackBST<Node, int>();
        int c = 0;
        keys = new Node[nodes.size()];
        for (auto node : nodes) {
            st->put(node, c);
            keys[c] = node;
            c += 1;
        }
        graph = new EdgeWeightedDigraph(nodes.size());
    };

    // copy constructor
    WeightedStructDigraph(const WeightedStructDigraph& sdg) {
        st = new RedBlackBST<Node, int>(*sdg.st);
        graph = new EdgeWeightedDigraph(*sdg.graph);
        keys = new string[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = sdg.keys[v];
    }

    // move constructor
    WeightedStructDigraph(WeightedStructDigraph&& sdg)
        : st(sdg.st), keys(sdg.keys), graph(sdg.graph) {
        sdg.st = nullptr;
        sdg.keys = nullptr;
        sdg.graph = nullptr;
    }

    // copy assignment
    WeightedStructDigraph& operator=(const WeightedStructDigraph& sdg) {
        // free the existing lists, map and graph
        delete st;
        delete[] keys;
        delete graph;

        // copy the symbol graph passed in
        st = new RedBlackBST<Node, int>(*sdg.st);
        graph = new EdgeWeightedDigraph(*sdg.graph);
        keys = new string[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = sdg.keys[v];
        return (*this);
    }

    // move assignment
    WeightedStructDigraph& operator=(WeightedStructDigraph&& sdg) {
        // free the existing lists, map and graph
        delete st;
        delete[] keys;
        delete graph;

        st = sdg.st;
        keys = sdg.keys;
        graph = sdg.graph;
        sdg.st = nullptr;
        sdg.keys = nullptr;
        sdg.graph = nullptr;
        return (*this);
    }

    // destructor
    ~WeightedStructDigraph() {
        delete st;
        delete[] keys;
        delete graph;
    }

    // returns whether or not the graph contain the vertex named s
    bool contains(const Node& s) const { return (st->contains(s)); }

    // returns the integer associated with the vertex named s
    int index_of(const Node& s) const { return (*(st->get(s))); }

    // returns the name of the vertex associated with the integer
    Node name_of(const int v) const { return (keys[v]); }

    // returns the associated graph
    EdgeWeightedDigraph* get_graph() const { return graph; }

    // add_edge
    void add_edge(const Node& s, const Node& t, const float weight) {
        graph->add_edge(Edge(index_of(s), index_of(t), weight));
    }
};

#endif
