#include <iostream>
#include <vector>

void countingSort(int arr[], int n) {
    int max_val = *std::max_element(arr, arr + n);
    int min_val = *std::min_element(arr, arr + n);

    int range = max_val - min_val + 1; 

    std::vector<int> count(range), output(n);
    
    for(int i = 0; i < n; i++)
        count[arr[i] - min_val]++;

    for(int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for(int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }

    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    countingSort(arr, n);

    for(int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}
