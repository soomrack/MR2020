#include <iostream>
#include <time.h> 
#include <vector>

using namespace std;

void sort(int parray[], int array_size)
{
    int rows = 10;
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++)
        arr[i] = new int[array_size + 1];
    for (int x = 0; x < 10; x++) arr[x][array_size] = 0;
    // main loop for each digit position
    for (int digit = 1; digit <= 1000000000; digit *= 10)
    {
        // array to bucket
        for (int i = 0; i < array_size; i++)
        {
            // get the digit 0-9
            int dig = (parray[i] / digit) % 10;
            // add to bucket and increment count
            arr[dig][arr[dig][array_size]++] = parray[i];
        }
        // bucket to array
        int idx = 0;
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < arr[x][array_size]; y++)
                parray[idx++] = arr[x][y];
            // reset the internal bucket counters
            arr[x][array_size] = 0;
        }
    }
    delete arr;
}


void bucketsort(int origin_array[], int array_size)
{
    //divide array into ng=egative and positive
    int* negative_array = new int[array_size];
    int negative_array_counter = 0;
    int* positive_array = new int[array_size];
    int positive_array_counter = 0;
    for (int i = 0; i < array_size; i++)
    {
        if (origin_array[i] >= 0)
            positive_array[positive_array_counter++] = origin_array[i];
        else
            negative_array[negative_array_counter++] = -origin_array[i];
    }
    sort(negative_array, negative_array_counter);
    for (int i = negative_array_counter - 1, j = 0; i >= 0; j++, i--)
        origin_array[i] = -negative_array[j];
    sort(positive_array, positive_array_counter);
    for (int i = negative_array_counter, j = 0; i < array_size; j++, i++)
        origin_array[i] = positive_array[j];
}

int main()
{
    const int num = 20000;
    int sarray[num];
    clock_t start = clock();
    bucketsort(sarray, num);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
}