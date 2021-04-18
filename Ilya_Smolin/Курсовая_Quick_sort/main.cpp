#include <chrono>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>

void sort( int32_t * arr, uint32_t size )
{
    if (size > 1)
    {
        int32_t left = 0;
        int32_t right = size - 1;
        int32_t pivot = arr[rand() %size];

        while (left <= right)
        {
            while (arr[left] < pivot)
                left++;
            while (arr[right] > pivot)
                right--;
            if (left <= right)
            {
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
                left++;
                right--;
            }
        }

        if (right > 0)
            sort(arr, right + 1);

        if (right < size - 1)
            sort(&arr[right + 1], size - 1 - right);
    }
}

int main()
{
    int32_t ar[100000]= {0};
    for (int & i : ar)
    {
        i = rand();
    }
    auto begin = std::chrono::steady_clock::now();
    sort(ar, sizeof(ar)/sizeof(int32_t));
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ns\n";
}