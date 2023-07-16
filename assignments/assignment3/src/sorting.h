#ifndef SORTING_H
#define SORTING_H

class Comparator
{
public:
    int compare(int data[], int x, int y) { return data[x] - data[y]; };
};

class CountingComparator
{
protected:
    Comparator &comp;
    int counter;

public:
    void resetCounter() { counter = 0; };
    int getCounter() { return counter; };
    int compare(int data[], int x, int y)
    {
        ++counter;
        return comp.compare(data, x, y);
    };
    CountingComparator(Comparator &comp) : comp(comp), counter(0){};
};

class SortingAlgorithm
{
protected:
    int *data;
    int size;
    CountingComparator &comp;

public:
    void swap(int i, int j);
    virtual void sort(){};
    SortingAlgorithm(int *sortData, int dataSize, CountingComparator &comparator) : data(sortData), size(dataSize), comp(comparator){};
    ~SortingAlgorithm(){};
};

class BubbleSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
};

class MergeSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

protected:
    int *aux;

public:
    void sort() override;
    void split(int l, int r);
    void merge(int l, int r, int halfway);
};

class QuickSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
    int divide(int l, int r);
    void qs(int l, int r);
};

#endif /* SORTING_H */