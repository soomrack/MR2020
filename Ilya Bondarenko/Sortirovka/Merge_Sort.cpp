#include <iostream>

void merge_sort_function(int* array, int size) {
    if (size == 1) {
        return;
    }
    int middle = size >> 1;
    int left[middle];
    int right[size - middle];
    for (int pointer = 0; pointer < middle; pointer++) {
        left[pointer] = array[pointer];
    }
    for (int pointer = middle; pointer < size; pointer++) {
        right[pointer - middle] = array[pointer];
    }
    merge_sort_function(left, middle);
    merge_sort_function(right, size - middle);
    int a_index = 0;
    int left_index = 0;
    int right_index = 0;
    while (left_index < middle & right_index < size - middle) {
        if (left[left_index] < right[right_index]) {
            array[a_index] = left[left_index];
            a_index++;
            left_index++;
        }
        else {
            array[a_index] = right[right_index];
            a_index++;
            right_index++;
        }
    }
    if (left_index == middle) {
        for (; right_index < size - middle; right_index++) {
            array[a_index] = right[right_index];
            a_index++;
        }
    }
    else {
        for (; left_index < middle; left_index++) {
            array[a_index] = left[left_index];
            a_index++;
        }
    }
}
   
int main() {
    int a[10] = { 5, 7, 10, 44, 52, 76, 3, 2, 1 };
    merge_sort_function(a, 10);
}