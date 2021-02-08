#include <iostream>
using namespace  std;

void insertion_sort_function(int function_array[], int length) {
    for (int sorted_index = 0; sorted_index < length-1; sorted_index++) {
        for (int j = sorted_index; j > 0 && function_array[j-1] > function_array[j]; j--) {
            swap(function_array[j-1], function_array[j]);
        }
    }
}

int main() {
    int size;

    cout << "Enter the number of array elements" << endl;
    cin >> size;

    if (size <= 0) {
        cerr << "Invalid size" << endl;
        return 1;
    }

    int arr[size];

    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    insertion_sort_function(arr, size);

    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}
