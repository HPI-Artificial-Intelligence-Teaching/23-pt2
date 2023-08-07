
#include <cmath>
#include <functional>
#include <vector>

#include "vlib/bag.h"
#include "vlib/index_min_pq.h"
#include "vlib/redblack_bst.h"
#include "weighted_struct_digraph.h"

template <typename T>
Bag<T> a_star(
    const WeightedStructDigraph<T>& sdg, const T& source, const T& dest,
    std::function<float(const WeightedStructDigraph<T>&, const T&, const T&)>
        heuristic) {
    EdgeWeightedDigraph graph = *(sdg.get_graph());
    Bag<T> pth;
    if (!sdg.contains(source) || !sdg.contains(dest)) {
        return pth;
    }
    // TODO: Implementieren Sie hier den A*-Algorithmus
    IndexMinPQ<float> openVertices(graph.V());
    openVertices.insert(sdg.index_of(source), 0);
    RedBlackBST<int, int> closedVertices;
    RedBlackBST<int, float> costs;
    for (int i = 0; i < graph.V(); i++) {
        costs.put(i, INFINITY);
    }
    costs.put(sdg.index_of(source), 0);
    RedBlackBST<int, int> parents;
    parents.put(sdg.index_of(source), -1);
    bool found = false;
    while (!openVertices.is_empty()) {
        // select minimum cost vertex from openvertices;
        // std::cout << openVertices;
        int vi = openVertices.del_min();
        // std::cout << "Current: " << vi << std::endl;
        // if we have reached our destination we can look up the path
        if (vi == sdg.index_of(dest)) {
            // std::cout << "Reached dest." << std::endl;
            found = true;
            break;
        }
        // add vi to closedVertices
        closedVertices.put(vi, vi);
        // get neighbours nk
        for (auto nk : sdg.get_graph()->adj(vi)) {
            // for every neighbour of vi do stuff
            if (!closedVertices.contains(nk.to())) {
                // calc cost of path to nk
                float nk_cost = *(costs.get(vi)) + nk.weight();
                // if cost smaller than saved update
                if (nk_cost < *(costs.get(nk.to()))) {
                    // save updated cost
                    // std::cout << "Updated Cost for " << nk.to() << ":"
                    //           << nk_cost << std::endl;
                    costs.put(nk.to(), nk_cost);
                    parents.put(nk.to(), vi);
                    // std::cout << "Vo contains " << nk.to() << "? "
                    //           << openVertices.contains(nk.to()) << std::endl;
                    if (!openVertices.contains(nk.to())) {
                        // std::cout << "Adding " << nk.to() << std::endl;
                        openVertices.insert(
                            nk.to(),
                            nk_cost +
                                heuristic(sdg, sdg.name_of(nk.to()), dest));
                    } else {
                        // std::cout << openVertices << std::endl;
                        // std::cout << "Changing " << nk.to() << std::endl;
                        openVertices.change_key(
                            nk.to(),
                            nk_cost +
                                heuristic(sdg, sdg.name_of(nk.to()), dest));
                    }
                }
            }
        }
    }
    if (found) {
        int c = sdg.index_of(dest);
        while (c != -1) {
            pth.add(sdg.name_of(c));
            if (parents.get(c)) {
                c = *(parents.get(c));
            } else {
                throw(std::logic_error("This path should not be reachable"));
            }
        }
    }
    return pth;
}