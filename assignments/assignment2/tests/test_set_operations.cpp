#include "doctest.h"
#include "../src/Set.h"
#include "../src/set_operations.cpp"

TEST_CASE("A3.2: Set operations")
{
    Set<int> a = Set<int>();
    Set<int> b = Set<int>();
    Set<int> c = Set<int>();
    SUBCASE("Intersection")
    {
        a.add(1);
        a.add(2);
        a.add(3);
        b.add(2);
        b.add(3);
        b.add(4);
        c.add(2);
        c.add(3);
        CHECK_EQ(intersection(a, b), c);
    }
    SUBCASE("Union")
    {
        a.add(1);
        a.add(2);
        a.add(3);
        b.add(2);
        b.add(3);
        b.add(4);
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        CHECK_EQ(union_(a, b), c);
    }
    SUBCASE("Difference")
    {
        a.add(1);
        a.add(2);
        a.add(3);
        b.add(2);
        b.add(3);
        b.add(4);
        c.add(1);
        CHECK_EQ(difference(a, b), c);
    }
}