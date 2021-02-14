#include "Sort.h"

void testSort (int * arr, int size){
    printArr(arr, size);

    int * arrCopy1 = new int[size];
    int * arrCopy2 = new int[size];
    int * arrCopy3 = new int[size];
    copyArr(arr, arrCopy1, size);
    copyArr(arr, arrCopy2, size);
    copyArr(arr, arrCopy3, size);

    insertionSort(arr, size);
    std::cout << "Insertion sort: ";
    printArr(arr, size);

    bubbleSort(arrCopy1, size);
    std::cout << "Bubble sort: ";
    printArr(arrCopy1, size);

    mergeSort(arrCopy2, size);
    std::cout << "Merge sort: ";
    printArr(arrCopy2, size);

    heapSort(arrCopy3, size);
    std::cout << "Heap sort: ";
    printArr(arrCopy3, size);

    delete [] arrCopy1;
    delete [] arrCopy2;
    delete [] arrCopy3;
    std::cout << std::endl;
}

int main() {
    int arr1[5] = {5, 4, 3, 2, 1};
    testSort(arr1, 5);

    int arr2[10] = {-5, 14, 23, 2, 0, 1, 1, -10, 9, 3};
    testSort(arr2, 10);

    return 0;
}
