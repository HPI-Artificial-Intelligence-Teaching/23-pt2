/******************************************************************************
 *
 * Compute preorder and postorder for a digraph that runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./dfo_test ../data/tinyDAG.txt
 *     v  pre post
 *  --------------
 *     0   0   8
 *     1   3   2
 *     2   9  10
 *     3  10   9
 *     4   2   0
 *     5   1   1
 *     6   4   7
 *     7  11  11
 *     8  12  12
 *     9   5   6
 *    10   8   5
 *    11   6   4
 *    12   7   3
 *  Preorder:  0 5 4 1 6 9 11 12 10 2 3 7 8
 *  Postorder: 4 5 1 12 11 10 9 6 0 3 2 7 8
 *  Reverse postorder: 8 7 2 3 0 6 9 10 11 12 1 5 4
 *
 ******************************************************************************/

#include "dfo.h"

#include <fstream>
#include <iomanip>
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
    DepthFirstOrder dfo(dg);
    cout << "   v  pre post" << endl
         << "--------------" << endl;
    for (auto v = 0; v < dg.V(); v++)
        cout << setw(4) << v << setw(4) << dfo.preorder(v) << setw(4) << dfo.postorder(v) << endl;

    cout << "Preorder:  ";
    for (auto v : dfo.preorder())
        cout << v << " ";
    cout << endl;

    cout << "Postorder: ";
    for (auto v : dfo.postorder())
        cout << v << " ";
    cout << endl;

    cout << "Reverse postorder: ";
    for (auto v : dfo.reverse_order())
        cout << v << " ";
    cout << endl;

    return (0);
}