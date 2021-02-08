#include <iostream>

using namespace std;

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    { cout << array[i] << " ";
    }
    cout << endl;
}

void insertion_sort(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int j = i + 1;
        while ((j > 0) && (array[j] < array[j - 1]))
        {
            int temp = array[j - 1];
            array[j - 1] = array[j];
            array[j] = temp;
            j--;
        }
    }
}
int main()
{
    int array[8] = { 6,9,23,2,12,-5,-1,5 };
    insertion_sort(array,8);
    print_array(array,8);
    return 0;
}