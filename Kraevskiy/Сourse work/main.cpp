#include <iostream>
using namespace std;

void heapify(int array[], int arr_size, int i)
{
    int largest  = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < arr_size && array[left] > array[largest])
    {
        largest = left;
    }
    if (right < arr_size && array[right] > array[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify (array, arr_size, largest);
    }
}

void heap_sort(int array[], int arr_size)
{
    for (int i = arr_size / 2 - 1; i >= 0; i--)
    {
        heapify(array, arr_size, i);
    }
    for (int i = arr_size - 1; i >= 0; i--)
    {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main()
{
    return 0;
}