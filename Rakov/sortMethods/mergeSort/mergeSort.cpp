#include <iostream>
using namespace std;

void merge(int array[], int middle, int size){
    int leftPart[middle]; 
    int rightPart[size - middle];
 
    for (int i = 0; i < middle; i++){
        leftPart[i] = array[i];
    }  
    for (int j = 0; (middle + j) < size; j++){
        rightPart[j] = array[middle + j];
    }
    
    int i = 0;
    int j = 0;
    int k = 0;
 
    while (i < middle && (middle + j) < size){
        if (leftPart[i] <= rightPart[j]) {
            array[k] = leftPart[i];
            i++;
        }else{
            array[k] = rightPart[j];
            j++;
        }

        k++;
    }
 
    while (i < middle) {
        array[k] = leftPart[i];
        i++;
        k++;
    }
 
    while ((middle + j) < size) {
        array[k] = rightPart[j];
        j++;
        k++;
    }
}

void mergeSort(int array[],int array_size){
    if(array_size <= 1){
        return;
    }

    int middleIndex = array_size/2;
    mergeSort(array, middleIndex);
    mergeSort(array, array_size - (middleIndex + 1));
    merge(array, middleIndex, array_size);
}

int main(){
    int A[5] = {0, 6, 7, 2, 100};
    mergeSort(A, 5);

    cout << A[3];

    return 0;
}