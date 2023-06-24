/******************************************************************************
 *
 * A directed graph, implemented using an array of sets. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#include "digraph.h"

// copys adjacency lists
Bag<int>* Digraph::copy_adj_lists(const Digraph& g) const {
    Bag<int>* adj_lists = new Bag<int>[no_vertices];

    for (auto v = 0; v < g.no_vertices; v++) {
        // reverse so that adjacency list is in same order as original
        Stack<int> reverse;
        for (auto w : g.adj_lists[v]) {
            reverse.push(w);
        }
        while (!reverse.is_empty()) {
            adj_lists[v].add(reverse.pop());
        }
    }
    return (adj_lists);
}

// file I/O constructor
Digraph::Digraph(ifstream& ifs) : no_edges(0) {
    // read the number of vertices
    if (!(ifs >> no_vertices))
        throw runtime_error("Number of vertices expected");

    // read the number of edges
    int E;
    if (!(ifs >> E))
        throw runtime_error("Number of edges expected");

    adj_lists = new Bag<int>[no_vertices];
    in_degree = new int[no_vertices];
    for (auto v = 0; v < no_vertices; v++) {
        in_degree[v] = 0;
    }

    // read the edges
    for (auto i = 0; i < E; i++) {
        int v, w;
        if (!(ifs >> v) || !(ifs >> w))
            throw runtime_error("Two vertex indicies expected");
        add_edge(v, w);
    }
}

// adds the directed edge v->w to the directed graph
void Digraph::add_edge(const int v, const int w) {
    validate_vertex(v);
    validate_vertex(w);
    adj_lists[v].add(w);
    in_degree[w]++;
    no_edges++;
    return;
}

// returns the reverse of the digraph
Digraph Digraph::reverse() const {
    Digraph rev(no_vertices);
    for (auto v = 0; v < no_vertices; v++) {
        for (auto w : adj(v)) {
            rev.add_edge(w, v);
        }
    }
    return (rev);
}

// implementation of the stream output for digraphs
ostream& operator<<(ostream& out, const Digraph& dg) {
    out << dg.V() << " vertices, " << dg.E() << " edges" << endl;
    for (auto v = 0; v < dg.V(); v++) {
        out << v << ": ";
        for (auto w : dg.adj(v)) out << w << " ";
        out << endl;
    }
    return (out);
}