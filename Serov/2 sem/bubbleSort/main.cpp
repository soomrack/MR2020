#include <iostream>
#include <string.h>

using namespace std;

void bubbleSort (int *array, int length){
    for (int sortedIndex = length-1; sortedIndex > 0; sortedIndex --){
        for (int k = 0; k<sortedIndex; k++ ){
            if (array[k+1]<array[k])
                swap(array[k+1],array[k]);
        }
    }
}

void printArray(int *array, int length) {
    for (int k = 0; k < length; k++)
        printf("%d ", array[k]);
}

int main() {
    int a[9] = {25, 17, 0, 4, -5, 16, 333, -22, 11};
    bubbleSort(a, 9);
    printArray(a,9);
}
