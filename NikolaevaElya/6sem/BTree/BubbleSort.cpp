#include <iostream>
using namespace std;

int swap(int *first, int *second){
    int temp = *first;
    *first = *second;
    *second = temp;

    return 0;
}

int bubbleSort(int arr[], int size) {
    for(int step = 0; step < size; step++) {
        for (int i = 0; i < size - 1; i++) {
            if(arr[i] > arr[i+1]) {
            swap(arr[i], arr[i+1]);
            }
        } 
    }
    
    return 0;
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    cout << "  " << arr[i];
  }
  cout << "\n";
}

int main(){
    int test[] = {-3, 9, 8, -34, 99, -1};
    bubbleSort(test, 6);

    printArray(test, 6);

    return 0;
}