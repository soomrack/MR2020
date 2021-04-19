#include <iostream>
#include <algorithm>
#include <vector> //used for the sake of simplicity
using namespace std;
 
 
void b_sort(int sarray[], int array_size) 
{
    int rows = 10;
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[array_size+1];
    }
    for (int x = 0; x < 10; x++) arr[x][array_size] = 0;
    // main loop for each digit position
    for (int digit = 1; digit <= 1000000000; digit *= 10) 
    {
        // array to bucket
        for (int i = 0; i < array_size; i++) 
        {
            // get the digit 0-9
            int dig = (sarray[i] / digit) % 10;
            // add to bucket and increment count
            arr[dig][arr[dig][array_size]++] = sarray[i];
        }
        // bucket to array
        int idx = 0;
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < arr[x][array_size]; y++)
                sarray[idx++] = arr[x][y];
            // reset the internal bucket counters
            arr[x][array_size] = 0;
        }
    }
    delete arr;
}

int main()
{
    int sarray[10] = { 14,17,2,2,211,80,5,4,9,52 };
    b_sort(sarray,10);
    int a = 10;
    a++;
}