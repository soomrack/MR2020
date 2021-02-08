#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void insertionSort(int *array, int size)
{
    int counter=0;
    for(int i=1;i<size;i++){
        for(int j=i; j>0 && array[j-1]>array[j];j--){
            counter++;
            int tmp=array[j-1];
            array[j-1]=array[j];
            array[j]=tmp;
        }
    }
}

int main() {
    int array[6] = {6, 5, 4, -2, 3, 1};
    insertionSort(array, 6);
    for (int i = 0; i < 6; i++) {
        cout << array[i] << " ";
    }
    return 0;
}
