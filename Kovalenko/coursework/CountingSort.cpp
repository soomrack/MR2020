#include <iostream>
#include <cstdlib>

void CountingSort(int *array, int size, int max_element)
{
    int *counting_array;
    for(int i = 0; i <= max_element + 1; i++)
    {
        counting_array[i] = 0;
    }
    for(int i = 0; i < size; ++i)
    {
        ++counting_array[array[i]];
    }
    int index = 0;
    for(int i = 0; i < max_element + 1; ++i)
    {
        for (int j = 0; j < counting_array[i]; ++j) {
            array[index] = i;
            index++;
        }
    }
}

void CountingSort_Modified(int *array, int size)
{
    int max = INT_MIN, min = INT_MAX;
    for (int i = 0; i < size; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    int *counting_array = new int[max + 1 - min];
    for (int i = 0; i < max + 1 - min; i++) {
        counting_array[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        counting_array[array[i] - min] = counting_array[array[i] - min] + 1;
    }
    int i = 0;
    for (int j = min; j < max + 1; j++) {
        while (counting_array[j-min] != 0) {
            array[i] = j;
            counting_array[j-min]--;
            i++;
        }
    }
}

int main() {
int arr[5000] = {0};
for(int i = 0; i <= 4999; i++)
{
    arr[i] = rand();
}
CountingSort_Modified(arr, 5000);
for(int i = 0; i <= 4999 ; i++)
{
    printf("%d\n", arr[i]);
}
    return 0;
}
