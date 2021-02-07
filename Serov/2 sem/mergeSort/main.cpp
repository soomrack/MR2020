#include <iostream>

void mergeSort(int *array, int start, int end, int *buffer) {

    if (start == end)
        return;
    int mid = (start + end) / 2;
    mergeSort(array, start, mid, buffer);
    mergeSort(array, mid + 1, end, buffer);

    for (int k = start; k <= end; k++)
        buffer[k] = array[k];

    int rightIndex = mid + 1;
    int leftIndex  = start;
    int arrayIndex = start;
    while ((leftIndex <= mid) && rightIndex <= end){

        if (buffer[leftIndex] <= buffer[rightIndex]){
            array[arrayIndex] = buffer[leftIndex];
            arrayIndex ++;
            leftIndex ++;
        }
        else{
            array[arrayIndex] = buffer[rightIndex];
            arrayIndex ++;
            rightIndex ++;
        }
    }

    if (leftIndex > mid){
        while (rightIndex <= end){
            array[arrayIndex] = buffer[rightIndex];
            arrayIndex ++;
            rightIndex ++;
        }
    }

    if (rightIndex > end){
        while (leftIndex <= mid){
            array[arrayIndex] = buffer[leftIndex];
            arrayIndex ++;
            leftIndex ++;
        }
    }
}

void printArray(int *array, int length) {
    for (int k = 0; k < length; k++)
        printf("%d ", array[k]);
}

int main(){
    int buffer[9] = {0};
    int a[9] = {25, 17, 0, 4, -5, 16, 333, -22, 11};
    mergeSort(a, 0, 8, buffer);
    printArray(a,9);
}