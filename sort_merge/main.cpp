#include <iostream>
#include <stdlib.h>

using namespace std;

void print_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
    { cout << array[i] << " ";
    }
    cout << endl;
}

void merge_sort(int *array, int size)
{
    int mid = size / 2; // находим середину сортируемой последовательности
    if (size % 2 == 1)
        mid++;
    int h = 1; // шаг
    // выделяем память под формируемую последовательность
    int *c = (int*)malloc(size * sizeof(int));
    int step;
    while (h < size)
    {
        step = h;
        int i = 0;   // индекс первого пути
        int j = mid; // индекс второго пути
        int k = 0;   // индекс элемента в результирующей последовательности
        while (step <= mid)
        {
            while ((i < step) && (j < size) && (j < (mid + step)))
            { // пока не дошли до конца пути заполняем следующий элемент формируемой последовательности меньшим из двух просматриваемых
                if (array[i] < array[j])
                {
                    c[k] = array[i];
                    i++; k++;
                }
                else {
                    c[k] = array[j];
                    j++; k++;
                }
            }
            while (i < step)
            { // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
                c[k] = array[i];
                i++; k++;
            }
            while ((j < (mid + step)) && (j<size))
            {  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
                c[k] = array[j];
                j++; k++;
            }
            step = step + h; // переходим к следующему этапу
        }
        h = h * 2;
        // Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
        for (i = 0; i<size; i++)
            array[i] = c[i];
    }
}

int main()
{
    int array[8] = { 6,9,23,2,12,-5,-1,5 };
    merge_sort(array,8);
    print_array(array,8);
    return 0;
}