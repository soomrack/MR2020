#include <iostream>     



// restores max-heap property (parent>=child)
void heapify(int* arr, int start, int end)
{
    int left = 2*start;
    int right = 2*start + 1;
    int largest = -1;
    if (left <= end && arr[left] > arr[start])
        largest = left;
    else largest = start;
    if (right <= end && arr[right] > arr[largest])
        largest = right;
    if (largest != start)
    {
        std::swap(arr[start], arr[largest]);
        heapify(arr, largest, end);
    }
} 
// rearranges arr into maxheap
void build_heap(int* arr, int start, int end)
{
    int length = end - start + 1;
    for (int i = length/2; i >= 0; i--)
        heapify(arr, i, end);
}
// in-place n*log(n) sorting
void heapsort(int *arr, int start, int end)
{
    build_heap(arr, start, end);
    for (int k = end; k >= 1; k--)
    {
        std::swap(arr[0], arr[k]);      // takes the top of the heap (max element) 
        heapify(arr, 0, k - 1);         // restores heap (smaller size this time)
    }

}

int main() 
{
    int a[9] = {-1, 5, -1, 25, -5, 33, 789, -22, -11};
    heapsort(a, 0, 8);
    
    for (int k = 0; k < 9; k++)
        printf("%d ", a[k]);
}
