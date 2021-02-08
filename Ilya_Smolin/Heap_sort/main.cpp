#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;

void heapify (int32_t * arr, int32_t begin, int32_t end)
{
    int32_t left = 2 * begin + 1;
    int32_t right = left + 1;
    int32_t largest = begin;

    if (left > end) return;

    if (right > end)
    {
        if (left > begin)
        {
            swap(arr[begin], arr[left]);
        }
        return;
    }

    if (arr[left] > arr[largest])
        largest = left;

    if (arr[right] > arr[largest])
        largest =   right;

    if (largest != begin)
    {
        swap(arr[begin], arr[largest]);
        heapify(arr, largest, end);
    }
}

void build_heap (int32_t * arr, uint32_t size)
{
    for (int k = size / 2 - 1; k >= 0; k--)
        heapify(arr, k, size - 1);
}


void heap_sort ( int32_t * arr, uint32_t size)
{
    build_heap(arr, size);

    for (uint32_t k = size-1; k > 1; k--)
    {
        swap(arr[0], arr[k]);
        heapify(arr, 0, k-1);
    }
}




int main() {
    int32_t arr[12] = { 1116, 654, 110, 171, 946, 672, 95, 325, 837, 974, 416, 3333, };
    heap_sort (arr, sizeof(arr)/sizeof(int32_t));
    for (int i = 0; i != sizeof(arr)/sizeof(int32_t); i++)
    {
        cout <<arr[i]<< endl;
    }
}
