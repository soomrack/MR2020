#include "Sort.h"

void Bubble_sort(int * arr, int n) {
    for(int bub_index = 0; bub_index < n - 1; bub_index++) {
        for(int i = 0; i < n - bub_index - 1; i++) {
            if(arr[i] > arr[i+1]) {
                Swap(&arr[i], &arr[i+1]);
            }
        }
    }
}

void Insertion_sort(int * arr, int n) {
    for(int i = 0; i < n-1; i++) {
        int j = i + 1;
        while(j > 0 && arr[j-1] > arr[j]) {
            Swap(&arr[j],&arr[j-1]);
            j--;
        }
        
    }
}
static void Merge(int * arr, int left, int med, int right) {
    int i1 = left; // index for first (left) subarray
    int i2 = med + 1; // for second (right) subarray
    int index_buf = 0;
    int buf[right-left+1];
    // merge to buffer
    while(i1 < med + 1 && i2 < right + 1) {
        if(arr[i1] < arr[i2]) {
            buf[index_buf] = arr[i1];
            i1++;
        } else {
            buf[index_buf] = arr[i2];
            i2++;
        }
        index_buf++;
    }
    // copy the remaining elements
    while (i1 < med + 1) {
        buf[index_buf] = arr[i1];
        i1++;
        index_buf++;
    }
    while (i2 < right + 1 ) {
        buf[index_buf] = arr[i2];
        i2++;
        index_buf++;
    }
    // copy the buf to the arr
    for(int i = 0; i < index_buf; i++) {
        arr[left] = buf[i];
        left++;
    }
}

void Merge_sort(int * arr, int left, int right) {
    if(left == right) {
        return;
    }
    int med = left + (right - left) / 2;
    Merge_sort(arr,left,med);
    Merge_sort(arr,med+1,right);
    
    Merge(arr,left,med,right);
}
void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Print_array(int * arr, int n) {
    for(int i = 0; i < n; i++ ) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}