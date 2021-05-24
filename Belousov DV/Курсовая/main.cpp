#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

void Sort ( int32_t * array, uint32_t size)
{
    if (size <= 1)
        return;
    for (int sorted_index = 0; sorted_index != size-1; sorted_index ++)
    {
        int k = sorted_index+1;
        while (array[k-1] > array[k] & k > 0)
        {
            swap(array[k], array[k-1]);
            k--;
        }
    }
}

void Print_Array ( int32_t * array, uint32_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ",array[i]);
    }
}


int main()
{
    int32_t a[100] = {};

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        a[i] = rand();
    }
    auto begin = chrono::steady_clock::now();
    Sort (a, sizeof(a)/sizeof(int32_t));
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ns\n";
    Print_Array(a,sizeof(a)/sizeof(int32_t));
}