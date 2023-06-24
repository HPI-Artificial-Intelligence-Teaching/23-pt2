/******************************************************************************
 *
 * A graph, implemented using an array of sets. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#include "graph.h"

// copys adjacency lists
Bag<int>* Graph::copy_adj_lists(const Graph& g) const {
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
Graph::Graph(ifstream& ifs) : no_edges(0) {
    // read the number of vertices
    if (!(ifs >> no_vertices))
        throw runtime_error("Number of vertices expected");

    // read the number of edges
    int E;
    if (!(ifs >> E))
        throw runtime_error("Number of edges expected");

    adj_lists = new Bag<int>[no_vertices];

    // read the edges
    for (auto i = 0; i < E; i++) {
        int v, w;
        if (!(ifs >> v) || !(ifs >> w))
            throw runtime_error("Two vertex indicies expected");
        add_edge(v, w);
    }
}

// adds an edge to the undirected graph
void Graph::add_edge(const int v, const int w) {
    validate_vertex(v);
    validate_vertex(w);
    no_edges++;
    adj_lists[v].add(w);
    adj_lists[w].add(v);
    return;
}

// implementation of the stream output for Graphs
ostream& operator<<(ostream& out, const Graph& g) {
    out << g.V() << " vertices, " << g.E() << " edges" << endl;
    for (auto v = 0; v < g.V(); v++) {
        out << v << ": ";
        for (auto w : g.adj(v)) out << w << " ";
        out << endl;
    }
    return (out);
}
