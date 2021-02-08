#include <iostream>
#include <string.h>

using namespace std;

void bubbleSort (int* array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-1; j++) {
            if (array[j] > array[j + 1]) {
                int b = array[j];
                array[j] = array[j + 1];
                array[j + 1] = b;
            }
        }
    }
}
int main() {
    int array[6] = {6, 5, 4, -2, 3, 1};
    bubbleSort(array, 6);
    for (int i = 0; i < 6; i++) {
        cout << array[i] << " ";
    }
    return 0;
}
