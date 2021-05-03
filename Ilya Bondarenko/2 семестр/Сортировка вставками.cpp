#include <iostream>
using namespace std;

void insertion_sort(int array[], const int size_of_array)
{
	for (int sortable_array = 1; sortable_array < size_of_array; sortable_array ++)
	{
		for (int current_number = sortable_array; (current_number > 0) && (array[current_number - 1] > array[current_number]); current_number--)
		{
			swap(array[current_number - 1], array[current_number]);
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

	// вызываем функцйию сортировки 
	insertion_sort(array, 20);

	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements ++)
	{
		cout << array[number_of_elements] << ", ";
	}
}
