// HeapSort.cpp
#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
private:
    void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    void sort(vector<int>& arr) {
        int n = arr.size();

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    void printArray(const vector<int>& arr) {
        for (int i : arr)
            cout << i << " ";
        cout << endl;
    }
};

int main() {
    HeapSort heapSort;
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    cout << "Original array: ";
    heapSort.printArray(arr);
    
    heapSort.sort(arr);
    
    cout << "Sorted array: ";
    heapSort.printArray(arr);

    return 0;
}