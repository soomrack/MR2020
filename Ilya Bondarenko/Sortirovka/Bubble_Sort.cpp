#include <iostream>

using namespace std;

void bubbleSort(int* array, int length) {
    for (int sorted_index = length - 1; sorted_index > 0; sorted_index--) {
        for (int pointer = 0; pointer < sorted_index; pointer++) {
            if (array[pointer] > array[pointer+1])
                swap(array[pointer], array[pointer+1]);
        }
    }
}

int main() {
    int a[10] = { 5, 7, 10, 44, 52, 76, 3, 2, 1 };
    bubbleSort(a, 10);
}