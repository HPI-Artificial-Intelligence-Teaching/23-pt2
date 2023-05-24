#include <iostream>

template <typename T>
void shellSort(T arr[], int n) {
    // Starte mit einer großen Lücke und reduziere sie
    for (int h = n / 2; h > 0; h /= 2) {
        // Führe eine gapped Insertion Sort für diese Lücke durch
        for (int i = h; i < n; i++) {
            T temp = arr[i];
            int j;

            for (j = i; j >= h && arr[j - h] > temp; j -= h) {
                arr[j] = arr[j - h];
            }

            arr[j] = temp;
        }
    }
}

template <typename T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Unsorted array: ";
    printArray(arr, n);

    shellSort(arr, n);

    std::cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}
