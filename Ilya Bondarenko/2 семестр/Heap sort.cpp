#include <iostream>
using namespace std;

void heapify(int array[], const int size_of_array, int reference_value)
{
    int largest = reference_value;
    int left_value = 2 * reference_value + 1;
    int right_value = 2 * reference_value + 2;

    if (left_value < size_of_array && array[left_value] > array[largest])
    {
        largest = left_value;
    }
    if (right_value < size_of_array && array[right_value] > array[largest])
    {
        largest = right_value;
    }

    if (largest != right_value)
    {
        swap(array[right_value], array[largest]);
        heapify(array, size_of_array, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heap_sort(int array[], const int size_of_array)
{
    for (int reference_value = size_of_array / 2 - 1; reference_value >= 0; reference_value--)
    {
        heapify(array, size_of_array, reference_value);
    }

    for (int current_value = size_of_array - 1; current_value >= 0; current_value --)
    {   
        swap(array[0], array[current_value]);
        heapify(array, current_value, 0);
    }
}

//главная функция
void main()
{
	setlocale(LC_ALL, "Rus");

	// задаем исходный массив
	int array[20] = { 1, 21, 3, 69, 85, 4, 45, 2, 9, 5, 110, 250, 700, 100, 1105 , 52, 99, 10, 9400, 7 };
	cout << " Исходный массив:  1, 21, 3, 69, 85, 4, 45, 2, 9, 5, 110, 250, 700, 100, 1105 , 52, 99, 10, 9400, 7 " << endl;

	// вызываем функцйию сортировки 
    heap_sort(array, 20);
	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements++)
	{
		cout << array[number_of_elements] << ", ";
	}
}
