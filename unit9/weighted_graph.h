/******************************************************************************
 *
 * An edge-weighted undirected graph, implemented using adjacency lists. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

#include <fstream>
#include <iostream>

#include "bag.h"
#include "edge.h"
#include "stack.h"

using namespace std;

// Implements a class representing an undirected edge-weighted graph of vertices named 0 through V-1
class EdgeWeightedGraph {
    int no_vertices;       // number of vertices
    int no_edges;          // number of edges
    Bag<Edge>* adj_lists;  // array of adjacency lists

    // copys adjacency lists
    Bag<Edge>* copy_adj_lists(const EdgeWeightedGraph&) const;

   public:
    // constructor
    EdgeWeightedGraph(const int V) : no_vertices(V),
                                     no_edges(0) {
        if (V < 0) throw logic_error("Number of vertices must be non-negative");
        adj_lists = new Bag<Edge>[V];
    }

    // file I/O constructor
    EdgeWeightedGraph(ifstream&);

    // copy constructor
    EdgeWeightedGraph(const EdgeWeightedGraph& g) : no_vertices(g.no_vertices),
                                                    no_edges(g.no_edges) {
        adj_lists = copy_adj_lists(g);
    }

    // move constructor
    EdgeWeightedGraph(EdgeWeightedGraph&& g) : no_vertices(g.no_vertices),
                                               no_edges(g.no_edges),
                                               adj_lists(g.adj_lists) {
        g.no_vertices = 0;
        g.no_edges = 0;
        g.adj_lists = nullptr;
    }

    // copy assignment
    EdgeWeightedGraph& operator=(const EdgeWeightedGraph& g) {
        // free the existing adjacency lists
        delete[] adj_lists;
        // copy the graph passed in
        no_vertices = g.no_vertices;
        no_edges = g.no_edges;
        adj_lists = copy_adj_lists(g);
        return (*this);
    }

    // move assignment
    EdgeWeightedGraph& operator=(EdgeWeightedGraph&& g) {
        // free the existing adjacency lists
        delete[] adj_lists;

        no_vertices = g.no_vertices;
        no_edges = g.no_edges;
        adj_lists = g.adj_lists;
        g.no_vertices = 0;
        g.no_edges = 0;
        g.adj_lists = nullptr;
        return (*this);
    }

    // destructor
    ~EdgeWeightedGraph() {
        delete[] adj_lists;
    }

    // returns the number of vertices
    int V() const { return (no_vertices); }

    // returns the number of edges
    int E() const { return (no_edges); }

    // validates a vertex index
    void validate_vertex(const int v) const {
        if (v < 0 || v >= no_vertices)
            throw logic_error("Vertex index out of range");
    }

    // adds an edge to the undirected graph
    void add_edge(const Edge&);

    // out-degree of a vertex
    int degree(const int v) const {
        validate_vertex(v);
        return (adj_lists[v].size());
    }

    // return the iterator over the adjacency-list for a vertex
    Bag<Edge>& adj(const int v) const {
        validate_vertex(v);
        return (adj_lists[v]);
    }
};

extern ostream& operator<<(ostream&, const EdgeWeightedGraph&);

#endif
