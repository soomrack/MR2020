#include <iostream>

using namespace std;

void InsertionSort (int* a, int N) {
    for (int sorted_index = 1; sorted_index != N; sorted_index++) {
        int k = sorted_index;
        while ((a[k - 1] > a[k]) && (k > 0)){
            swap(a[k - 1], a[k]);
            k--;
        }
    }
}

void PrintArray (int *A, int length){
    for (int k = 0; k<length; k++ )
        printf("%d ", A[k]);
}

int main() {
    int A[6] = {5, 2, 1, 4, 6, 3};
    InsertionSort(A, 6);
    PrintArray(A, 6);
}