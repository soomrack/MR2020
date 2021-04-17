#include <iostream>
using namespace std;

int swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;

    return 0;
}

//This is the function to creat Max Heap
void heapify(int array[], int array_size, int i){
    int largest = i; 
    int left = 2 * i + 1;  //left leaf of the largest element
    int right = 2 * i + 2; //right leaf of the largest element
  
    if((left < array_size) && (array[left] > array[largest])){
        largest = left;
    }
   
    if((right < array_size) && (array[right] > array[largest])){
        largest = right;
    }

    if(largest != i){
        swap(array[i], array[largest]);        //lift up the biggest element
        heapify(array, array_size, largest);   
    }
}

void heapSort(int array[], int array_size){
    for (int i = array_size / 2 - 1; i >= 0; i--){
        heapify(array, array_size, i);
    }

    // One by one extract an element from the heap
    for (int i = array_size - 1; i > 0; i--) {
        swap(array[0], array[i]);  // Move current root to end
        heapify(array, i, 0);    // Reduce the heap 
    }
}
 
int main()
{
    int A[5] = {0, 6, 7, 2, 100};
    heapSort(A, 5);

    cout << A[3];

    return 0;
}