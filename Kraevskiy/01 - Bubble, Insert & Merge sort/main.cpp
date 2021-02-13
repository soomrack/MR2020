#include <iostream>


void Swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void Print_array (int array[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d  ", array[i]);
    printf("\n");
}


void Bubble_sort(int array[], int length)
{
    if (length == 1) return;
    for (int sorted_index = length - 1; sorted_index != 0; sorted_index--)
    {
        for (int k = 0; k < sorted_index; k++)
        {
            if (array[k] > array[k+1])
                Swap(&array[k], &array[k+1]);
        }

    }
}


void Insert_sort(int array[], int length)
{
    if (length == 1) return;
    for (int sorted_index = 1; sorted_index != length-1; sorted_index++)
    {
        int k = sorted_index + 1;
        while (array[k-1] > array[k] && k > 0)
        {
            Swap (&array[k-1], &array[k]);
            k--;
        }
    }
}


void Merge(int* array, int first, int last)
{
    int* buffer = new int[100];
    int middle = (first + last) / 2;
    int start = first;
    int final = middle + 1;

    for (int j = first; j <= last; j++)
    {
        if ((start <= middle) && ((final > last) || (array[start] < array[final])))
        {
            buffer[j] = array[start];
            start++;
        }
        else
        {
            buffer[j] = array[final];
            final++;
        }
    }

    for (int j = first; j <= last; j++)
    {
        array[j] = buffer[j];
    }
    delete[]buffer;
}


void Merge_sort(int* A, int first, int last)
{
    if (first < last)
    {
        Merge_sort(A, first, (first + last) / 2);     //sorting of the left side
        Merge_sort(A, (first + last) / 2 + 1, last);  //sorting of the right side
        Merge(A, first, last);
    }
}


int main()
{
    int testArray1[10] = {5, 4, 2, 5, 6, 1, 6, 9, 3, 10};
    //Bubble_sort(testArray1, 10);
    //Insert_sort(testArray1, 10);
    Merge_sort(testArray1, 0,9);
    Print_array(testArray1, 10);

    return 0;
}