#include "sorting.h"

void SortingAlgorithm::swap(int i, int j) {
    int x = data[i];
    data[i] = data[j];
    data[j] = x;
}

void BubbleSort::sort()
{
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (comp.compare(data, j, j + 1) > 0) {
                swap(j, j + 1);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
};

void MergeSort::split(int lo, int hi)
{
    if (hi <= lo) return;
    int mid = (hi + lo) / 2;
    split(lo, mid);
    split(mid + 1, hi);
    merge(lo, mid, hi);
};

void MergeSort::merge(int lo, int mid, int hi)
{
    if (comp.compare(data, mid+1, mid) > 0) {
        return;
    }
    for (int k = lo; k <= hi; k++) {
        aux[k] = data[k];
    }

    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)               data[k] = aux[j++];
        else if (j > hi)           data[k] = aux[i++];
        else if (comp.compare(aux, j, i) < 0)  data[k] = aux[j++];
        else                       data[k] = aux[i++];
    }
};

void MergeSort::sort()
{
    aux = new int[size];
    split(0, size-1);
};

int QuickSort::divide(int lo, int hi)
{
    int pivot = lo;
    int i = lo + 1;
    int j = hi;
    while (true) {
        while (i <= j && comp.compare(data, i, pivot) <= 0) i++;
        while (i <= j && comp.compare(data, j, pivot) > 0) j--;
        if (i >= j) break;

        swap(i, j);
    }

    swap(lo, j);
    return j;
};

void QuickSort::qs(int lo, int hi)
{
    if (lo < hi)
    {
        int dividor = divide(lo, hi);
        qs(lo, dividor - 1);
        qs(dividor + 1, hi);
    }
};

void QuickSort::sort()
{
    qs(0, size-1);
};