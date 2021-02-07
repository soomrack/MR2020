#include <iostream>

using namespace std;

void BubbleSort(int *a, int N) {
    for (int sorted_index = N - 1; sorted_index != 0; sorted_index--){
        for (int k = 0; k < sorted_index; k++) {
            if (a[k] > a[k + 1])
                swap(a[k], a[k + 1]);
        }
    }
}

void PrintArray (int *A, int length){
    for (int k = 0; k<length; k++ )
        printf("%d ", A[k]);
}

int main() {
    int A[6] = {5, 2, 1, 4, 6, 3};
    BubbleSort(A, 6);
    PrintArray(A, 6);
}
