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
void mergesort(T* a, T* aux, int lo, int hi) {
    if (hi <= lo) return;

    int mid = lo + (hi - lo) / 2;
    
    // Recurse on the two halves
    mergesort(a, aux, lo, mid);
    mergesort(a, aux, mid + 1, hi);
    
    // Skip merge if already in order
    if (!(a[mid] > a[mid + 1])) return;

    // Merge results
    merge(a, aux, lo, mid, hi);
}

template <typename T>
void mergesort(T* a, int length) {
    T* aux = new T[length];
    mergesort(a, aux, 0, length - 1);
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
