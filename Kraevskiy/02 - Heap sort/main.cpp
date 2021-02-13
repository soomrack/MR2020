#include <iostream>

void Swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Print_array (int array[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d  ", array[i]);
    printf("\n");
}

void Heapify(int arr[], int arr_size, int i)
{
    int largest  = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < arr_size && arr[left] > arr[largest ])
    {
        largest  = left;
    }
    if (right < arr_size && arr[right] > arr[largest ])
    {
        largest  = right;
    }
    if (largest  != i)
    {
        Swap (&arr[i], &arr[largest ]);
        Heapify (arr, arr_size, largest);
    }
}

void Heap_sort(int arr[], int arr_size)
{
    for (int i = arr_size / 2 - 1; i >= 0; i--)
    {
        Heapify(arr, arr_size, i);
    }
    for (int i = arr_size - 1; i >= 0; i--)
    {
        Swap (&arr[0], &arr[i]);
        Heapify(arr, i, 0);
    }
}


int main()
{
    int testArray1[10] = {5, 4, 2, 5, 6, 1, 6, 9, 3, 10};
    Heap_sort(testArray1, 10);
    Print_array(testArray1, 10);

    return 0;
}