#include <iostream> 

void insertion_sort(int* array, int length)
{
    for (int i = 1; i < length; i++)        //iterates through 
    {
        for (int j = i; j>0 && array[j-1]>array[j]; j--)    // looks for a A[i]'s place in the sorted part of the list
            std::swap(array[j], array[j-1]);                // by swaps with larger elements - inserts A[i]
    }
}


int main() 
{
    int a[9] = {-1, 5, -1, 25, -5, 33, 789, -22, -11};
    insertion_sort(a, 9);
    
    for (int k = 0; k < 9; k++)
        printf("%d ", a[k]);
}