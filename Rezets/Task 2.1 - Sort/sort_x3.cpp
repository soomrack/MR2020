#include <iostream>
using namespace std;

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void bubble_sort(int *array, int size)
{
    for (int sorted_elements = 0; sorted_elements < size; sorted_elements++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                int temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
            }
        }
    }
}

void insertion_sort(int *array, int size)
{
    for (int sorted_element_index = 0; sorted_element_index < size - 1; sorted_element_index++)
    {
        int i = sorted_element_index + 1;
        while ((i > 0) && (array[i] < array[i - 1]))
        {
            int temp = array[i - 1];
            array[i - 1] = array[i];
            array[i] = temp;
            i--;
        }
    }
}

void merge_array(int *array, int first_index, int last_index)
{
    int middle;
    int array1_index;
    int array2_index;
    int *temp_array = new int[last_index + 1];
    
    middle = (first_index + last_index)/2;
    array1_index = first_index;
    array2_index = middle + 1;
    
    for (int i = first_index; i <= last_index; i++)
    {
        if ((array1_index <= middle) && ((array2_index > last_index) || (array[array1_index] < array[array2_index])))
        {
            temp_array[i] = array[array1_index];
            array1_index++;
        }
        else
        {
            temp_array[i] = array[array2_index];
            array2_index++;
        }
    }

    for (int i = first_index; i <= last_index; i++)
        array[i] = temp_array[i];
    delete []temp_array;
}

void merge_sort_array(int *array, int first_index, int last_index)
{
        if (first_index < last_index)
        {
            merge_sort_array(array, first_index, (first_index + last_index)/2);
            merge_sort_array(array, (first_index + last_index)/2 + 1, last_index);
            merge_array(array, first_index, last_index);
        }
}

void merge_sort(int *array, int size)
{
    merge_sort_array(array, 0, size - 1);
}

int main()
{
    return 0;
}
