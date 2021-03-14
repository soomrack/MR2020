#include <iostream>
#include <string.h>

void bubbleSort (int *array, int size){
    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-1-i; j++){
            if (array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int array[7] = {4, 3, 2, 1, 7, 6 , 5,};
    bubbleSort(array, 7);
    for (int i = 0; i < 7; i++){
        std::cout << array[i] << ' ';
    }
    return 0;
}
