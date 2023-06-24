/******************************************************************************
 *
 * A breadth first search on an undirected graph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __BFS_H__
#define __BFS_H__

#include <limits>
#include <stdexcept>

#include "graph.h"
#include "queue.h"
#include "stack.h"

// Implements a class representing a data type for determining the vertices connected to a given source vertex s
class BreadthFirstSearch {
    int no_vertices;  // total number of vertices
    bool* marked;     // marked[v] = is there an s-v path?
    int* edge_to;     // edge_to[v] = previous edge on shortest s-v path
    int* dist_to;     // dist_to[v] = number of edges shortest s-v path

    // breadth first search from a single source s
    void bfs(const Graph& g, const int s);

   public:
    // constructor
    BreadthFirstSearch(const Graph& g, const int s) : no_vertices(g.V()) {
        // validate the source index
        if (s < 0 || s >= no_vertices) throw logic_error("Vertex index out of range");

        // initialize the marked edge_to and dist_to array
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        dist_to = new int[no_vertices];

        // run breadth-first search
        bfs(g, s);
    }

    // copy constructor
    BreadthFirstSearch(const BreadthFirstSearch& b) : no_vertices(b.no_vertices) {
        // initialize the marked, edge_to and dist_to array
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        dist_to = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            marked[i] = b.marked[i];
            edge_to[i] = b.edge_to[i];
            dist_to[i] = b.dist_to[i];
        }
    }

    // move constructor
    BreadthFirstSearch(BreadthFirstSearch&& b) : no_vertices(b.no_vertices),
                                                 marked(b.marked),
                                                 edge_to(b.edge_to),
                                                 dist_to(b.dist_to) {
        b.no_vertices = 0;
        b.marked = nullptr;
        b.edge_to = nullptr;
        b.dist_to = nullptr;
    }

    // copy assignment
    BreadthFirstSearch& operator=(const BreadthFirstSearch& b) {
        // free the existing marked, edge_to, dist_to list
        delete[] marked;
        delete[] edge_to;
        delete[] dist_to;

        // copy the BFS result list passed in
        no_vertices = b.no_vertices;
        marked = new bool[no_vertices];
        edge_to = new int[no_vertices];
        dist_to = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            marked[i] = b.marked[i];
            edge_to[i] = b.edge_to[i];
            dist_to[i] = b.dist_to[i];
        }

        return (*this);
    }

    // move assignment
    BreadthFirstSearch& operator=(BreadthFirstSearch&& b) {
        // free the existing marked, edge_to and dist_to lists
        delete[] marked;
        delete[] edge_to;
        delete[] dist_to;

        no_vertices = b.no_vertices;
        marked = b.marked;
        edge_to = b.edge_to;
        dist_to = b.dist_to;
        b.no_vertices = 0;
        b.marked = nullptr;
        b.edge_to = nullptr;
        b.dist_to = nullptr;
        return (*this);
    }

    // destructor
    ~BreadthFirstSearch() {
        delete[] marked;
        delete[] edge_to;
        delete[] dist_to;
    }

    // returns if there is a path between the source vertex and vertex v
    bool has_path_to(const int v) const;

    // returns the number of edges in a shortest path between the source vertex and vertex v
    int distance_to(const int v) const;

    // returns a shortest path between the source vertex and a vertex v
    Stack<int> path_to(const int v) const;
};

#endif
