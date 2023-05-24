#include <iostream>

template <typename T>
void merge(T* a, T* aux, int lo, int mid, int hi) {
    // Copy data to aux array
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // Merge back to a[]
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)               a[k] = aux[j++];
        else if (j > hi)           a[k] = aux[i++];
        else if (aux[j] < aux[i])  a[k] = aux[j++];
        else                       a[k] = aux[i++];
    }
}

template <typename T>
void mergesort(T* a, int length) {
    T* aux = new T[length];
    for (int sz = 1; sz < length; sz = sz+sz) { // sz: subarray size
        for (int lo = 0; lo < length - sz; lo += sz + sz) {
            // Merge subarrays a[lo..lo+sz-1] & a[lo+sz..lo+sz+sz-1]
            int mid = lo + sz - 1;
            int hi = std::min(lo + sz + sz - 1, length - 1);
            merge(a, aux, lo, mid, hi);
        }
    }
    delete[] aux;
}

int main() {
    int a[] = {7, 6, 5, 4, 3, 2, 1, 0};
    int length = sizeof(a) / sizeof(a[0]);

    mergesort(a, length);

    for (int i = 0; i < length; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
