/******************************************************************************
 *
 * A depth first search on a weighted directed graph that determines whether an
 * edge-weighted digraph has a directed cycle
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __WEIGHTED_DIRECTED_CYCLE_H__
#define __WEIGHTED_DIRECTED_CYCLE_H__

#include <stdexcept>

#include "edge.h"
#include "stack.h"
#include "weighted_digraph.h"

// Implements a class that determines whether an edge-weighted digraph has a directed cycle
class EdgeWeightedDirectedCycle {
    Stack<Edge>* dcycle;  // directed cycle (or null if no such cycle)

    const Edge null_edge;

    // run DFS and find a directed cycle (if one exists)
    void dfs(const EdgeWeightedDigraph& dg, const int v, bool* marked, bool* on_stack, Edge* edge_to) {
        on_stack[v] = true;
        marked[v] = true;
        for (auto& e : dg.adj(v)) {
            const int w = e.to();

            // short circuit if directed cycle found
            if (dcycle != nullptr) {
                return;
            } else if (!marked[w]) {
                // found new vertex, so recur
                edge_to[w] = e;
                dfs(dg, w, marked, on_stack, edge_to);
            } else if (on_stack[w]) {
                // trace back directed cycle
                dcycle = new Stack<Edge>();
                Edge f = e;
                while (f.from() != w) {
                    dcycle->push(f);
                    f = edge_to[f.from()];
                }
                dcycle->push(f);
            }
        }
        on_stack[v] = false;
    }

   public:
    // constructor
    EdgeWeightedDirectedCycle(const EdgeWeightedDigraph& dg) : dcycle(nullptr) {
        // initialize the marked, on_stack and edge_to array
        bool* marked = new bool[dg.V()];    // marked[v] = has vertex v been marked?
        bool* on_stack = new bool[dg.V()];  // on_stack[v] = is vertex on the stack?
        Edge* edge_to = new Edge[dg.V()];   // edge_to[v] = previous vertex on path to v
        for (auto v = 0; v < dg.V(); v++) {
            marked[v] = false;
            on_stack[v] = false;
            edge_to[v] = null_edge;
        }

        // run depth-first search recursively
        for (auto v = 0; v < dg.V(); v++)
            if (!marked[v] && dcycle == nullptr)
                dfs(dg, v, marked, on_stack, edge_to);

        // free the memory for the marked, on_stack and edge_to array
        delete[] marked;
        delete[] on_stack;
        delete[] edge_to;
    }

    // copy constructor
    EdgeWeightedDirectedCycle(const EdgeWeightedDirectedCycle& dc) {
        // copy the cycle
        dcycle = (dc.has_cycle()) ? new Stack<Edge>(*dc.dcycle) : nullptr;
    }

    // move constructor
    EdgeWeightedDirectedCycle(EdgeWeightedDirectedCycle&& dc) : dcycle(dc.dcycle) {
        dc.dcycle = nullptr;
    }

    // copy assignment
    EdgeWeightedDirectedCycle& operator=(const EdgeWeightedDirectedCycle& dc) {
        // possibly free the existing dcycle
        if (dcycle) delete dcycle;

        // copy the direct cycle passed in
        dcycle = (dc.has_cycle()) ? new Stack<Edge>(*dc.dcycle) : nullptr;

        return (*this);
    }

    // move assignment
    EdgeWeightedDirectedCycle& operator=(EdgeWeightedDirectedCycle&& dc) {
        // possibly free the existing dcycle
        if (dcycle) delete dcycle;

        // copy the directed cycle (without a deep copy)
        dcycle = dc.dcycle;

        dc.dcycle = nullptr;

        return (*this);
    }

    // destructor
    ~EdgeWeightedDirectedCycle() {
        if (dcycle) delete dcycle;
    }

    // returns if the edge-weighted digraph has a directed cycle
    bool has_cycle() const { return (dcycle != nullptr); }

    // returns the directed cycle (if the edge-weighted digraph has a directed cycle)
    Stack<Edge> cycle() const {
        if (has_cycle())
            return (*dcycle);
        else
            throw logic_error("Digraph has no cycle");
    }
};

#endif