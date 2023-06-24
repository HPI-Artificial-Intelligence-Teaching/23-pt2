/******************************************************************************
 *
 * Computes the topological ordering of a DAG which runs in O(E + V) time.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./topological_test ../data/jobs.txt "/"
 *  Calculus
 *  Linear Algebra
 *  Introduction to CS
 *  Advanced Programming
 *  Algorithms
 *  Theoretical CS
 *  Artificial Intelligence
 *  Robotics
 *  Machine Learning
 *  Neural Networks
 *  Databases
 *  Scientific Computing
 *  Computational Biology
 *
 ******************************************************************************/

#include "topological.h"

#include <iostream>
#include <string>

#include "symbol_digraph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // parameter check
    if (argc != 3) {
        cerr << "Invalid number of arguments. Call with filename and delimiter." << endl;
        return (1);
    }

    // read the symbol graph from the file
    SymbolDigraph sdg(argv[1], argv[2][0]);
    Topological topological(*sdg.get_graph());

    // read a string as input
    for (auto v : topological.order())
        cout << sdg.name_of(v) << endl;

    return (0);
}