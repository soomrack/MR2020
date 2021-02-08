#include <iostream>
#include <cstring>
#include "sortings.h"


int main() {
    int original[10];

    for (int i = 0; i < 10; i++){
        original[i] = rand() % 255;
        std::cout << original[i] << " ";
    }
    std::cout << std::endl;

    int bubble[10];
    memcpy(bubble, original, sizeof(original));

    BubbleSort(bubble, 10);
    std::cout << "Bubble Sort: ";
    for (int i: bubble){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int merge[10];
    memcpy(merge, original, sizeof(original));

    std::cout << MergeSort(merge, 10);
    std::cout << "Merge Sort:  ";
    for (int i: merge){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int insert[10];
    memcpy(insert, original, sizeof(original));

    InsertSort(insert, 10);

    std::cout << "Insert Sort: ";
    for (int i: insert){
        std::cout << i << " ";
    }
    return 0;
}
