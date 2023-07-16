#include "sorting.h"
#include "sorting.cpp"
#include "generator.h"
#include "generator.cpp"
#include <iostream>

void compareQSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateWorstCaseQuicksort(n);
    QuickSort qs = QuickSort(data, n, comp);
    qs.sort();
    std::cout << "QS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

void compareQSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateBestCaseQuicksort(n);
    QuickSort qs = QuickSort(data, n, comp);
    qs.sort();
    std::cout << "QS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

void compareMSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateWorstCaseMergesort(n);
    MergeSort ms = MergeSort(data, n, comp);
    ms.sort();
    std::cout << "MS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

void compareMSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateBestCaseMergesort(n);
    MergeSort ms = MergeSort(data, n, comp);
    ms.sort();
    std::cout << "MS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

void compareBSWorstcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateWorstCaseBubblesort(n);
    BubbleSort bs = BubbleSort(data, n, comp);
    bs.sort();
    std::cout << "BS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

void compareBSBestcase(int n, CountingComparator comp) {
    comp.resetCounter();
    int* data = generateBestCaseBubblesort(n);
    BubbleSort bs = BubbleSort(data, n, comp);
    bs.sort();
    std::cout << "BS, n=" << n << ", counts= " << comp.getCounter() << "\n";
    delete data;
}

/* main entry point for the program */
int main(int argc, char *argv[]) {
    Comparator comp = Comparator();
    CountingComparator comp2 = CountingComparator(comp);

    std::cout << "Comparing worst cases \n";
    compareBSWorstcase(10, comp2);
    compareBSWorstcase(100, comp2);
    compareBSWorstcase(1000, comp2);

    compareQSWorstcase(10, comp2);
    compareQSWorstcase(100, comp2);
    compareQSWorstcase(1000, comp2);

    compareMSWorstcase(10, comp2);
    compareMSWorstcase(100, comp2);
    compareMSWorstcase(1000, comp2);

    std::cout << "Comparing best cases \n";
    compareBSBestcase(10, comp2);
    compareBSBestcase(100, comp2);
    compareBSBestcase(1000, comp2);

    compareQSBestcase(10, comp2);
    compareQSBestcase(100, comp2);
    compareQSBestcase(1000, comp2);

    compareMSBestcase(10, comp2);
    compareMSBestcase(100, comp2);
    compareMSBestcase(1000, comp2);
}