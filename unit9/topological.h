/******************************************************************************
 *
 * Computes the topological order for a digraph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __TOPOLOGICAL_H__
#define __TOPOLOGICAL_H__

#include <stdexcept>

#include "digraph.h"
#include "directed_cycle.h"
#include "stack.h"

// Implements a class that computes the topological order of an acyclic digraph
class Topological {
    Stack<int>* post_order;  // vertices in postorder

    // run DFS in digraph dg from vertex v and computes postorder
    void dfs(const Digraph& dg, const int v, bool* marked) {
        marked[v] = true;
        for (auto w : dg.adj(v)) {
            if (!marked[w]) {
                dfs(dg, w, marked);
            }
        }
        post_order->push(v);

        return;
    }

   public:
    // constructor
    Topological(const Digraph& dg) {
        DirectedCycle finder(dg);

        if (!finder.has_cycle()) {
            // initialize the marked array
            bool* marked = new bool[dg.V()];  // marked[v] = has v been marked in dfs?
            for (auto v = 0; v < dg.V(); v++) {
                marked[v] = false;
            }

            post_order = new Stack<int>();

            // run DFS to compute the order
            for (auto v = 0; v < dg.V(); v++)
                if (!marked[v]) dfs(dg, v, marked);

            // free the marked array and set the pointer back to nullptr
            delete[] marked;
        } else
            post_order = nullptr;
    }

    // copy constructor
    Topological(const Topological& t) {
        // copy the reverse post-order vertices
        post_order = (t.post_order != nullptr) ? new Stack<int>(*t.post_order) : nullptr;
    }

    // move constructor
    Topological(Topological&& t) : post_order(t.post_order) {
        t.post_order = nullptr;
    }

    // copy assignment
    Topological& operator=(const Topological& t) {
        // free the existing post_order
        if (post_order) delete post_order;

        // copy the topological order passed in
        post_order = (t.post_order != nullptr) ? new Stack<int>(*t.post_order) : nullptr;

        return (*this);
    }

    // move assignment
    Topological& operator=(Topological&& t) {
        // free the existing post_order
        if (post_order) delete post_order;

        post_order = t.post_order;
        t.post_order = nullptr;

        return (*this);
    }

    // destructor
    ~Topological() {
        if (post_order) delete post_order;
    }

    // returns whether the digraph has a topological order
    bool has_order() const {
        return (post_order != nullptr);
    }
    // returns whether the digraph has a topological order
    bool is_DAG() const {
        return (has_order());
    }

    // returns the vertices in topological order
    Stack<int> order() const {
        if (has_order())
            return (*post_order);
        else
            throw logic_error("order() can only be called for DAGs.");
    }
};

#endif