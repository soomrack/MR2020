#include <iostream>

using namespace std;

void heapify (int *arr, int begin, int end){
    int left = 2*begin+1;
    int right = 2*begin+2;
    if (left > end) return;
    if (right > end) {
        if (arr[begin] < arr[left])
            swap (arr[begin], arr[left]);
        return;
    }

    if (arr[left] > arr[right]) {
        if (arr[begin] < arr[left]) {
            swap (arr[begin], arr[left]);
            heapify (arr, left, end);
            return;
        }
    } else {
        if (arr[begin] < arr[right]) {
            swap (arr[begin], arr[right]);
            heapify (arr, right, end);
            return;
        }
    }
}

void buildHeap (int *arr, int begin, int end){
    for (int i = (end - begin + 1)/2; i >= 0; i--)
        heapify (arr, i, end);
}

void heapSort (int *arr, int begin, int end){
    buildHeap(arr, begin, end);
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
    int a[6] = {3, -4, 11, 0, -15, 2};
    heapSort(a, 0, 5);
    printArray(a,6);
}

