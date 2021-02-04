#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;

void sort ( int32_t * arr, uint32_t size)
{
    if (size <= 1)
        return;
    for (int sorted_index = 0;
         sorted_index != size-1;
         sorted_index ++)
    {
        int k = sorted_index+1;
        while (arr[k-1] > arr[k] & k > 0)
        {
            swap(arr[k], arr[k-1]);
            k--;
        }
    }
}





int main() {
    int32_t arr[12] = { 16, 654, 110, 171, 946, 672, 95, 325, 837, 974, 416, 33, };
    sort (arr, sizeof(arr)/sizeof(int32_t));
    for (int i = 0; i != sizeof(arr)/sizeof(int32_t); i++)
    {
        cout <<arr[i]<< endl;
    }
}