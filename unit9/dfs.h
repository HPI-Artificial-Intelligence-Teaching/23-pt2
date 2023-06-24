/******************************************************************************
 *
 * A depth first search on an undirected graph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __DFS_H__
#define __DFS_H__

#include <stdexcept>

#include "graph.h"
#include "stack.h"

// Implements a class representing a data type for determining the vertices connected to a given source vertex s
class DepthFirstSearch {
    int no_vertices;   // total number of vertices
    bool* marked;      // marked[v] = is there an s-v path?
    int* edge_to;      // edge_to[v] = previous edge on shortest s-v path
    int no_connected;  // number of vertices connected to s
    int source;        // index of the source node

    // depth first search from v
    void dfs(const Graph& g, const int v) {
        no_connected++;
        marked[v] = true;
        for (auto w : g.adj(v)) {
            if (!marked[w]) {
                dfs(g, w);
                edge_to[w] = v;
            }
        }
    }

   public:
    // constructor
    DepthFirstSearch(const Graph& g, const int s) : no_connected(0),
                                                    no_vertices(g.V()),
                                                    source(s) {
        // validate the source index
        if (s < 0 || s >= no_vertices) throw logic_error("Vertex index out of range");

        // initialize the marked and edge_to array
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        for (auto v = 0; v < no_vertices; v++) {
            marked[v] = false;
            edge_to[v] = -1;
        }

        // run depth-first search recursively
        dfs(g, s);
    }

    // copy constructor
    DepthFirstSearch(const DepthFirstSearch& d) : no_connected(d.no_connected),
                                                  no_vertices(d.no_vertices),
                                                  source(d.source) {
        // initialize the marked and edge_to array
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            marked[i] = d.marked[i];
            edge_to[i] = d.edge_to[i];
        }
    }

    // move constructor
    DepthFirstSearch(DepthFirstSearch&& d) : no_vertices(d.no_vertices),
                                             no_connected(d.no_connected),
                                             source(d.source),
                                             marked(d.marked),
                                             edge_to(d.edge_to) {
        d.no_vertices = 0;
        d.no_connected = 0;
        d.marked = nullptr;
        d.edge_to = nullptr;
    }

    // copy assignment
    DepthFirstSearch& operator=(const DepthFirstSearch& d) {
        // free the existing marked and edge_to list
        delete[] marked;
        delete[] edge_to;

        // copy the DFS result list passed in
        no_vertices = d.no_vertices;
        no_connected = d.no_connected;
        source = d.source;
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            marked[i] = d.marked[i];
            edge_to[i] = d.edge_to[i];
        }

        return (*this);
    }

    // move assignment
    DepthFirstSearch& operator=(DepthFirstSearch&& d) {
        // free the existing marked and edge_to lists
        delete[] marked;
        delete[] edge_to;

        no_vertices = d.no_vertices;
        no_connected = d.no_connected;
        source = d.source;
        marked = d.marked;
        edge_to = d.edge_to;
        d.no_vertices = 0;
        d.no_connected = 0;
        d.marked = nullptr;
        d.edge_to = nullptr;
        return (*this);
    }

    // destructor
    ~DepthFirstSearch() {
        delete[] marked;
        delete[] edge_to;
    }

    // returns the number of vertices connected to the source vertex
    int count() const { return (no_connected); }

    // returns if there is a path between the source vertex and vertex v
    bool has_path_to(const int v) const {
        // validate the target index
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (marked[v]);
    }

    // returns a path between the source vertex and a vertex v
    Stack<int> path_to(const int v) const {
        Stack<int> path;

        if (!has_path_to(v)) return (path);
        int x = v;
        while (x != source) {
            path.push(x);
            x = edge_to[x];
        }
        path.push(x);
        return (path);
    }
};

#endif
