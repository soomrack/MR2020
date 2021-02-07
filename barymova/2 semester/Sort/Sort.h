#ifndef SORT_SORT_H
#define SORT_SORT_H

#include <iostream>

void insertionSort (int * arr, int size);
void bubbleSort (int * arr, int size);
void mergeSort (int * arr, int size);

void printArr(int * arr, int size);
void copyArr(const int * original, int * copy, int size);

#endif //SORT_SORT_H
