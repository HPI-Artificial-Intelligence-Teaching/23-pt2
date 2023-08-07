#include <doctest.h>

#include "../src/distances.h"
#include "../src/weighted_struct_digraph.h"
#include "TestAirport.h"

TEST_CASE("A3.1: Distanzmaße") {
    Bag<TestAirport> airports;
    airports.add(TestAirport{3, 10, 20});
    airports.add(TestAirport{2, 3, 4});
    airports.add(TestAirport{1, 1, 1});
    airports.add(TestAirport{0, 0, 0});
    WeightedStructDigraph<TestAirport> g(airports);
    g.add_edge(g.name_of(1), g.name_of(2), 1.0);
    SUBCASE("Euklidische Distanzen") {
        CHECK(euclidean(g, TestAirport{0, 0, 0}, TestAirport{1, 1, 1}) ==
              doctest::Approx(1.41421356237));
        CHECK(euclidean(g, TestAirport{0, 0, 0}, TestAirport{2, 3, 4}) ==
              doctest::Approx(5.0));
    }
    SUBCASE("Geodesische Distanz") {
        CHECK(haversine(g, TestAirport{0, 0, 0}, TestAirport{1, 1, 1}) ==
              doctest::Approx(157.249));
        CHECK(haversine(g, TestAirport{0, 0, 0}, TestAirport{3, 10, 20}) ==
              doctest::Approx(2476.17));
    }
    SUBCASE("Manhattan Distanz") {
        CHECK(manhattan(g, TestAirport{0, 0, 0}, TestAirport{1, 1, 1}) ==
              doctest::Approx(2));
        CHECK(manhattan(g, TestAirport{0, 0, 0}, TestAirport{3, 10, 20}) ==
              doctest::Approx(30));
    }
    SUBCASE("Outdegree Distanz") {
        CHECK(out_degree(g, TestAirport{0, 0, 0}, TestAirport{1, 1, 1}) ==
              doctest::Approx(-1));
        CHECK(out_degree(g, TestAirport{0, 0, 0}, TestAirport{3, 10, 20}) ==
              doctest::Approx(0));
    }
}