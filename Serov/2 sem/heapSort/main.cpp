#include <iostream>

using namespace std;

void heapify (int *arr, int start, int end){
    int left = 2*start+1;
    int right = 2*start+2;
    if (left > end) return;
    if (right > end) {
        if (arr[start] < arr[left])
            swap (arr[start], arr[left]);
        return;
    }

    if (arr[left] > arr[right]) {
        if (arr[start] < arr[left]) {
            swap (arr[start], arr[left]);
            heapify (arr, left, end);
            return;
        }
    } else {
        if (arr[start] < arr[right]) {
            swap (arr[start], arr[right]);
            heapify (arr, right, end);
            return;
        }
    }
}

void buildHeap (int *arr, int start, int end){
    int length = end - start + 1;
    for (int i = length/2; i >= 0; i--)
        heapify (arr, i, end);
}

void heapSort (int *arr, int start, int end){
    buildHeap(arr, start, end);
    for (int k = end; k >= 1; k--){
        swap(arr[0], arr[k]);
        heapify(arr, 0, k - 1);
    }
}

void printArray (int *array, int length) {
    for (int k = 0; k < length; k++)
        printf("%d ", array[k]);
}

int main() {
    int a[9] = {25, 17, 0, 4, -5, 16, 333, -22, 11};
    heapSort(a, 0, 8);
    printArray(a,9);
}
