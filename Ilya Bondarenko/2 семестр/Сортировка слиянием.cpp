#include <iostream>
using namespace std;

void mergeSort(int array[], int start_of_array, int end_of_array, int* buffer) {

    if (start_of_array == end_of_array)
    {
        return;
    }
    int middle = (start_of_array + end_of_array) / 2;
    mergeSort(array, start_of_array, middle, buffer);
    mergeSort(array, middle + 1, end_of_array, buffer);

    for (int counter = start_of_array; counter <= end_of_array; counter++)
    {
        buffer[counter] = array[counter];
    }
    int right_index = middle + 1;
    int left_index = start_of_array;
    int array_index = start_of_array;
    while ((left_index <= middle) && right_index <= end_of_array) 
    {

        if (buffer[left_index] <= buffer[right_index]) 
        {
            array[array_index] = buffer[left_index];
            array_index ++;
            left_index ++;
        }
        else 
        {
            array[array_index] = buffer[right_index];
            array_index ++;
            right_index ++;
        }
    }

    if (left_index > middle) 
    {
        while (right_index <= end_of_array) 
        {
            array[array_index] = buffer[right_index];
            array_index ++;
            right_index ++;
        }
    }

    if (right_index > end_of_array) 
    {
        while (left_index <= middle) 
        {
            array[array_index] = buffer[left_index];
            array_index ++;
            left_index ++;
        }
    }
}

//главная функция
void main()
{
	setlocale(LC_ALL, "Rus");

	// задаем исходный массив
	int array[20] = { 1, 21, 3, 69, 85, 4, 45, 2, 9, 5, 110, 250, 700, 100, 1105 , 52, 99, 10, 9400, 7 };
	cout << " Исходный массив:  1, 21, 3, 69, 85, 4, 45, 2, 9, 5, 110, 250, 700, 100, 1105 , 52, 99, 10, 9400, 7 " << endl;
    int buffer[20] = { 0 };

	// вызываем функцйию сортировки 
    mergeSort(array, 0, 19, buffer);

	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements++)
	{
		cout << array[number_of_elements] << ", ";
	}
}