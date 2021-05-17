#include <iostream>
#include <chrono>
using namespace std;

#define ARRAY_SIZE 10
#define RANGE_OF_VALUES 10000

int kadanes(int array[],int length) {
    int highestMax = 0;
    int currentElementMax = 0;

    for(int i = 0; i < length; i++) {
        currentElementMax =max(array[i],currentElementMax + array[i]) ;
        highestMax = max(highestMax,currentElementMax); 
    }

    return highestMax;
}
int main() {
    int elementsQuantity[ARRAY_SIZE] = {5, 10, 50, 100, 200, 500, 1000, 5000, 10000, 100000};

    for (int k = 0; k < 10; k++) {
        int arr[elementsQuantity[k]] = {0};

        for (int i = 0; i < elementsQuantity[k]; i++) {
            arr[i] = rand() % RANGE_OF_VALUES - RANGE_OF_VALUES/2;
        }

        auto start = chrono::steady_clock::now();
        cout << "The Maximum Sum is: "<<kadanes(arr,elementsQuantity[k]) << endl;
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Duration is " << duration.count() << " ms"<< endl;   
    }
    
    return 0;
}
