#include "My_header.h"

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void Make_heap(int *array, int size, int root) {
    // start
    int largest = root;
    int left_child = 2 * root + 1;
    int right_child = 2 * root + 2;
    // change "largest" if children is bigger
    if (left_child < size && array[left_child] > array[largest]) {
        largest = left_child;
    }
    if (right_child < size && array[right_child] > array[largest]) {
        largest = right_child;
    }
    if (largest != root) {
        // put the largest on the root position
        swap(&array[root], &array[largest]);
        // repeat while (largest != root)
        Make_heap(array, size, largest);
    }
}

void Heap_sort(int *arr, int size) {
    // Make heap (binary tree) from bottom to top
    for (int i = size / 2 - 1; i >= 0; i--) {
        Make_heap(arr, size, i);
    }

    for (int end = size - 1; end > 0; end--) {
        // Place max element (root) to the end. Forget about him...
        swap(&arr[0],&arr[end]);
        // Refactor heap with new element on the root position.
        Make_heap(arr, end, 0);
    }
}
