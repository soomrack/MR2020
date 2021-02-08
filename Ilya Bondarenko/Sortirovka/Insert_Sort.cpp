#include <iostream>

using namespace std;

void insertionSort(int* array, int size) {
    for (int sorted_Index = 0; sorted_Index != size - 1; sorted_Index++) {
        int counter = sorted_Index;
        while ((array[counter - 1] > array[counter]) && (counter > 1)) {
        swap(array[counter-1], array[counter ]);
        counter--;
            }
    }
}

int main() {
    int a[10] = { 5, 1, 10, 4, 3, 16, 33, 21, 11, 19 };
    insertionSort(a, 10);
}