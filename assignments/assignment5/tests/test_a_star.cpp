#include <doctest.h>

#include "../src/a_star.h"
#include "../src/distances.h"
#include "../src/vlib/edge.h"
#include "../src/weighted_struct_digraph.h"
#include "TestAirport.h"

TEST_CASE("A2: A* Algorithm") {
    // construct a lattice graph with only one smallest path
    Bag<TestAirport> airports;
    airports.add(TestAirport{8, 3.0, 3.0});
    airports.add(TestAirport{7, 2.0, 3.0});
    airports.add(TestAirport{6, 1.0, 3.0});
    airports.add(TestAirport{5, 3.0, 2.0});
    airports.add(TestAirport{4, 2.0, 2.0});
    airports.add(TestAirport{3, 1.0, 2.0});
    airports.add(TestAirport{2, 3.0, 1.0});
    airports.add(TestAirport{1, 2.0, 1.0});
    airports.add(TestAirport{0, 1.0, 1.0});

    WeightedStructDigraph<TestAirport> sdg(airports);
    Bag<Edge> edges;
    edges.add(Edge(0, 1, 1.0));
    edges.add(Edge(0, 3, 10.0));
    edges.add(Edge(1, 2, 10.0));
    edges.add(Edge(1, 4, 1.0));
    edges.add(Edge(2, 5, 10.0));
    edges.add(Edge(3, 4, 10.0));
    edges.add(Edge(3, 6, 10.0));
    edges.add(Edge(4, 5, 1.0));
    edges.add(Edge(4, 7, 10.0));
    edges.add(Edge(5, 8, 1.0));
    edges.add(Edge(6, 7, 10.0));
    edges.add(Edge(7, 8, 10.0));
    for (auto e : edges)
        sdg.add_edge(airports[e.from()], airports[e.to()], e.weight());

    SUBCASE("Path exists") {
        // test that a path from top left to bottom right exists
        // and is 5 long (3 itermidiate nodes + start + end)
        Bag<TestAirport> p = a_star<TestAirport>(sdg, airports[0], airports[8],
                                                 euclidean<TestAirport>);
        REQUIRE(p.size() == 5);
        // check that start and end point are right
        CHECK(p[0] == airports[0]);
        CHECK(p[1] == airports[1]);
        CHECK(p[2] == airports[4]);
        CHECK(p[3] == airports[5]);
        CHECK(p[4] == airports[8]);
    }
    SUBCASE("Path does not exist") {
        Bag<TestAirport> p =
            a_star<TestAirport>(sdg, airports[0], TestAirport{11, 4.0, 4.0},
                                euclidean<TestAirport>);
        CHECK(p.size() == 0);
    }
}