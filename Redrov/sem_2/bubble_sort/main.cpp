#include <iostream>

void bubble_sort(int* array, size_t size){
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size-1; j++)
        {
            if (array[j] > array[j + 1]){ //swap if next element less than current
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    
}


int main(int argc, char const *argv[])
{
    // some tests
    int arr[7] = {5, 6, 7, 4, 3, 2, 1};

    bubble_sort(arr, 7);

    for (size_t i = 0; i < 7; i++)
    {
        std::cout << arr[i] << ' ';
    }
    
    return 0;
}
