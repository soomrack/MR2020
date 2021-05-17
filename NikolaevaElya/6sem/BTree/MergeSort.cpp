#include <iostream>
using namespace std;
 
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];// Create temp arrays
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
        
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    // Merge the temp arrays back into arr[l..r]
    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is right index of the sub-array of arr to be sorted */
void mergeSort(int arr[],int l,int r) {
    if(l>=r) {
        return;
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}
 
void printArray(int A[], int size) {// Function to print an array
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
}
 
int main()
{
    int arr[] = { 64, -3, 80, 5, 10, 9 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Given array is \n";
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    cout << "\nSorted array is \n";
    printArray(arr, arr_size);
    return 0;
}