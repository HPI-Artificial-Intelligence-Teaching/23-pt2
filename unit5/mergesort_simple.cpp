#include <iostream>

template <typename T>
T* merge(T* L, int leftCount, T* R, int rightCount) {
    T* result = new T[leftCount + rightCount];
    
    int leftIndex = 0, rightIndex = 0, resultIndex = 0;
    
    // Merge arrays
    while(leftIndex < leftCount && rightIndex < rightCount) {
        if(L[leftIndex] < R[rightIndex])
            result[resultIndex++] = L[leftIndex++];
        else
            result[resultIndex++] = R[rightIndex++];
    }
    
    // Copy remaining elements
    while(leftIndex < leftCount)
        result[resultIndex++] = L[leftIndex++];
    while(rightIndex < rightCount)
        result[resultIndex++] = R[rightIndex++];
    
    return result;
}

template <typename T>
T* mergesort(T* a, int n) {
    if(n < 2) return a; // Base case
    
    int mid = n / 2;
    
    // Split array into two halves
    T* L = new T[mid];
    T* R = new T[n - mid];
    
    for(int i = 0; i < mid; i++)
        L[i] = a[i];
    for(int i = mid; i < n; i++)
        R[i - mid] = a[i];
    
    // Recursively sort two halves
    L = mergesort(L, mid);
    R = mergesort(R, n - mid);
    
    // Merge sorted halves
    T* result = merge(L, mid, R, n - mid);
    
    // Cleanup
    delete[] L;
    delete[] R;
    
    return result;
}

int main() {
    int a[] = {7, 6, 5, 4, 3, 2, 1, 0};
    int n = sizeof(a) / sizeof(a[0]);

    int* sorted = mergesort(a, n);

    for(int i = 0; i < n; i++) {
        std::cout << sorted[i] << " ";
    }
    delete[] sorted;

    return 0;
}
