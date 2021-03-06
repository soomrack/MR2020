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
        for (int i = 0; i < size - 1; i++)
            if (array[i] > array[i + 1])
                swap(array[i + 1], array[i]);
}


void insertion_sort(int *array, int size)
{
    for (int sorted_element_index = 0; sorted_element_index < size - 1; sorted_element_index++)
    {
        int i = sorted_element_index + 1;
        while ((i > 0) && (array[i] < array[i - 1]))
        {
            swap(array[i - 1], array[i]);
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


void heap_creation(int *array, int size, int last_parent)
{
    int max = last_parent;
    int left = 2 * last_parent + 1;
    int right = 2 * last_parent + 2;

    if (left < size && array[left] > array[max])
        max = left;

    if (right < size && array[right] > array[max])
        max = right;

    if (max != last_parent)
    {
        swap(array[last_parent], array[max]);
        heap_creation(array, size, max);
    }
}


void heap_sort(int *array, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heap_creation(array, size, i);

    for (int i = size - 1; i >= 0; i--)
    {
        swap(array[0], array[i]);
        heap_creation(array, i, 0);
    }
}


int main()
{
    return 0;
}
