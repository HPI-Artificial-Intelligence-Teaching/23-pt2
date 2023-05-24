#include <iostream>
#include <future>

template <typename T>
void mergesort(T* a, T* aux, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    
    auto f1 = std::async(std::launch::async, mergesort<T>, a, aux, lo, mid);
    auto f2 = std::async(std::launch::async, mergesort<T>, a, aux, mid + 1, hi);
    
    f1.wait();
    f2.wait();
    
    merge(a, aux, lo, mid, hi);
}

template <typename T>
void mergesort(T* a, T* aux, int lo, int hi) {
    if (hi <= lo) return;
    int mid = (hi + lo) / 2;
    mergesort(a, aux, lo, mid);
    mergesort(a, aux, mid + 1, hi);
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

    mergeSort(a, length);

    for (int i = 0; i < length; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
