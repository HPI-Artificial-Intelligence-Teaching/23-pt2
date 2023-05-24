#include <iostream>

template <typename T>
void merge(T* a, T* aux, int lo, int mid, int hi) {
    // Merge a[lo...mid] with a[mid+1...hi] into aux[lo...hi]
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)               aux[k] = a[j++];
        else if (j > hi)           aux[k] = a[i++];
        else if (a[j] < a[i])      aux[k] = a[j++];
        else                       aux[k] = a[i++];
    }
}

template <typename T>
void mergesort(T* a, T* aux, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    mergesort(aux, a, lo, mid);          // Sort left half into aux
    mergesort(aux, a, mid + 1, hi);      // Sort right half into aux
    merge(a, aux, lo, mid, hi);          // Merge results into a
}

template <typename T>
void mergesort(T* a, int length) {
    T* aux = new T[length];
    for (int i = 0; i < length; i++) {
        aux[i] = a[i];                   // Copy data to aux array
    }
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
