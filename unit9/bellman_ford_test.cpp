/******************************************************************************
 *
 * Computes the shortest path tree in edge-weighted digraph G from vertex s, or
 * finds a negative cost cycle reachable from s, using the Bellman-Ford shortest path algorithm.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./bellman_ford_test ../data/tinyEWDn.txt 0
 *  0 to 0 (0.00)
 *  0 to 1 (0.93)  0->2  0.26   2->7  0.34   7->3  0.39   3->6  0.52   6->4  -1.25   4->5  0.35   5->1  0.32
 *  0 to 2 (0.26)  0->2  0.26
 *  0 to 3 (0.99)  0->2  0.26   2->7  0.34   7->3  0.39
 *  0 to 4 (0.26)  0->2  0.26   2->7  0.34   7->3  0.39   3->6  0.52   6->4  -1.25
 *  0 to 5 (0.61)  0->2  0.26   2->7  0.34   7->3  0.39   3->6  0.52   6->4  -1.25   4->5  0.35
 *  0 to 6 (1.51)  0->2  0.26   2->7  0.34   7->3  0.39   3->6  0.52
 *  0 to 7 (0.60)  0->2  0.26   2->7  0.34
 *
 *  % ./bellman_ford_test ../data/tinyEWDnc.txt 0
 *  4->5  0.35
 *  5->4  -0.66
 *
 ******************************************************************************/

#include "bellman_ford.h"

#include <fstream>
#include <iostream>

#include "weighted_digraph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 3) {
        cerr << "Invalid number of arguments. Call with filename and index of source vertex." << endl;
        return (1);
    }

    // read the graph from the file
    ifstream graph_file;
    graph_file.open(argv[1]);
    if (!graph_file) {
        cerr << "Unable to open file" << argv[1] << endl;
        return (1);
    }
    EdgeWeightedDigraph dg(graph_file);
    graph_file.close();

    // read the source vertex and initialize the depth-first search
    int s = atoi(argv[2]);
    BellmanFordSP sp(dg, s);

    // print negative cycle
    if (sp.has_negative_cycle()) {
        for (auto& e : *sp.negative_cycle())
            cout << e.from() << "->" << e.to() << "  " << fixed << setprecision(2) << e.weight() << endl;
    } else {
        // output the graph on the screen
        for (auto v = 0; v < dg.V(); v++) {
            if (sp.has_path_to(v)) {
                cout << s << " to " << v << " (" << fixed << setprecision(2) << sp.distance_to(v) << ")  ";
                for (auto& e : sp.path_to(v)) {
                    cout << e.from() << "->" << e.to() << "  " << fixed << setprecision(2) << e.weight() << "   ";
                }
                cout << endl;
            } else {
                cout << s << " to " << v << "         no path" << endl;
            }
        }
    }

    return (0);
}