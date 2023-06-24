/******************************************************************************
 *
 * Computes a minimum spanning forest using a lazy version of Prim's algorithm
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  %  ./prim_test ../data/tinyEWG.txt
 *  0-7 0.16000
 *  1-7 0.19000
 *  0-2 0.26000
 *  2-3 0.17000
 *  5-7 0.28000
 *  4-5 0.35000
 *  6-2 0.40000
 *  1.81000
 *
 *  %  ./prim_test ../data/mediumEWG.txt
 *  0-225   0.02383
 *  49-225  0.03314
 *  44-49   0.02107
 *  44-204  0.01774
 *  49-97   0.03121
 *  202-204 0.04207
 *  176-202 0.04299
 *  176-191 0.02089
 *  68-176  0.04396
 *  58-68   0.04795
 *  ...
 *  10.46351
 *
 ******************************************************************************/

#include "prim.h"

#include <fstream>
#include <iostream>

#include "weighted_graph.h"

using namespace std;

// main entry point of the program
int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 2) {
        cerr << "Invalid command line. Expecting one argument of input file name." << endl;
        return (1);
    }

    // read the graph from the file
    ifstream graph_file;
    graph_file.open(argv[1]);
    if (!graph_file) {
        cerr << "Unable to open file " << argv[1] << endl;
        return (1);
    }
    EdgeWeightedGraph g(graph_file);
    graph_file.close();

    // output the graph on the screen
    LazyPrimMST mst(g);
    for (auto& e : mst.edges()) {
        cout << e.from() << "-" << e.to() << " " << fixed << setprecision(5) << e.weight() << "  " << endl;
    }
    cout << fixed << setprecision(5) << mst.weight() << endl;

    return (0);
}