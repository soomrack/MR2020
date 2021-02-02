#include "Sort.h"

int main() {
    int array_1[20] = {70, 31, 32, 71, 94, 32, 33, 35, 56, 28, 66, 64, 71, 88, 90, 85, 27, 73, 98, 43};
    int array_2[20] = {90, 61, 68, 1, 22, 10, 72, 13, 6, 39, 52, 83, 29, 81, 38, 90, 12, 8, 13, 13};
    int array_3[20] = {504, 804, 685, 496, 669, 61, 106, 203, 172, 445, 343, 34, 698, 664, 234, 184, 677, 814, 849, 969};
    
    std::cout<< "First array:\n";
    Print_array(array_1,20);
    Bubble_sort(array_1,20);
    std::cout<< "Sorted:\n";
    Print_array(array_1,20);
    
    std::cout<< "Second array:\n";
    Print_array(array_2,20);
    Insertion_sort(array_2,20);
    std::cout<< "Sorted:\n";
    Print_array(array_2,20);
    
    std::cout<< "Third array:\n";
    Print_array(array_3,20);
    Merge_sort(array_3,0,19);
    std::cout<< "Sorted:\n";
    Print_array(array_3,20);
    return 0;
}
