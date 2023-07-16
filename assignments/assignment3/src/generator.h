#ifndef GENERATOR_H
#define GENERATOR_H

void swap(int* data, int i, int j);

void merge(int* data, int* left, int* right, int size, int m);
void separate(int* data, int size);
int* generateSorted(int n);

int* generateWorstCaseMergesort(int n);
int* generateWorstCaseQuicksort(int n);
int* generateWorstCaseBubblesort(int n);
int* generateBestCaseMergesort(int n);
int* generateBestCaseQuicksort(int n);
int* generateBestCaseBubblesort(int n);

#endif /* GENERATOR_H */