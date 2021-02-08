#include <iostream>

using namespace std;

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    { cout << array[i] << " ";
    }
    cout << endl;
}

void bubble_sort(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main()
{
    int array[8] = { 6,9,23,2,12,-5,-1,5 };
    bubble_sort(array,8);
    print_array(array,8);
    return 0;
}