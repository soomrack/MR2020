#include <iostream>
void Merge(int *A, int first, int last, int *buff) {
    int middle = (first + last) / 2;
    int leftStart = first;
    int rightStart = middle + 1;
    for (int j = first; j <= last; j++)
        if ((leftStart <= middle) && ((rightStart > last) || (A[leftStart] < A[rightStart]))) {
            buff[j] = A[leftStart];
            leftStart++;
        } else {
            buff[j] = A[rightStart];
            rightStart++;
        }
    for (int j = first; j <= last; j++) A[j] = buff[j];
}

void MergeSort(int *A, int first, int last, int *buff)
{
    if (first<last)
    {
        MergeSort(A, first, (first+last)/2, buff);
        MergeSort(A, (first+last)/2+1, last, buff);
        Merge(A, first, last, buff);
    }
}

void PrintArray (int *A, int length){
    for (int k = 0; k<length; k++ )
        printf("%d ", A[k]);
}

int main() {
    int buff[6] = {0};
    int A[6] = {5, 2, 1, 4, 6, 3};
    MergeSort(A, 0, 5, buff);
    PrintArray(A, 6);
}
