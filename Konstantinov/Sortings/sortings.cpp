//
// Created by alex on 04.02.2021.
//

#include <cstring>
#include "sortings.h"

void BubbleSort(int *array, size_t size){
    for(auto i = 0; i < size - 1; i++){
        for(auto j = i + 1; j < size; j++){
            if(array[i] > array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

static void MergeArrays(int * left, size_t left_size, int* right, size_t right_size, int * buffer){

    int left_ptr = 0;
    int right_ptr = 0;

    for(int i = 0; i < left_size + right_size; i++){
        if(right_ptr < right_size && left_ptr < left_size) {  // Если обе половины ещё не полностью записаны
            if (left[left_ptr] > right[right_ptr]) {          // Тогда сравниваем текущий элемент в каждой половине
                buffer[i] = right[right_ptr];                 // И вставляем наименьший, инкрементируя соответствующий указатель
                right_ptr++;
            }
            else {
                buffer[i] = left[left_ptr];
                left_ptr++;
            }
        } else if( right_ptr < right_size){                   // Если же одна из половин "кончилась", то остаток забиваем из второй
            buffer[i] = right[right_ptr];
            right_ptr++;
        } else{
            buffer[i] = left[left_ptr];
            left_ptr++;
        }

    }

    memcpy(left, buffer, 4 * (left_size + right_size));     // Поскольку левая и правая половина могут быть только "соседними", можно копировать без разделения

}

static void StaticMergeSort(int *array, size_t size, int * buffer){

    if(size <= 1)
        return;

    size_t left_size = size/2;
    size_t right_size = size - left_size;

    int * right_array = array + left_size;

    StaticMergeSort(array, left_size, buffer);                               // Сортировка первого массива

    StaticMergeSort(right_array, right_size, buffer);                        // И второго

    MergeArrays(array, left_size, right_array, right_size, buffer); // Затем - слияние

}

int MergeSort(int *array, size_t size){
    int * buffer = new int[size];

    if (buffer == nullptr){
        return MEM_ERR;
    }

    StaticMergeSort(array, size, buffer);

    delete[] buffer;

    return 0;
}


void InsertSort(int *array, size_t size){

    for(int i = 0; i < size - 1; i++){          // Перебор всех элементов

        for(int j = 0; j <= i; j++){            // Перебор всех уже отсортированных элементов
            if (array[i+1] < array[j]){         // И сравнение со следующим неотсортированным элементом
                int temp = array[i+1];
                for(int k = i; k >= j; k--){    // Сдвиг нужной части массива
                    array[k+1] = array[k];
                }
                array[j] = temp;
                continue;
            }
        }
    }
}

static void Heapify(int * array, size_t size, int i){
    int largest = i;

    int left  = 2*i + 1;
    int right = 2*i + 2;

    if(left < size && array[left] > array[largest]){
        largest = left;
    }
    if(right < size && array[right] > array[largest]){
        largest = right;
    }

    if (largest != i){
        std::swap(array[i], array[largest]);

        Heapify(array, size, largest);
    }
}

void HeapSort(int *array, size_t size){

    for(int i = size/2 -1; i >= 0; i--){
        Heapify(array, size, i);
    }

    for(int i = size-1; i >= 0; i--){

        std::swap(array[0], array[i]);

        Heapify(array, i, 0);
    }
}
