#include <iostream>
#include <chrono>

void merge_array(int *array, int first_index, int last_index)
{
    int *temp_array = new uint32_t[last_index + 1];
    int middle = (first_index + last_index)/2;
    int array1_index = first_index;
    int array2_index = middle + 1;
    
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
