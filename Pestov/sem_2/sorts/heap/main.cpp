#include <iostream>

// Heap - array, array[l] - parent, left - 2l + 1, right - 2l + 2 
 


void heapify(int arr[], int n, int i)
{
    int largest = i;   
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        int t = arr[i];
        arr[i] = arr[largest];
        arr[largest] = t;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>=0; i--)
    {

        int t = arr[0];
        arr[0] = arr[i];
        arr[i] = t;

        heapify(arr, i, 0);
    }
}



int main(int argc, char const *argv[])
{
    int arr1[] = {1, 2, 13, 3, 5, 7, 25, 15, 12, 17, 19};
    int n = sizeof(arr1)/sizeof(arr1[0]);

    heapSort(arr1, n);

    for (int i=0; i<n; ++i)
        std::cout << arr1[i] << " ";
    std::cout << "\n";
    return 0;
}

