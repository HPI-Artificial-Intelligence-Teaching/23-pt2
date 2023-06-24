/******************************************************************************
 *
 * Computes the strongly-connected components of a digraph using the Kosaraju-Sharir algorithm
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __SCC_H__
#define __SCC_H__

#include <stdexcept>

#include "dfo.h"
#include "digraph.h"

// Implements a class that computes the strongly-connected components of a digraph using the Kosaraju-Sharir algorithm
class KosarajuSharirSCC {
    int no_vertices;    // total number of vertices
    int* cc_id;         // id[v] = id of strong component containing v
    int no_components;  // number of connected components

    // run DFS in digraph dg from vertex v
    void dfs(const Digraph& dg, const int v, bool* marked) {
        marked[v] = true;
        cc_id[v] = no_components;
        for (auto w : dg.adj(v)) {
            if (!marked[w]) {
                dfs(dg, w, marked);
            }
        }
        return;
    }

   public:
    // constructor
    KosarajuSharirSCC(const Digraph& dg) : no_vertices(dg.V()),
                                           no_components(0) {
        // initialize the marked and cc_id array
        bool* marked = new bool[no_vertices];  // marked[v] = has v been marked in dfs?
        cc_id = new int[no_vertices];
        for (auto v = 0; v < no_vertices; v++) {
            marked[v] = false;
            cc_id[v] = -1;
        }

        // run depth-first search recursively in the topological order of the reverse graph
        DepthFirstOrder dfo(dg.reverse());
        for (auto v : dfo.reverse_order()) {
            if (!marked[v]) {
                dfs(dg, v, marked);
                no_components++;
            }
        }

        // release the marked array
        delete[] marked;
    }

    // copy constructor
    KosarajuSharirSCC(const KosarajuSharirSCC& scc) : no_vertices(scc.no_vertices),
                                                      no_components(scc.no_components) {
        // allocated the cc_id array
        cc_id = new int[no_vertices];

        // copy the cc_id and cc_size array
        for (auto i = 0; i < no_vertices; i++) {
            cc_id[i] = scc.cc_id[i];
        }
    }

    // move constructor
    KosarajuSharirSCC(KosarajuSharirSCC&& scc) : no_vertices(scc.no_vertices),
                                                 no_components(scc.no_components),
                                                 cc_id(scc.cc_id) {
        scc.no_vertices = 0;
        scc.no_components = 0;
        scc.cc_id = nullptr;
    }

    // copy assignment
    KosarajuSharirSCC& operator=(const KosarajuSharirSCC& scc) {
        // free the existing cc_id list
        delete[] cc_id;

        // copy the DFS result list passed in
        no_vertices = scc.no_vertices;
        no_components = scc.no_components;

        cc_id = new int[no_vertices];

        for (auto i = 0; i < no_vertices; i++) {
            cc_id[i] = scc.cc_id[i];
        }

        return (*this);
    }

    // move assignment
    KosarajuSharirSCC& operator=(KosarajuSharirSCC&& scc) {
        // free the existing cc_id list
        delete[] cc_id;

        // copy the pointers
        no_vertices = scc.no_vertices;
        no_components = scc.no_components;

        cc_id = scc.cc_id;

        // release the pointers for the no-longer valid object
        scc.no_vertices = 0;
        scc.no_components = 0;
        scc.cc_id = nullptr;

        return (*this);
    }

    // destructor
    ~KosarajuSharirSCC() {
        delete[] cc_id;
    }

    // returns the component id of the connected component containing vertex v
    int id(const int v) const {
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (cc_id[v]);
    }

    // returns true if vertices v and w are in the same connected component
    bool connected(const int v, const int w) const {
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        if (w < 0 || w >= no_vertices) throw logic_error("Vertex index out of range");
        return (cc_id[v] == cc_id[w]);
    }

    // returns the number of strongly connected components in the graph
    int count() const { return (no_components); }
};

#endif