//#include <cstdbool>
#include <iostream>

void swap(int* arr, int a, int b){
  arr[a] ^= arr[b];
  arr[b] ^= arr[a];
  arr[a] ^= arr[b];
  return;
}

void bubbleSort(int* array, int size) {
  if (size <= 1) return;
  bool check = true;
  while (check) {
    check = false;
    for (int i = 1; i < size; i++) {
      if (array[i - 1] > array[i]) {
        swap(array, i - 1, i);
        check = true;
      }
    }
  }
  return;
}

void insertSort(int* array, int size) {
  if (size <= 1) return;
  for (int i = 1; i < size; i++) {
    for (int k = i - 1; k >= 0 && array[k - 1] > array[k]; k--) {
      swap(array, k - 1, k);
    }
  }
  return;
}

void mergeSort(int* arr, int* buffer, int start, int end) {
  int n = end - start + 1;
  if (n == 1) return;
  int middle = n >> 1;
  for (int i = start; i < start + middle; i++)
    buffer[i] = arr[i];
  for (int i = start + middle; i < end + 1; i++)
    buffer[i] = arr[i];

  mergeSort(buffer, arr, start, start + middle - 1);
  mergeSort(buffer, arr, start + middle, end);

  int a_index = start;//index of the array with the answer
  int left_index = start;
  int right_index = start + middle;
  while ((left_index < start + middle) & (right_index < end + 1))
  {
    if (buffer[left_index] < buffer[right_index])
    {
      arr[a_index] = buffer[left_index];
      left_index++;
    }
    else
    {
      arr[a_index] = buffer[right_index];
      right_index++;
    }
    a_index++;
  }
  if (left_index == start + middle)
  {
    for (; right_index < end + 1; right_index++)
    {
      arr[a_index] = buffer[right_index];
      a_index++;
    }
  }
  else
  {
    for (; left_index < start + middle; left_index++)
    {
      arr[a_index] = buffer[left_index];
      a_index++;
    }

  }
  return;
}

void trueMergeSort(int* arr, int size) {
  int* buffer = new int[size];
  mergeSort(arr, buffer, 0, size - 1);
  delete buffer;
  return;
}

int main() {
  int array[] = {6, 7, 5, 0, 4, 5, 4, 7, 1, 8, 9, 4 };
  trueMergeSort(array, 12);
  for (int i = 0; i < 12; i++) {
    std::cout << array[i];
  }
}