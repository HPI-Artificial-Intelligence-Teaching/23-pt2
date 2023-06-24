/******************************************************************************
 *
 * Computes the shortest path tree using Dijkstra's algorithm (assumes all weights are non-negative)
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./dijkstra_test ../data/tinyEWD.txt 0
 *  0 to 0 (0.00)
 *  0 to 1 (1.05)  0->4  0.38   4->5  0.35   5->1  0.32
 *  0 to 2 (0.26)  0->2  0.26
 *  0 to 3 (0.99)  0->2  0.26   2->7  0.34   7->3  0.39
 *  0 to 4 (0.38)  0->4  0.38
 *  0 to 5 (0.73)  0->4  0.38   4->5  0.35
 *  0 to 6 (1.51)  0->2  0.26   2->7  0.34   7->3  0.39   3->6  0.52
 *  0 to 7 (0.60)  0->2  0.26   2->7  0.34
 *
 *  % ./dijkstra_test ../data/mediumEWD.txt 0
 *  0 to 0 (0.00)
 *  0 to 1 (0.71)  0->44  0.06   44->93  0.07   ...  107->1  0.07
 *  0 to 2 (0.65)  0->44  0.06   44->231  0.10  ...  42->2  0.11
 *  0 to 3 (0.46)  0->97  0.08   97->248  0.09  ...  45->3  0.12
 *  0 to 4 (0.42)  0->44  0.06   44->93  0.07   ...  77->4  0.11
 *  ...
 *
 ******************************************************************************/

#include "dijkstra.h"

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
    DijkstraSP sp(dg, s);

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

    return (0);
}