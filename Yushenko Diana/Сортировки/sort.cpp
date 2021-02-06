#include <iostream>
#include "sort.h"

void bubbleSort(int *array, size_t size){
    for (int arr_index = size; arr_index != 0; arr_index--){
        for (int i = 0; i < arr_index; i++){
            if (array[i] > array[i + 1]){
                std::swap(array[i], array[i + 1]);
            }
        }
    }
}

void insertSort(int *array, size_t size){
    for (int arr_index = 1; arr_index < size; arr_index++){
        for (int i = arr_index; i > 0 && array[i - 1] > array[i]; i--){
            std::swap(array[i - 1], array[i]);
        }
    }
}

void mergeSort(int *array, size_t size){
    int mid = size / 2;
    int step = 0;
    int step_h = 1;
    if (size & 2 == 1){
        mid++;
    }
    int *arr = new int[size];
    while (step_h < size){
        step = step_h;
        int first_part = 0;
        int second_part = mid;
        int elem_index = 0;
        while (step <= mid){
            while (first_part < step && second_part < size && second_part < (mid + step)){
                if(array[first_part] < array[second_part]){
                    arr[elem_index] = array[first_part];
                    first_part++;
                    elem_index++;
                } else {
                    arr[elem_index] = array[second_part];
                    second_part++;
                    elem_index++;
                }
            }
            while (first_part < step){
                arr[elem_index] = array[first_part];
                first_part++;
                elem_index++;
            }
            while (second_part < (mid + step) && second_part < size){
                arr[elem_index] = array[second_part];
                second_part++;
                elem_index++;
            }
            step = step + step_h;
        }
        step_h = step_h * 2;
        for(first_part = 0; first_part < size; first_part++){
            array[first_part] = arr[first_part];
        }
    }
}
