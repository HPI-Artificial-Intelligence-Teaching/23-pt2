/******************************************************************************
 *
 * Computes the shortest path tree using Dijkstra's algorithm (assumes all weights are non-negative)
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <limits>

#include "edge.h"
#include "index_min_pq.h"
#include "stack.h"
#include "weighted_digraph.h"

// Implements a class that computes the shortest path tree using Dijkstra's algorithm
class DijkstraSP {
    int no_vertices;  // number of vertices
    double* dist_to;  // dist_to[v] = distance of shortest s->v path
    Edge* edge_to;    // edge_to[v] = last edge on shortest s->v path

    const Edge null_edge;

    // relax edge e and update pq if changed
    void relax(const Edge& e, IndexMinPQ<double>& pq) {
        const int v = e.from();
        const int w = e.to();
        if (dist_to[w] > dist_to[v] + e.weight()) {
            dist_to[w] = dist_to[v] + e.weight();
            edge_to[w] = e;
            if (pq.contains(w))
                pq.decrease_key(w, dist_to[w]);
            else
                pq.insert(w, dist_to[w]);
        }
        return;
    }

   public:
    // constructor
    DijkstraSP(const EdgeWeightedDigraph& dg, const int s) : no_vertices(dg.V()) {
        // check that all weights are non-negative
        for (auto& e : dg.edges()) {
            if (e.weight() < 0) throw logic_error("one edge has negative weight");
        }

        // allocate memory for dist_to and edge_to array
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];

        validate_vertex(s);

        // initialization of dist_to array
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = numeric_limits<double>::infinity();
            edge_to[v] = null_edge;
        }
        dist_to[s] = 0.0;

        // relax vertices in order of distance from s
        IndexMinPQ<double> pq(no_vertices);  // priority queue of vertices
        pq.insert(s, dist_to[s]);
        while (!pq.is_empty()) {
            int v = pq.del_min();
            for (auto& e : dg.adj(v))
                relax(e, pq);
        }
    }

    // copy constructor
    DijkstraSP(const DijkstraSP& dsp) : no_vertices(dsp.no_vertices) {
        // allocate memory for dist_to and edge_to array
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];

        // copy the solution passed in
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = dsp.dist_to[v];
            edge_to[v] = dsp.edge_to[v];
        }
    }

    // move constructor
    DijkstraSP(DijkstraSP&& dsp) : no_vertices(dsp.no_vertices),
                                   dist_to(dsp.dist_to),
                                   edge_to(dsp.edge_to) {
        dsp.no_vertices = 0;
        dsp.dist_to = nullptr;
        dsp.edge_to = nullptr;
    }

    // copy assignment
    DijkstraSP& operator=(const DijkstraSP& dsp) {
        // free the memory for the dist_to and edge_to array
        delete[] dist_to;
        delete[] edge_to;

        // allocate memory for dist_to and edge_to array
        no_vertices = dsp.no_vertices;
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];

        // copy the solution passed in
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = dsp.dist_to[v];
            edge_to[v] = dsp.edge_to[v];
        }

        return (*this);
    }

    // move assignment
    DijkstraSP& operator=(DijkstraSP&& dsp) {
        // free the memory for the dist_to and edge_to array
        delete[] dist_to;
        delete[] edge_to;

        // copy the weight and reset marked
        no_vertices = dsp.no_vertices;
        dist_to = dsp.dist_to;
        edge_to = dsp.edge_to;

        // mark the moved pointers to NULL
        dsp.no_vertices = 0;
        dsp.dist_to = nullptr;
        dsp.edge_to = nullptr;

        return (*this);
    }

    // destructor
    ~DijkstraSP() {
        delete[] dist_to;
        delete[] edge_to;
    }

    // validates a vertex index
    void validate_vertex(const int v) const {
        if (v < 0 || v >= no_vertices)
            throw logic_error("Vertex index out of range");
    }

    // returns the length of a shortest path from the source vertex to vertex v
    double distance_to(const int v) const {
        validate_vertex(v);
        return (dist_to[v]);
    }

    // returns if there is a path between the source vertex and vertex v
    bool has_path_to(const int v) const {
        validate_vertex(v);
        return (dist_to[v] < numeric_limits<double>::infinity());
    }

    // returns a shortest path from the source vertex to vertex v
    const Stack<Edge> path_to(const int v) const {
        validate_vertex(v);

        Stack<Edge> path;
        if (!has_path_to(v)) return (path);

        for (auto e = edge_to[v]; e != null_edge; e = edge_to[e.from()]) {
            path.push(e);
        }
        return (path);
    }
};

#endif