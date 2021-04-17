#include <iostream>
using namespace std;

int insertSort(int array[], int array_size){
    for (int i = 0; i < array_size; i++){
        int key = array[i];  
        int j = i - 1;  
  
        while (j >= 0 && array[j] > key){  
            array[j + 1] = array[j];  
            j = j - 1;  
        }  
        
        array[j + 1] = key;     
    }
    
    return 0;
}

int main(){
    int A[5] = {0, 6, 7, 2, 100};
    insertSort(A, 5);

    cout << A[3];


    return 0;
}