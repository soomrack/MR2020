#include <stdio.h>

void bubble_sort (int *arr, int size) {
    for (int i = size - 1; i != 0; i--) {
        for (int n = 0; n < i; n++) {
            if (arr[n] > arr[n + 1]) {
                int m = arr[n];
                arr[n] = arr[n + 1];
                arr[n + 1] = m;
            }
        }
    }
}

void insertion_sort (int *arr, int size){
    for (int i = 0; i != size - 1; i++){
        int n = i + 1;
        while (n > 0 && arr[n - 1] > arr[n]){
            int m = arr[n];
            arr[n] = arr[n - 1];
            arr[n - 1] = m;
            n--;
        }
    }
}

void merge (int * arr, int middle, int left, int right) {
    int iterator1 = 0;
    int iterator2 = 0;
    int result_array[right - left];
    while (left + iterator1 < middle & middle + iterator2 < right) {
        if (arr[left + iterator1] < arr[middle + iterator2]) {
            result_array[iterator1 + iterator2] = arr[left + iterator1];
            iterator1++;
        }
        else {
            result_array[iterator1 + iterator2] = arr[middle + iterator2];
            iterator2++;
        }
    }
    while (left + iterator1 < middle) {
        result_array[iterator1 + iterator2] = arr[left + iterator1];
        iterator1++;
    }
    while (middle + iterator2 < right) {
        result_array[iterator1 + iterator2] = arr[middle + iterator2];
        iterator2++;
    }
    for (int i = 0; i < iterator2 + iterator1; ++i) {
        arr[left + i] = result_array[i];
    }
}

void merge_sort ( int *arr, int left, int right)
{
    if (left + 1 >= right)
        return;
    int middle = (left+right) / 2;
    merge_sort (arr, left, middle);
    merge_sort (arr, middle, right);
    merge (arr, middle, left, right);
}

int main() {
    return 0;
}
