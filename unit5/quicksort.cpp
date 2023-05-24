#include <iostream>

template<typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
int partition(T a[], int lo, int hi) {
    T pivot = a[lo];  // first element as pivot
    int i = lo + 1;
    int j = hi;
    while (true) {
        while (i <= j && a[i] <= pivot) i++;
        while (i <= j && a[j] > pivot) j--;
        if (i >= j) break;

        swap(a[i], a[j]);
    }

    swap(a[lo], a[j]);
    return j;
}

template<typename T>
void quicksort(T a[], int lo, int hi) {
    if (lo < hi) {
        int p = partition(a, lo, hi);
        quicksort(a, lo, p - 1);
        quicksort(a, p + 1, hi);
    }
}

template<typename T>
void shuffle(T a[], int n) {
    // set the random seed to current time
    srand(time(0)); 
    for (int i = 0; i < n; i++) {
        int r = i + rand() % (n - i); 
        swap(a[i], a[r]);
    } 
}

template<typename T>
void quicksort(T a[], int n) {
    shuffle(a, n);
    quicksort(a, 0, n-1);
}

int main() {
    int a[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(a)/sizeof(a[0]);


    quicksort(a, 0, n-1);

    for(int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    // shuffle before repeated sorting
    quicksort(a, n);

    for(int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    return 0;
}
