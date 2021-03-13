#include <iostream>

/*
 * [_____________initial_array______________]
 * >sort()
 * [______ensorted______|_______sorted______]
 * >sort() 
 * [__sorted_|_unsorted_|_______sorted______]
 * >merge()
 * [_unsorted_|____________sorted___________]
 * >...
*/


void mergesort(int* array, int start, int end);

/*
 * merge two sorted subs array[block1_start, block1_end) and array[block2_start...block2_end) to working area - array[r_start...] 
 */
void merge(int* array, int block1_start, int block1_end, int block2_start, int block2_end, int r_start) 
{
    while (block1_start < block1_end && block2_start < block2_end) {
        int temp = array[block1_start] < array[block2_start] ? array[block1_start++] : array[block2_start++];
        std::swap(array[r_start++], temp);
    }
    while (block1_start < block1_end)
        std::swap(array[r_start++], array[block1_start++]);
    while (block2_start < block2_end)
        std::swap(array[r_start++], array[block2_start++]);
}  

/* 
 * sort array[start, l_end), and put result to working area w. 
 * constraint, len(w) == l_end - start
 */
void wsort(int* array, int start, int l_end, int r_start) {
    if (l_end - start > 1)                                   // more than two elements in the left block
    {
        int middle = start + (l_end - start) / 2;
        mergesort(array, start, middle);                     // split the input part
        mergesort(array, middle, l_end);                     // of the array in two
        merge(array, start, middle, middle, l_end, r_start); // and merge the result together
    }
    else
        while (start < l_end)
            std::swap(array[start++], array[r_start++]);
}
// in-place mergesort
void mergesort(int* array, int start, int end) {
    int  n;
    if (end - start <= 1)
        return ;
//  [start ... l_end | r_start ... end]
    int l_end = start + (end - start) / 2;              
    int r_start = start + end - l_end;
    wsort(array, start, l_end, r_start);        // the last half contains sorted elements 
    while (r_start - start > 2) {
        n = r_start;
        r_start = start + (n - start + 1) / 2;  // the first half of the previous working area 
        wsort(array, r_start, n, start);        // contains sorted elements 
        merge(array, start, start + n - r_start, n, end, r_start);
    }
    for (n = r_start; n > start; --n) 
        for (l_end = n; l_end < end && array[l_end] < array[l_end-1]; ++l_end)
            std::swap(array[l_end], array[l_end-1]);
}

int main(){
    int a[9] = {14, 1, 10, 4, 9, 5, 80, 8, 7};
    mergesort(a, 0, 9);

    for (int k = 0; k < 9; k++)
        printf("%d ", a[k]);
}