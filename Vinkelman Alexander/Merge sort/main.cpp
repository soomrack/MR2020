#include <iostream>
using namespace  std;

void merge_sort_function(int *a, int n) {
    if (n == 1) return;
    int middle = n >> 1;
    int left[middle];
    int right[n-middle];
    for (int k = 0; k < middle; k++) {
        left[k] = a[k];
    }
    for (int k = middle; k < n; k++) {
        right[k-middle] = a[k];
    }
    merge_sort_function(left, middle);
    merge_sort_function(right, n-middle);
    int a_index = 0;
    int left_index = 0;
    int right_index = 0;
    while (left_index < middle & right_index < n-middle) {
        if (left[left_index] < right[right_index]) {
            a[a_index] = left[left_index];
            a_index++;
            left_index++;
        } else {
            a[a_index] = right[right_index];
            a_index++;
            right_index++;
        }
    }
    if (left_index == middle) {
        for ( ; right_index < n-middle; right_index++) {
            a[a_index] = right[right_index];
            a_index++;
        }
    } else {
        for ( ; left_index < middle; left_index++) {
            a[a_index] = left[left_index];
            a_index++;
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

    merge_sort_function(arr, size);

    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}
