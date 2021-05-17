#include <iostream>
using namespace std;

//построение кучи
void heapify(int array[], int begin, int end)
{
	int left = 2 * begin + 1;
	int right = 2 * begin + 2;

	if (left > end)
	{
		return;
	}
	if (right > end)
	{
		if (array[begin] < array[left])
		{
			swap(array[begin], array[left]);
			return;
		}
	}
	if (array[left] > array[right])
	{
		if (array[begin] < array[left])
		{
			swap(array[begin], array[left]);
			heapify(array, left, end);
			return;
		}
	}
	else
	{
		if (array[begin] < array[right])
		{
			swap(array[begin], array[right]);
			heapify(array, right, end);
			return;
		}
	}
}
void build_heap(int array[], int start, int end)
{
	int length = end - start + 1;
	for (int counter = length / 2; counter >= 0; counter --)
	{
		heapify(array, counter, end);
	}
}

void heap_sort(int array[], int start, int end)
{
		build_heap(array, start, end);
		for (int counter = end; counter >= 1; counter--)
		{
			swap(array[0], array[counter]);
			heapify(array, 0, counter - 1);
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
	heap_sort(array, 0, 19);


	// выводим результат
	cout << " Отcортированный массив:  " << endl;
	for (int number_of_elements = 0; number_of_elements < 20; number_of_elements++)
	{
		cout << array[number_of_elements] << ", ";
	}
}