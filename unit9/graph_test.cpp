/******************************************************************************
 *
 * A graph, implemented using an array of sets. Parallel edges and self-loops allowed.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./graph_test ../data/tinyG.txt
 *  13 vertices, 13 edges
 *  0: 6 2 1 5
 *  1: 0
 *  2: 0
 *  3: 5 4
 *  4: 5 6 3
 *  5: 3 4 0
 *  6: 0 4
 *  7: 8
 *  8: 7
 *  9: 11 10 12
 *  10: 9
 *  11: 9 12
 *  12: 11 9
 *
 *  % ./graph_test ../data/mediumG.txt
 *  250 vertices, 1273 edges
 *  0: 225 222 211 209 204 202 191 176 163 160 149 114 97 80 68 59 58 49 44 24 15
 *  1: 220 203 200 194 189 164 150 130 107 72
 *  2: 141 110 108 86 79 51 42 18 14
 *
 *  ...
 ******************************************************************************/

#include "graph.h"

#include <fstream>
#include <iostream>

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
    Graph g(graph_file);
    graph_file.close();

    // output the graph on the screen
    cout << g << endl;

    return (0);
}