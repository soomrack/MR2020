#include <iostream>
using namespace std;

int swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;

    return 0;
}

int bubbleSort(int array[], int array_size){
    for(int i = 0; i < array_size; i++){
        if(array[i] > array[i+1]){
            swap(array[i], array[i+1]);
        }        
    }
    
    return 0;
}

int main(){
    int A[5] = {0, 6, 7, 2, 100};
    bubbleSort(A, 5);

    cout << A[3];

    return 0;
}
