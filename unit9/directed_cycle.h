/******************************************************************************
 *
 * A depth first search on a directed graph that determines whether a digraph has a directed cycle
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __DIRECTED_CYCLE_H__
#define __DIRECTED_CYCLE_H__

#include <stdexcept>

#include "digraph.h"
#include "stack.h"

// Implements a class that determines whether a digraph has a directed cycle
class DirectedCycle {
    Stack<int>* dcycle;  // directed cycle (or null if no such cycle)

    // run DFS and find a directed cycle (if one exists)
    void dfs(const Digraph& dg, const int v, bool* marked, bool* on_stack, int* edge_to) {
        on_stack[v] = true;
        marked[v] = true;
        for (auto w : dg.adj(v)) {
            // short circuit if directed cycle found
            if (dcycle != nullptr) {
                return;
            } else if (!marked[w]) {
                // found new vertex, so recur
                edge_to[w] = v;
                dfs(dg, w, marked, on_stack, edge_to);
            } else if (on_stack[w]) {
                // trace back directed cycle
                dcycle = new Stack<int>();
                for (auto x = v; x != w; x = edge_to[x])
                    dcycle->push(x);
                dcycle->push(w);
                dcycle->push(v);
            }
        }
        on_stack[v] = false;
    }

   public:
    // constructor
    DirectedCycle(const Digraph& dg) : dcycle(nullptr) {
        // initialize the marked, on_stack and edge_to array
        bool* marked = new bool[dg.V()];        // marked[v] = has vertex v been marked?
        bool* on_stack = new bool[dg.V()];      // on_stack[v] = is vertex on the stack?
        int* edge_to = new int[dg.V()];         // edge_to[v] = previous vertex on path to v
        for (auto v = 0; v < dg.V(); v++) {
            marked[v] = false;
            on_stack[v] = false;
            edge_to[v] = -1;
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
    DirectedCycle(const DirectedCycle& dc) {
        // copy the cycle
        dcycle = (dc.has_cycle()) ? new Stack<int>(*dc.dcycle) : nullptr;
    }

    // move constructor
    DirectedCycle(DirectedCycle&& dc) : dcycle(dc.dcycle) {
        dc.dcycle = nullptr;
    }

    // copy assignment
    DirectedCycle& operator=(const DirectedCycle& dc) {
        // possibly free the existing dcycle
        if (dcycle) delete dcycle;

        // copy the direct cycle passed in
        dcycle = (dc.has_cycle()) ? new Stack<int>(*dc.dcycle) : nullptr;

        return (*this);
    }

    // move assignment
    DirectedCycle& operator=(DirectedCycle&& dc) {
        // possibly free the existing dcycle
        if (dcycle) delete dcycle;

        // copy the directed cycle (without a deep copy)
        dcycle = dc.dcycle;

        dc.dcycle = nullptr;

        return (*this);
    }

    // destructor
    ~DirectedCycle() {
        if (dcycle) delete dcycle;
    }

    // returns if the digraph has a directed cycle
    bool has_cycle() const { return (dcycle != nullptr); }

    // returns the directed cycle (if the digraph has a directed cycle)
    Stack<int> cycle() const {
        if (has_cycle())
            return (*dcycle);
        else
            throw logic_error("Digraph has no cycle");
    }
};

#endif