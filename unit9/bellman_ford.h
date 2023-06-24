/******************************************************************************
 *
 * Computes the shortest path tree in edge-weighted digraph G from vertex s, or
 * finds a negative cost cycle reachable from s, using the Bellman-Ford shortest path algorithm.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __BELLMAN_FORD_H__
#define __BELLMAN_FORD_H__

#include <limits>

#include "edge.h"
#include "queue.h"
#include "stack.h"
#include "weighted_digraph.h"
#include "weighted_directed_cycle.h"

using namespace std;

// Implements a class that computes the shortest path tree in edge-weighted digraph G from vertex s using Bellman-Ford
class BellmanFordSP {
    int no_vertices;     // number of vertices
    double* dist_to;     // dist_to[v] = distance of shortest s->v path
    Edge* edge_to;       // edge_to[v] = last edge on shortest s->v path
    Stack<Edge>* cycle;  // negative cycle (or null if no such cycle)

    const Edge null_edge;

    // relax vertex v and put other endpoints on queue if changed
    void relax(const EdgeWeightedDigraph& dg, const int v, Queue<int>& queue, bool* on_queue, int& cost) {
        for (auto& e : dg.adj(v)) {
            int w = e.to();
            if (dist_to[w] > dist_to[v] + e.weight() + numeric_limits<double>::epsilon()) {
                dist_to[w] = dist_to[v] + e.weight();
                edge_to[w] = e;
                if (!on_queue[w]) {
                    queue.enqueue(w);
                    on_queue[w] = true;
                }
            }
            if (++cost % dg.V() == 0) {
                find_negative_cycle();
                if (has_negative_cycle()) return;  // found a negative cycle
            }
        }
        return;
    }

    // by finding a cycle in predecessor graph
    void find_negative_cycle() {
        EdgeWeightedDigraph spt(no_vertices);
        for (auto v = 0; v < no_vertices; v++)
            if (edge_to[v] != null_edge)
                spt.add_edge(edge_to[v]);

        EdgeWeightedDirectedCycle finder(spt);
        cycle = (finder.has_cycle()) ? new Stack<Edge>(finder.cycle()) : nullptr;

        return;
    }

   public:
    // constructor
    BellmanFordSP(const EdgeWeightedDigraph& dg, const int s) : no_vertices(dg.V()),
                                                                cycle(nullptr) {
        // allocate memory for dist_to, edge_to, and on_queue array
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];
        bool* on_queue = new bool[no_vertices];

        validate_vertex(s);

        // initialization of dist_to array
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = numeric_limits<double>::infinity();
            edge_to[v] = null_edge;
            on_queue[v] = false;
        }
        dist_to[s] = 0.0;

        // Bellman-Ford algorithm
        Queue<int> queue;
        int cost = 0;
        queue.enqueue(s);
        on_queue[s] = true;
        while (!queue.is_empty() && !has_negative_cycle()) {
            int v = queue.dequeue();
            on_queue[v] = false;
            relax(dg, v, queue, on_queue, cost);
        }

        // free the memory for the on_queue array
        delete[] on_queue;
    }

    // copy constructor
    BellmanFordSP(const BellmanFordSP& bsp) : no_vertices(bsp.no_vertices) {
        // allocate memory for dist_to and edge_to array
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];

        // copy the solution passed in
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = bsp.dist_to[v];
            edge_to[v] = bsp.edge_to[v];
        }

        // copy the cycle
        cycle = (bsp.has_negative_cycle()) ? new Stack<Edge>(*bsp.cycle) : nullptr;
    }

    // move constructor
    BellmanFordSP(BellmanFordSP&& bsp) : no_vertices(bsp.no_vertices),
                                         dist_to(bsp.dist_to),
                                         edge_to(bsp.edge_to),
                                         cycle(bsp.cycle) {
        bsp.no_vertices = 0;
        bsp.dist_to = nullptr;
        bsp.edge_to = nullptr;
        bsp.cycle = nullptr;
    }

    // copy assignment
    BellmanFordSP& operator=(const BellmanFordSP& bsp) {
        // possibly free the existing dcycle
        if (cycle) delete cycle;

        // free the memory for the dist_to and edge_to array
        delete[] dist_to;
        delete[] edge_to;

        // allocate memory for dist_to and edge_to array
        no_vertices = bsp.no_vertices;
        dist_to = new double[no_vertices];
        edge_to = new Edge[no_vertices];

        // copy the solution passed in
        for (auto v = 0; v < no_vertices; v++) {
            dist_to[v] = bsp.dist_to[v];
            edge_to[v] = bsp.edge_to[v];
        }
        cycle = (bsp.has_negative_cycle()) ? new Stack<Edge>(*bsp.cycle) : nullptr;

        return (*this);
    }

    // move assignment
    BellmanFordSP& operator=(BellmanFordSP&& bsp) {
        // possibly free the existing dcycle
        if (cycle) delete cycle;

        // free the memory for the dist_to and edge_to array
        delete[] dist_to;
        delete[] edge_to;

        // copy the weight and reset marked
        no_vertices = bsp.no_vertices;
        dist_to = bsp.dist_to;
        edge_to = bsp.edge_to;
        cycle = bsp.cycle;

        // mark the moved pointers to NULL
        bsp.no_vertices = 0;
        bsp.dist_to = nullptr;
        bsp.edge_to = nullptr;
        bsp.cycle = nullptr;

        return (*this);
    }

    // destructor
    ~BellmanFordSP() {
        delete[] dist_to;
        delete[] edge_to;
        if (cycle) delete cycle;
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
        if (has_negative_cycle()) throw logic_error("Negative cost cycle exists");

        Stack<Edge> path;
        if (!has_path_to(v)) return (path);

        for (auto e = edge_to[v]; e != null_edge; e = edge_to[e.from()]) {
            path.push(e);
        }
        return (path);
    }

    // returns if there is a negative cycle reachable from the source vertex
    bool has_negative_cycle() const {
        return (cycle != nullptr);
    }

    // returns a negative cycle reachable from the source vertex or nullptr, if it does not exists
    Stack<Edge>* negative_cycle() const {
        return (cycle);
    }
};

#endif