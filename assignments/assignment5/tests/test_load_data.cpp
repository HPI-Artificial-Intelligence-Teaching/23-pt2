#include <doctest.h>

#include "../src/load_airports.cpp"

TEST_CASE("A1.2: Load Data") {
    CHECK_NOTHROW(load_data("../data/airports.csv", "../data/routes.csv"));
    auto sdg = load_data("../data/airports.csv", "../data/routes.csv");

    // check that number of airports is correct
    CHECK(sdg->get_graph()->V() == 7698);

    // check that number of routes is correct
    CHECK(sdg->get_graph()->E() == 66299);
}