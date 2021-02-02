#include <iostream>
using namespace std;

void Bubble_sort(int* parray,int size_array)
{
	for (int sorted_index = size_array-1; sorted_index!=0; sorted_index--)
	{
		for (int i = 0; i < sorted_index; i++)
		{
			if (parray[i] > parray[i + 1])
				swap(parray[i], parray[i + 1]);
		}
	}
}

void Insertion_sort(int* parray, int size_array)
{
	for (int sorted_index = 0; sorted_index != size_array - 1; sorted_index++)
	{
		int i = sorted_index + 1;
		while ((parray[i - 1] > parray[i]) & (i > 0))
		{
			swap(parray[i - 1], parray[i]);
			i--;
		}
	}
}

void Merge_sort(int* parray, int* buffer, int start, int end)
{
	int n = end - start + 1;
	if (n == 1) return;
	int middle = n >> 1;
	for (int i = start; i < start+middle; i++)
		buffer[i] = parray[i];
	for (int i = start+middle; i < end+1; i++)
		buffer[i] = parray[i];
	Merge_sort(buffer, parray, start, start + middle - 1);//buffer and array swap
	Merge_sort(buffer, parray, start + middle, end);//buffer and array swap
	int a_index = start;//index of the array with the answer
	int left_index = start;
	int right_index = start + middle;
	while ((left_index < start + middle) & (right_index < end + 1))
	{
		if (buffer[left_index] < buffer[right_index])
		{
			parray[a_index] = buffer[left_index];
			a_index++;
			left_index++;
		}
		else
		{
			parray[a_index] = buffer[right_index];
			a_index++;
			right_index++;
		}
	}
	if (left_index == start + middle)
	{
		for (; right_index < end + 1; right_index++)
		{
			parray[a_index] = buffer[right_index];
			a_index++;
		}
	}
	else
	{
		for (; left_index < start + middle; left_index++)
		{
			parray[a_index] = buffer[left_index];
			a_index++;
		}
	}
}

int main()
{
	int array[6] = { 5,4,3,1,8,9 };
	int size_array = sizeof(array)/4;
	int* parray = array;
	int array_buffer[6] = { 0,0,0,0,0,0 };
	int* buffer = array_buffer;
	Merge_sort(parray,buffer,0,5);
	//Check
	for (int i = 0; i < 6; i++)
	{
		cout << array[i] << '\t';
	}
	//
	return 0;
}