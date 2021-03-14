#include <iostream>

#include <string>

void swap(int * a, int * b) {
    int t = * a;
    * a = * b;
    * b = t;
}
void insertionSort(int * array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j >= 0; j--) {
            if (array[j] > array[j+1]) {
                swap( & array[j+1], & array[j]);
            }
            else {
                break;
            }

        }
    }
}
int main(int argc, char
    const * argv[]) {
    int array[7] = {4, 3, 2, 1, 7, 6, 5,};
    int size = 7;
    insertionSort(array, size);

    for (int i = 0; i < 7; i++) {
        std::cout << array[i] << ' ';
    }
    return 0;
}