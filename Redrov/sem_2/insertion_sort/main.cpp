#include "iostream"

void insertion_sort(int* array, size_t size){

    for (int i = 0; i < size; i++)
    {
        for (int j = i; j > 0;  j--)
        {
            if (array[j - 1] < array[j] ) { break; }
            std::swap(array[j], array[j - 1]);
        }
    }
}


int main(int argc, char const *argv[])
{
    int arr[8] = {5, 6, 4, 7, 3, 8, 2, 1};

    insertion_sort(arr, 8);

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << arr[i] << ' ';
    }
    

    return 0;
}
