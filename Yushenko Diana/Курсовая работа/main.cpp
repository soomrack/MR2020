#include <iostream>
using namespace std;
void narayana(int *array, const int n);

int main() {
    int arr[5] = {13, 9, 7, 5, 2};
    narayana(arr, 5);
    for(int c = 0; c < 5; c++) { //Вывод элементов в консоль
        cout << arr[c] << "\n";
    }
    return 0;
}

void narayana(int *array, const int n) {
    int i, j, k ,l;
    for(i = n - 2; (i > 0) && (array[i] > array [i+1]); i--); //Реализация первого шага
    for (j = n - 1; array[j] < array[i]; j--); //Реализация второго шага
    swap(array[i], array[j]);
    for(l = i + 1, k = n - 1; l < k; l++, k--) { //Реализация третьего шага
        swap(array[l], array[k]);
    }
}
