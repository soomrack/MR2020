#include "Sort.h"
#define TRUE 1
#define FALSE 0

void copyArr(const int * original, int * copy, int size){
    for (int i = 0; i < size; i++){
        copy[i] = original[i];
    }
}

static void merge (int * arr,int middle, int size){
    int i = 0;
    int j = 0;
    int * arrPart1 = new int[middle];
    int * arrPart2 = new int[size - middle];
    copyArr(arr, arrPart1, middle);
    copyArr(&arr[size/2], arrPart2, size - middle);
    for (int k = 0; k < size; k++){
        if (i == middle){
            arr[k] = arrPart2[j];
            j++;
            continue;
        }
        if (j == size - middle){
            arr[k] = arrPart1[i];
            i++;
            continue;
        }
        if (arrPart1[i] < arrPart2[j]){
            arr[k] = arrPart1[i];
            i++;
        } else {
            arr[k] = arrPart2[j];
            j++;
        }
    }
    delete [] arrPart1;
    delete [] arrPart2;
}

static void swap (int * i, int * j){
    int temp = *i;
    *i = *j;
    *j = temp;
}

void insertionSort (int * arr, int size){
    for (int i = 1; i < size; i++){
        int temp = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] > temp){
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }
}

void bubbleSort (int * arr, int size){
    int j = 0;
    int isNeedToSortMore = TRUE;
    while (isNeedToSortMore){
        isNeedToSortMore = FALSE;
        for (int i = 0; i < size - j - 1; i++){
            if (arr[i] > arr[i + 1]){
                swap(&arr[i], &arr[i + 1]);
                isNeedToSortMore = TRUE;
            }
        }
        j++;
    }
}

void mergeSort (int * arr, int size){
    if (size < 2) return;
    int middle = size/2;
    mergeSort(arr, middle);
    mergeSort(&arr[middle], size - middle);
    merge(arr, middle, size);
}

static void heapify (int * arr, int size){
    for (int i = 0; i < size; i++){
        int currentIndex = i;
        while (currentIndex != 0){
            int parentIndex = (currentIndex - 1)/2;
            if (arr[parentIndex] >= arr[currentIndex]) break;
            swap(&arr[parentIndex], &arr[currentIndex]);
            currentIndex = parentIndex;
        }
    }
}

void heapSort (int * arr, int size){
    heapify(arr, size);
    for (int i = size - 1; i > 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i);
    }
}

void printArr(int * arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}
