#include "generator.h"

void swap(int* data, int i, int j)
{
    int x = data[i];
    data[i] = data[j];
    data[j] = x;
}

int* generateSorted(int n)
{
    int *out = new int[n];
    for (auto i = 0; i < n; i++)
    {
        out[i] = i;
    }
    return out;
};

void merge(int* data, int* left, int* right, int size, int m) {
    int i,j;
    for (i=0; i<m; ++i) {
        data[i] = left[i];
    }
    for (j=0; j<size-m; ++j) {
        data[i] = right[j];
        ++i;
    }
}

void separate(int* data, int size) {
    if (size == 1) {
        return;
    }
    if (size == 2) {
        int x = data[0];
        data[0] = data[1];
        data[1] = x;
        return;
    }
    int i=0,j=0;
    int m = (size+1)/2;
    int* left = new int[m];
    int* right = new int[size-m];

    for (i=0;i<size;i=i+2) {
        left[j]=data[i];
        ++j;
    }

    j=0;
    for (i=1;i<size;i=i+2) {
        right[j]=data[i];
        ++j;
    }
    separate(left, m);
    separate(right, size-m);
    merge(data, left, right, size, m);
}

int* generateWorstCaseBubblesort(int n)
{
    int *out = new int[n];
    for (auto i = 0; i < n; i++)
    {
        out[i] = n-(i+1);
    }
    return out;
};

int* generateWorstCaseMergesort(int n)
{
    int* sorted = generateSorted(n);
    separate(sorted, n);
    return sorted;
};

int* generateWorstCaseQuicksort(int n)
{
    return generateSorted(n);
};

int* generateBestCaseBubblesort(int n) {
    return generateSorted(n);
}

int* generateBestCaseMergesort(int n) {
    return generateSorted(n);
}

void rearrange(int* data, int lo, int hi) {
    if (lo == hi) {
        return;
    }
    if (lo == hi-1) {
        return;
    }
    int half = (hi+lo)/2;
    swap(data, lo, half);
    rearrange(data, lo+1, half);
    rearrange(data, half+1, hi);
}

int* generateBestCaseQuicksort(int n) {
    int* data = generateSorted(n);
    rearrange(data, 0, n-1);
    return data;
}