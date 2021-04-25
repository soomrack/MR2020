#include <iostream>

using namespace std;

void shell_sort(int array[], int size_of_array) //сортировка Шелла
{
	// дистанция выбрана согласно последовательности Пратта
	int distance[7] = { 9, 8, 6, 4, 3, 2, 1 };
	int iteration = 0;
	int position = 0;
	// в зависимости от номера итерации у нас берется разная дистанция
	while (iteration < 7) 
	{
		for (position = 0; position < size_of_array - distance[iteration]; position++) 
		{
			// сравниваем элементы в паре, при необходимости - меняем местами
			if (array[position] > array[position + distance[iteration]])
			{
				int temporary_variable = array[position];
				array[position] = array[position + distance[iteration]];
				array[position + distance[iteration]] = temporary_variable;
			}
		}
		iteration ++;
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
	// необходимо, чтобы массив состоял из 20 элементов
	shell_sort(array,20);
	
	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements ++)
	{
		cout << array[number_of_elements] << ", ";
	}
}

