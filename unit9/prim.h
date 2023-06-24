/******************************************************************************
 *
 * Computes a minimum spanning forest using a lazy version of Prim's algorithm
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __PRIM_H__
#define __PRIM_H__

#include "edge.h"
#include "min_pq.h"
#include "queue.h"
#include "weighted_graph.h"

// Implements a class that computes a minimum spanning forest using a lazy version of Prim's algorithm
class LazyPrimMST {
    double mst_weight;  // total weight of MST
    Queue<Edge> mst;    // edges in the MST

    // add all edges e incident to v onto pq if the other endpoint has not yet been scanned
    void scan(const EdgeWeightedGraph& g, const int v, bool* marked, MinPQ<Edge>& pq) {
        marked[v] = true;
        for (auto& e : g.adj(v)) {
            if (!marked[e.other(v)]) pq.insert(e);
        }
        return;
    }

    // run Prim's algorithm
    void prim(const EdgeWeightedGraph& g, const int s, bool* marked, MinPQ<Edge>& pq) {
        scan(g, s, marked, pq);
        while (!pq.is_empty()) {                   // better to stop when mst has V-1 edges
            Edge e = pq.del_min();                 // smallest edge on pq
            int v = e.either(), w = e.other(v);    // two endpoints
            if (marked[v] && marked[w]) continue;  // lazy, both v and w already scanned
            mst.enqueue(e);                        // add e to MST
            mst_weight += e.weight();
            if (!marked[v]) scan(g, v, marked, pq);  // v becomes part of tree
            if (!marked[w]) scan(g, w, marked, pq);  // w becomes part of tree
        }
        return;
    }

   public:
    // constructor
    LazyPrimMST(const EdgeWeightedGraph& g) : mst_weight(0) {
        // allocate the marked array
        bool* marked = new bool[g.V()];  // marked[v] = v is on the MST
        for (auto v = 0; v < g.V(); v++) {
            marked[v] = false;
        }

        // run Prim from all vertices to
        MinPQ<Edge> pq;  // edges with one endpoint in tree
        for (auto v = 0; v < g.V(); v++) {
            if (!marked[v]) prim(g, v, marked, pq);
        }

        // release the marked array
        delete[] marked;
    }

    // copy constructor
    LazyPrimMST(const LazyPrimMST& m) : mst_weight(m.mst_weight),
                                        mst(m.mst) {}

    // move constructor
    LazyPrimMST(LazyPrimMST&& m) : mst_weight(m.mst_weight),
                                   mst(std::move(m.mst)) {}

    // copy assignment
    LazyPrimMST& operator=(const LazyPrimMST& m) {
        // copy the weight and mst
        mst_weight = m.mst_weight;
        mst = m.mst;

        return (*this);
    }

    // move assignment
    LazyPrimMST& operator=(LazyPrimMST&& m) {
        // copy the weight and move the mst
        mst_weight = m.mst_weight;
        mst = std::move(m.mst);

        return (*this);
    }

    // destructor
    ~LazyPrimMST() {}

    // returns the edges in a minimum spanning tree (or forest)
    const Queue<Edge>& edges() const {
        return (mst);
    }

    // returns the weight
    double weight() const {
        return (mst_weight);
    }
};

#endif