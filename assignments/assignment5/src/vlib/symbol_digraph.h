/******************************************************************************
 *
 * A directed graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __SYMBOL_DIGRAPH_H__
#define __SYMBOL_DIGRAPH_H__

#include <string>

#include "digraph.h"
#include "redblack_bst.h"

using namespace std;

// Implements a class representing a directed graph, where the vertex names are arbitrary strings
class SymbolDigraph {
    RedBlackBST<string, int>* st;  // string -> index
    string* keys;                  // index  -> string
    Digraph* graph;                // the underlying graph

   public:
    // constructor
    SymbolDigraph(const string&, const char);

    // copy constructor
    SymbolDigraph(const SymbolDigraph& sdg) {
        st = new RedBlackBST<string, int>(*sdg.st);
        graph = new Digraph(*sdg.graph);
        keys = new string[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = sdg.keys[v];
    }

    // move constructor
    SymbolDigraph(SymbolDigraph&& sdg) : st(sdg.st),
                                         keys(sdg.keys),
                                         graph(sdg.graph) {
        sdg.st = nullptr;
        sdg.keys = nullptr;
        sdg.graph = nullptr;
    }

    // copy assignment
    SymbolDigraph& operator=(const SymbolDigraph& sdg) {
        // free the existing lists, map and graph
        delete st;
        delete[] keys;
        delete graph;

        // copy the symbol graph passed in
        st = new RedBlackBST<string, int>(*sdg.st);
        graph = new Digraph(*sdg.graph);
        keys = new string[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = sdg.keys[v];
        return (*this);
    }

    // move assignment
    SymbolDigraph& operator=(SymbolDigraph&& sdg) {
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
    ~SymbolDigraph() {
        delete st;
        delete[] keys;
        delete graph;
    }

    // returns whether or not the graph contain the vertex named s
    bool contains(const string& s) const { return (st->contains(s)); }

    // returns the integer associated with the vertex named s
    int index_of(const string& s) const { return (*(st->get(s))); }

    // returns the name of the vertex associated with the integer
    string name_of(const int v) const { return (keys[v]); }

    // returns the associated graph
    const Digraph* get_graph() const { return (graph); }
};

#endif