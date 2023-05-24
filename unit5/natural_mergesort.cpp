#include <iostream>
#include <vector>

template <typename T>
void merge(T* a, int low, int mid, int high) {
    int i = low, j = mid + 1;
    std::vector<T> aux(a + low, a + high + 1);

    for (int k = low; k <= high; k++) {
        if (i > mid)               a[k] = aux[j++ - low];
        else if (j > high)         a[k] = aux[i++ - low];
        else if (aux[j - low] < aux[i - low])  a[k] = aux[j++ - low];
        else                       a[k] = aux[i++ - low];
    }
}

template <typename T>
void naturalMergesort(T* a, int length) {
    int low = 0, mid, high;

    while (low < length - 1) {
        while (low < length - 1 && a[low] <= a[low + 1]) low++;
        mid = low;

        if (mid < length - 1) {
            while (low < length - 1 && a[low] > a[low + 1]) low++;
            high = low;

            merge(a, low - high, mid, high);
        }

        low++;
    }
}

int main() {
    int a[] = {7, 6, 5, 4, 3, 2, 1, 0};
    int length = sizeof(a) / sizeof(a[0]);

    naturalMergesort(a, length);

    for (int i = 0; i < length; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
