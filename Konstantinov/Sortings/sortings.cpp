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

static int MergeArrays(int * left, size_t left_size, int* right, size_t right_size){

    int left_ptr = 0;
    int right_ptr = 0;

    int * result = new int[left_size + right_size];           // Динамически выделяем столько памяти, сколько нужно. Не более

    if(result == nullptr){
        return MEM_ERR;                                       // Проверяем на нулевой указатель и выходим из функции при ошибке
    }

    for(int i = 0; i < left_size + right_size; i++){
        if(right_ptr < right_size && left_ptr < left_size) {  // Если обе половины ещё не полностью записаны
            if (left[left_ptr] > right[right_ptr]) {          // Тогда сравниваем текущий элемент в каждой половине
                result[i] = right[right_ptr];                 // И вставляем наименьший, инкрементируя соответствующий указатель
                right_ptr++;
            }
            else {
                result[i] = left[left_ptr];
                left_ptr++;
            }
        } else if( right_ptr < right_size){                   // Если же одна из половин "кончилась", то остаток забиваем из второй
            result[i] = right[right_ptr];
            right_ptr++;
        } else{
            result[i] = left[left_ptr];
            left_ptr++;
        }

    }

    memcpy(left, result, 4 * (left_size + right_size));     // Поскольку левая и правая половина могут быть только "соседними", можно копировать без разделения
    delete result;

    return 0;
}

int MergeSort(int *array, size_t size){

    if(size <= 1)
        return 0;

    size_t left_size = size/2;
    size_t right_size = size - left_size;

    int * right_array = array + left_size;

    if(MergeSort(array, left_size) != 0){                               // Сортировка первого массива
        return MEM_ERR;
    }
    if(MergeSort(right_array, right_size) != 0){                        // И второго
        return MEM_ERR;
    }

    if(MergeArrays(array, left_size, right_array, right_size) != 0){    // Затем - слияние
        return MEM_ERR;
    }
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
