/******************************************************************************
 *
 * Computes the strongly-connected components of a digraph using the Kosaraju-Sharir algorithm
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./scc_test ../data/tinyDG.txt
 *  5 strong components
 *  1
 *  0 2 3 4 5
 *  9 10 11 12
 *  6 8
 *  7
 *
 *  % ./scc_test ../data/mediumDG.txt
 *  10 strong components
 *  21
 *  2 5 6 8 9 11 12 13 15 16 18 19 22 23 25 26 28 29 30 31 32 33 34 35 37 38 39 40 42 43 44 46 47 48 49
 *  14
 *  3 4 17 20 24 27 36
 *  41
 *  7
 *  45
 *  1
 *  0
 *  10
 *
 ******************************************************************************/

#include "scc.h"

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
    KosarajuSharirSCC scc(dg);
    cout << scc.count() << " strong components" << endl;

    // compute list of vertices in each strong component
    Queue<int>* components = new Queue<int>[scc.count()];
    for (auto v = 0; v < dg.V(); v++)
        components[scc.id(v)].enqueue(v);

    // print results
    for (auto i = 0; i < scc.count(); i++) {
        for (auto v : components[i])
            cout << v << " ";
        cout << endl;
    }

    // free the queues
    delete[] components;

    return (0);
}