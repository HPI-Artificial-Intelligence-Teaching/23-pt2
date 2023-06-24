/******************************************************************************
 *
 * Compute preorder and postorder for a digraph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __DFO_H__
#define __DFO_H__

#include <stdexcept>

#include "digraph.h"
#include "queue.h"
#include "stack.h"

// Implements a class representing a data type for determining depth-first search ordering of the vertices in a digraphdata type for determining the vertices connected to a given source vertex s
class DepthFirstOrder {
    int no_vertices;         // total number of vertices
    int* pre;                // pre[v] = preorder  number of v
    int* post;               // post[v] = postorder number of v
    Queue<int>* pre_order;   // vertices in preorder
    Queue<int>* post_order;  // vertices in postorder
    int pre_counter;         // counter or preorder numbering
    int post_counter;        // counter or postorder numbering

    // run DFS in digraph dg from vertex v and compute preorder/postorder
    void dfs(const Digraph& dg, const int v, bool* marked) {
        marked[v] = true;
        pre[v] = pre_counter++;
        pre_order->enqueue(v);
        for (auto w : dg.adj(v)) {
            if (!marked[w]) {
                dfs(dg, w, marked);
            }
        }
        post_order->enqueue(v);
        post[v] = post_counter++;

        return;
    }

   public:
    // constructor
    DepthFirstOrder(const Digraph& dg) : no_vertices(dg.V()),
                                         pre_counter(0),
                                         post_counter(0) {
        // initialize the marked, pre and post array
        bool* marked = new bool[no_vertices];       // marked[v] = has v been marked in dfs?
        pre = new int[no_vertices];
        post = new int[no_vertices];
        for (auto v = 0; v < no_vertices; v++) {
            marked[v] = false;
        }

        pre_order = new Queue<int>();
        post_order = new Queue<int>();

        // run DFS to compute the order
        for (auto v = 0; v < no_vertices; v++)
            if (!marked[v]) dfs(dg, v, marked);

        // free the marked array
        delete[] marked;
    }

    // copy constructor
    DepthFirstOrder(const DepthFirstOrder& dfo) : no_vertices(dfo.no_vertices),
                                                  pre_counter(dfo.pre_counter),
                                                  post_counter(dfo.post_counter) {
        // initialize the marked, pre and post array
        pre = new int[no_vertices];
        post = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            pre[i] = dfo.pre[i];
            post[i] = dfo.post[i];
        }

        // copy the pre- and post-order vertices
        pre_order = new Queue<int>(*dfo.pre_order);
        post_order = new Queue<int>(*dfo.post_order);
    }

    // move constructor
    DepthFirstOrder(DepthFirstOrder&& dfo) : no_vertices(dfo.no_vertices),
                                             pre_counter(dfo.pre_counter),
                                             post_counter(dfo.post_counter),
                                             pre(dfo.pre),
                                             post(dfo.post),
                                             pre_order(dfo.pre_order),
                                             post_order(dfo.post_order) {
        dfo.no_vertices = 0;
        dfo.pre_counter = 0;
        dfo.post_counter = 0;
        dfo.pre = nullptr;
        dfo.post = nullptr;
        dfo.pre_order = nullptr;
        dfo.post_order = nullptr;
    }

    // copy assignment
    DepthFirstOrder& operator=(const DepthFirstOrder& dfo) {
        // free the existing pre and post list and pre_order and post_order
        delete[] pre;
        delete[] post;
        delete pre_order;
        delete post_order;

        // copy the DFO passed in
        no_vertices = dfo.no_vertices;
        pre_counter = dfo.pre_counter;
        post_counter = dfo.post_counter;

        // initialize the marked, pre and post array
        pre = new int[no_vertices];
        post = new int[no_vertices];
        for (auto i = 0; i < no_vertices; i++) {
            pre[i] = dfo.pre[i];
            post[i] = dfo.post[i];
        }

        // copy the pre- and post-order vertices
        pre_order = new Queue<int>(*dfo.pre_order);
        post_order = new Queue<int>(*dfo.post_order);

        return (*this);
    }

    // move assignment
    DepthFirstOrder& operator=(DepthFirstOrder&& dfo) {
        // free the existing pre and post list and pre_order and post_order
        delete[] pre;
        delete[] post;
        delete pre_order;
        delete post_order;

        no_vertices = dfo.no_vertices;
        pre_counter = dfo.pre_counter;
        post_counter = dfo.post_counter;
        pre = dfo.pre;
        post = dfo.post;
        pre_order = dfo.pre_order;
        post_order = dfo.post_order;

        dfo.no_vertices = 0;
        dfo.pre_counter = 0;
        dfo.post_counter = 0;
        dfo.pre = nullptr;
        dfo.post = nullptr;
        dfo.pre_order = nullptr;
        dfo.post_order = nullptr;

        return (*this);
    }

    // destructor
    ~DepthFirstOrder() {
        delete[] pre;
        delete[] post;
        delete pre_order;
        delete post_order;
    }

    // returns the pre-order number of vertex v
    int preorder(const int v) const {
        // validate the target index
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (pre[v]);
    }

    // returns the vertices in pre-order
    const Queue<int>& preorder() const {
        return (*pre_order);
    }

    // returns the prost-order number of vertex v
    int postorder(const int v) const {
        // validate the target index
        if (v < 0 || v >= no_vertices) throw logic_error("Vertex index out of range");
        return (post[v]);
    }

    // returns the vertices in post-order
    const Queue<int>& postorder() const {
        return (*post_order);
    }

    // returns the vertices in reverse post-order
    Stack<int> reverse_order() const {
        Stack<int> reverse;

        for (auto v : *post_order)
            reverse.push(v);

        return (reverse);
    }
};

#endif