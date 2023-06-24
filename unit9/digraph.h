/******************************************************************************
 *
 * A directed graph, implemented using an array of sets. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <fstream>
#include <iostream>

#include "bag.h"
#include "stack.h"

using namespace std;

// Implements a class representing a directed graph of vertices named 0 through V-1
class Digraph {
    int no_vertices;      // number of vertices
    int no_edges;         // number of edges
    Bag<int>* adj_lists;  // array of adjacency lists
    int* in_degree;       // indegree[v] = indegree of vertex v

    // copys adjacency lists
    Bag<int>* copy_adj_lists(const Digraph&) const;

   public:
    // constructor
    Digraph(const int V) : no_vertices(V),
                           no_edges(0) {
        if (V < 0) throw logic_error("Number of vertices must be non-negative");
        adj_lists = new Bag<int>[V];
        in_degree = new int[V];
        for (auto v = 0; v < V; v++) {
            in_degree[v] = 0;
        }
    }

    // file I/O constructor
    Digraph(ifstream&);

    // copy constructor
    Digraph(const Digraph& dg) : no_vertices(dg.no_vertices),
                                 no_edges(dg.no_edges) {
        in_degree = new int[no_vertices];
        for (auto v = 0; v < no_vertices; v++) {
            in_degree[v] = dg.in_degree[v];
        }
        adj_lists = copy_adj_lists(dg);
    }

    // move constructor
    Digraph(Digraph&& dg) : no_vertices(dg.no_vertices),
                            no_edges(dg.no_edges),
                            adj_lists(dg.adj_lists),
                            in_degree(dg.in_degree) {
        dg.no_vertices = 0;
        dg.no_edges = 0;
        dg.adj_lists = nullptr;
        dg.in_degree = nullptr;
    }

    // copy assignment
    Digraph& operator=(const Digraph& dg) {
        // free the existing adjacency and in_degree lists
        delete[] adj_lists;
        delete[] in_degree;

        // copy the digraph passed in
        no_vertices = dg.no_vertices;
        no_edges = dg.no_edges;
        in_degree = new int[no_vertices];
        for (auto v = 0; v < no_vertices; v++) {
            in_degree[v] = dg.in_degree[v];
        }
        adj_lists = copy_adj_lists(dg);

        return (*this);
    }

    // move assignment
    Digraph& operator=(Digraph&& dg) {
        // free the existing adjacency and in_degree lists
        delete[] adj_lists;
        delete[] in_degree;

        no_vertices = dg.no_vertices;
        no_edges = dg.no_edges;
        adj_lists = dg.adj_lists;
        in_degree = dg.in_degree;

        dg.no_vertices = 0;
        dg.no_edges = 0;
        dg.adj_lists = nullptr;
        dg.in_degree = nullptr;

        return (*this);
    }

    // destructor
    ~Digraph() {
        delete[] adj_lists;
        delete[] in_degree;
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

    // adds the directed edge v->w to the directed graph
    void add_edge(const int, const int);

    // returns the reverse of the digraph
    Digraph reverse() const;

    // out-degree of a vertex
    int outdegree(const int v) const {
        validate_vertex(v);
        return (adj_lists[v].size());
    }

    // in-degree of a vertex
    int indegree(const int v) const {
        validate_vertex(v);
        return (in_degree[v]);
    }

    // return the iterator over the adjacency-list for a vertex
    const Bag<int>& adj(const int v) const {
        validate_vertex(v);
        return (adj_lists[v]);
    }
};

extern ostream& operator<<(ostream&, const Digraph&);

#endif
