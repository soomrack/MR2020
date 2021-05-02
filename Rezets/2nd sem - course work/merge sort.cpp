#include <iostream>

void merge_concatenated_part_of_array(int *array, int *temp_array, const int start_of_sector, const int end_of_sector)
{
    const int middle_of_sector = (start_of_sector + end_of_sector)/2;
    int part1_index = start_of_sector;
    int part2_index = middle_of_sector + 1;
    
    for (int i = start_of_sector; i <= end_of_sector; i++)
    {
        if ((part1_index <= middle_of_sector) && ((part2_index > end_of_sector) || (array[part1_index] < array[part2_index])))
        {
            temp_array[i] = array[part1_index];
            part1_index++;
        }
        else
        {
            temp_array[i] = array[part2_index];
            part2_index++;
        }
    }
    for (int i = start_of_sector; i <= end_of_sector; i++)
        array[i] = temp_array[i];
}

void split_and_sort_array(int *array, int *temp_array, const int start_of_sector, const int end_of_sector)
{
        if (start_of_sector < end_of_sector)
        {
            split_and_sort_array(array, temp_array, start_of_sector, (start_of_sector + end_of_sector)/2);
            split_and_sort_array(array, temp_array, (start_of_sector + end_of_sector)/2 + 1, end_of_sector);
            merge_concatenated_part_of_array(array, temp_array, start_of_sector, end_of_sector);
        }
}

void merge_sort(int *array, const int size)
{
    int *temp_array = new int[size];
    split_and_sort_array(array, temp_array, 0, size - 1);
    delete []temp_array;
}

int main()
{
    return 0;
}
