#include "iostream"

void merge_sort(int* array, size_t size){
    
}

int main(int argc, char const *argv[])
{
    int arr[8] = {5, 6, 4, 7, 3, 8, 2, 1};

    merge_sort(arr, 8);

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << arr[i] << ' ';
    }
    
    return 0;
}
