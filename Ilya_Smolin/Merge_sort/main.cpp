#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;

void merge (int32_t * arr, int32_t middle, int32_t left, int32_t right) {
    int32_t iterator1 = 0;
    int32_t iterator2 = 0;

    int32_t result_array[right - left];

    while (left + iterator1 < middle & middle + iterator2 < right)
    {
        if (arr[left + iterator1] < arr[middle + iterator2])
        {
            result_array[iterator1 + iterator2] = arr[left + iterator1];
            iterator1++;
        }
        else
        {
            result_array[iterator1 + iterator2] = arr[middle + iterator2];
            iterator2++;
        }
    }

    while (left + iterator1 < middle)
    {
        result_array[iterator1 + iterator2] = arr[left + iterator1];
        iterator1++;
    }

    while (middle + iterator2 < right)
    {
        result_array[iterator1 + iterator2] = arr[middle + iterator2];
        iterator2++;
    }

    for (int i = 0; i < iterator2 + iterator1; ++i)
    {
        arr[left + i] = result_array[i];
    }
}

void mergeSort ( int32_t * arr, int32_t left, int32_t right)
{
    if (left + 1 >= right)
        return;
    int32_t middle = (left+right) / 2;
    mergeSort (arr, left, middle);
    mergeSort (arr, middle, right);
    merge (arr, middle, left, right);
}





int main() {
    int32_t arr[12] = { 16, 654, 110, 171, 946, 672, 95, 325, 837, 974, 416, 33, };
    mergeSort (arr, 0, 12);
    for (int i = 0; i != sizeof(arr)/sizeof(int32_t); i++)
    {
        cout <<arr[i]<< endl;
    }
}