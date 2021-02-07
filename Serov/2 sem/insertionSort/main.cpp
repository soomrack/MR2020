#include <iostream>
#include <string.h>

using namespace std;

void insertionSort(int *array, int length){
    for (int sortedIndex = 0; sortedIndex < length-1; sortedIndex ++){
        for (int k = sortedIndex; (array[k+1] < array[k]) && (k!=-1); k--)
            swap(array[k],array[k+1]);
    }
}

void printArray(int *array, int length) {
    for (int k = 0; k < length; k++)
        printf("%d ", array[k]);
}

int main() {
    int a[9] = {25, 17, 0, 4, -5, 16, 333, -22, 1};
    insertionSort(a, 9);
    printArray(a,9);
}
