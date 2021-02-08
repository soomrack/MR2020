#include <iostream>
using namespace  std;

void bubble_sort_function(int function_array[], int length) {
    for (int sorted_index = length-1; sorted_index != 0; sorted_index--) {
        for (int k = 0; k < sorted_index; k++) {
            if (function_array[k] > function_array[k+1]) {
                swap(function_array[k], function_array[k+1]);
            }
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

    bubble_sort_function(arr, size);

    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}
