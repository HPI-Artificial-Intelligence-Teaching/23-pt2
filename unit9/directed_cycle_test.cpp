/******************************************************************************
 *
 * A depth first search on a directed graph that determines whether a digraph has a directed cycle
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./directed_cycle_test ../data/tinyDG.txt
 *  Directed cycle: 3 5 4 3
 *
 *  % ./directed_cycle_test ../data/tinyDAG.txt
 *  No directed cycle
 *
 ******************************************************************************/

#include "directed_cycle.h"

#include <fstream>
#include <iostream>

#include "digraph.h"

using namespace std;

// main entry point of the program
int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 2) {
        cerr << "Invalid command line. Expecting one argument of input file name." << endl;
        return (1);
    }

    // read the digraph from the file
    ifstream graph_file;
    graph_file.open(argv[1]);
    if (!graph_file) {
        cerr << "Unable to open file " << argv[1] << endl;
        return (1);
    }
    Digraph dg(graph_file);
    graph_file.close();

    // output the digraph on the screen
    DirectedCycle finder(dg);
    if (finder.has_cycle()) {
        cout << "Directed cycle: ";
        for (auto v : finder.cycle())
            cout << v << " ";
        cout << endl;
    } else
        cout << "No directed cycle" << endl;

    return (0);
}