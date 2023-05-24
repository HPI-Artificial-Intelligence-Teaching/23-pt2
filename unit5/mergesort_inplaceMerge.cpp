#include <iostream>

template <typename T>
void inplaceMerge(T a[], int low, int mid, int high) {
    int start = low;
    int end = mid + 1;
  
    // Wenn das direkte linke Element kleiner oder gleich 
    // ist als das rechte direkte Element, dann sind die Elemente sortiert
    if (a[mid] <= a[end]) {
        return;
    }
  
    // Zwei Zeiger zum Traversieren der beiden Hälften
    while (start <= mid && end <= high) {
  
        // Wenn das Element am Anfang der linken Seite kleiner
        // ist als das am Anfang der rechten Seite, inkrementiere den Zeiger
        if (a[start] <= a[end]) {
            start++;
        } else {
            T value = a[end];
            int index = end;
  
            // Verschieben aller Elemente um eins nach rechts, bis das 
            // rechte Element an der richtigen Stelle ist
            while (index != start) {
                a[index] = a[index - 1];
                index--;
            }
            a[start] = value;
  
            // Update der Indizes für weiteres Durchgehen
            start++;
            mid++;
            end++;
        }
    }
}

template <typename T>
void inplaceMergeSort(T a[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        inplaceMergeSort(a, low, mid);
        inplaceMergeSort(a, mid + 1, high);
        inplaceMerge(a, low, mid, high);
    }
}

int main() {
    int a[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(a) / sizeof(a[0]);

    inplaceMergeSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}
