#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "../src/sorting.h"
#include "../src/sorting.cpp"
#include "../src/generator.h"
#include "../src/generator.cpp"

TEST_CASE("A1: Comparator") {
    Comparator* origComp = new Comparator();
    int data[] = {1, 2, 3, 4};
    CHECK(origComp->compare(data, 0, 1) < 0);
}

TEST_CASE("A1: Counting Comparator") {
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    int data[] = {1, 2, 3, 4};
    CHECK(comp->compare(data, 0, 1) < 0);
    CHECK(comp->compare(data, 2, 1) > 0);
    CHECK(comp->compare(data, 3, 2) > 0);
    CHECK(comp->compare(data, 3, 3) == 0);
    CHECK(comp->getCounter() == 4);
    comp->resetCounter();
    CHECK(comp->getCounter() == 0);
}

TEST_CASE("A2: BubbleSort") {
    int* data = new int[10] {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    BubbleSort* sort = new BubbleSort(data, 10, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 45);
}

TEST_CASE("A2: QuickSort") {
    int* data = new int[10] {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    QuickSort* sort = new QuickSort(data, 10, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 41);
}

TEST_CASE("A2: MergeSort") {
    int* data = new int[10] {10,9,8,7,6,4,3,2,1,5};
    Comparator* origComp = new Comparator();
    CountingComparator* comp = new CountingComparator(*(origComp));
    MergeSort* sort = new MergeSort(data, 10, *comp);
    sort->sort();
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == i+1);
    }
    CHECK(comp->getCounter() == 25);
}

TEST_CASE("A3: Generator") {
    int* data = generateSorted(10);
    int* validation = new int[10] {0,1, 2, 3, 4, 5, 6,7,8,9};
    for (int i=0; i<10; ++i) {
        CHECK(data[i] == validation[i]);
    }  
}
