/******************************************************************************
 *
 * A depth first search on an undirected graph that computes connected components.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __CC_H__
#define __CC_H__

#include <stdexcept>

#include "graph.h"

// Implements a class determining the connected components in an undirected graph
class CC {
    int no_vertices;    // total number of vertices
    int* cc_id;         // cc_id[v] = cc_id of connected component containing v
    int* cc_size;       // cc_size[cc_id] = number of vertices in given component
    int no_components;  // number of connected components

    // depth first search from v
    void dfs(const Graph& g, const int v, bool* marked) {
        marked[v] = true;
        cc_id[v] = no_components;
        cc_size[no_components]++;
        for (auto w : g.adj(v)) {
            if (!marked[w]) dfs(g, w, marked);
        }
    }

   public:
    // constructor
    CC(const Graph& g) : no_components(0),
                         no_vertices(g.V()) {
        // initialize the marked, cc_id and cc_size array
        bool* marked = new bool[no_vertices];       // marked[v] = is there an s-v path?
        cc_id = new int[no_vertices];
        cc_size = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            marked[i] = false;
            cc_id[i] = -1;
            cc_size[i] = 0;
        }

        // run depth-first search recursively
        for (auto v = 0; v < no_vertices; v++) {
            if (!marked[v]) {
                dfs(g, v, marked);
                no_components++;
            }
        }

        // release the marked array
        delete[] marked;
    }

    // copy constructor
    CC(const CC& cc) : no_components(cc.no_components),
                       no_vertices(cc.no_vertices) {
        // allocated the cc_id and cc_size array
        cc_id = new int[no_vertices];
        cc_size = new int[no_vertices];

        // copy the cc_id and cc_size array
        for (auto i = 0; i < no_vertices; i++) {
            cc_id[i] = cc.cc_id[i];
            cc_size[i] = cc.cc_size[i];
        }
    }

    // move constructor
    CC(CC&& cc) : no_components(cc.no_components),
                  no_vertices(cc.no_vertices),
                  cc_size(cc.cc_size),
                  cc_id(cc.cc_id) {
        cc.no_vertices = 0;
        cc.no_components = 0;
        cc.cc_size = nullptr;
        cc.cc_id = nullptr;
    }

    // copy assignment
    CC& operator=(const CC& cc) {
        // free the existing cc_id and cc_size list
        delete[] cc_id;
        delete[] cc_size;

        // copy the DFS result list passed in
        no_vertices = cc.no_vertices;
        no_components = cc.no_components;

        cc_id = new int[no_vertices];
        cc_size = new int[no_vertices];

        for (auto i = 0; i < no_vertices; i++) {
            cc_id[i] = cc.cc_id[i];
            cc_size[i] = cc.cc_size[i];
        }

        return (*this);
    }

    // move assignment
    CC& operator=(CC&& cc) {
        // free the existing cc_id and cc_size list
        delete[] cc_id;
        delete[] cc_size;

        // copy the pointers
        no_vertices = cc.no_vertices;
        no_components = cc.no_components;

        cc_id = cc.cc_id;
        cc_size = cc.cc_size;

        // release the pointers for the no-longer valid object
        cc.no_vertices = 0;
        cc.no_components = 0;
        cc.cc_size = nullptr;
        cc.cc_id = nullptr;

        return (*this);
    }

    // destructor
    ~CC() {
        delete[] cc_id;
        delete[] cc_size;
    }

    // returns the component id of the connected component containing vertex v
    int id(const int v) const {
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (cc_id[v]);
    }

    // returns the number of vertices in the connected component containing vertex v
    int size(const int v) const {
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (cc_size[cc_id[v]]);
    }

    // returns true if vertices v and w are in the same connected component
    bool connected(const int v, const int w) const {
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        if (w < 0 || w >= no_vertices) throw logic_error("Vertex index out of range");
        return (cc_id[v] == cc_id[w]);
    }

    // returns the number of connected components in the graph
    int count() const { return (no_components); }
};

#endif
