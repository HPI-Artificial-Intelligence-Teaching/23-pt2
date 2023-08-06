/******************************************************************************
 *
 * An edge-weighted digraph, implemented using adjacency lists. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#include "weighted_digraph.h"

// copys adjacency lists
Bag<Edge>* EdgeWeightedDigraph::copy_adj_lists(const EdgeWeightedDigraph& dg) const {
    Bag<Edge>* adj_lists = new Bag<Edge>[no_vertices];

    for (auto v = 0; v < dg.no_vertices; v++) {
        // reverse so that adjacency list is in same order as original
        Stack<Edge> reverse;
        for (auto& w : dg.adj_lists[v]) {
            reverse.push(w);
        }
        while (!reverse.is_empty()) {
            adj_lists[v].add(reverse.pop());
        }
    }
    return (adj_lists);
}

// file I/O constructor
EdgeWeightedDigraph::EdgeWeightedDigraph(ifstream& ifs) : no_edges(0) {
    // read the number of vertices
    if (!(ifs >> no_vertices))
        throw runtime_error("Number of vertices expected");

    // read the number of edges
    int E;
    if (!(ifs >> E))
        throw runtime_error("Number of edges expected");

    adj_lists = new Bag<Edge>[no_vertices];
    in_degree = new int[no_vertices];
    for (auto v = 0; v < no_vertices; v++) {
        in_degree[v] = 0;
    }

    // read the edges
    for (auto i = 0; i < E; i++) {
        int v, w;
        double weight;
        if (!(ifs >> v) || !(ifs >> w) || !(ifs >> weight))
            throw runtime_error("Two vertex indicies expected");
        add_edge(Edge(v, w, weight));
    }
}

// adds an edge to the undirected graph
void EdgeWeightedDigraph::add_edge(const Edge& e) {
    int v = e.from();
    int w = e.to();
    validate_vertex(v);
    validate_vertex(w);
    no_edges++;
    adj_lists[v].add(e);
    in_degree[w]++;
    return;
}

// implementation of the stream output for Graphs
ostream& operator<<(ostream& out, const EdgeWeightedDigraph& dg) {
    out << dg.V() << " " << dg.E() << endl;
    for (auto v = 0; v < dg.V(); v++) {
        out << v << ": ";
        for (auto& e : dg.adj(v)) {
            out << e.from() << "->" << e.to() << " " << fixed << setprecision(5) << e.weight() << "  ";
        }
        out << endl;
    }
    return (out);
}