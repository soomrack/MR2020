#include <iostream>
using namespace std;

void bubble_sort(int array[], const int size_of_array)
{
	for (int array_walk = 0; array_walk < size_of_array - 1; array_walk++)
	{
		for (int pairwise_comparison = size_of_array - 1; pairwise_comparison > array_walk; pairwise_comparison--)
		{
			if (array[pairwise_comparison - 1] > array[pairwise_comparison])
			{
				std::swap(array[pairwise_comparison - 1], array[pairwise_comparison]);
			}
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
	bubble_sort(array, 20);

	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements++)
	{
		cout << array[number_of_elements] << ", ";
	}
}
