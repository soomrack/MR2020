#include <iostream> 

void mergeSort(int * arr, int l, int r);
void merge(int * arr, int l, int m, int r);
void swap(int *a, int *b);
void sort( int * arr, int size );

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void sort( int * arr, int size )
{ 
    // для удобной рекурсии  создаем новую функцию  с другими параметрами 
    mergeSort(arr, 0, size - 1);
}

void mergeSort(int * arr, int l, int r)
{
    // input: указатель на массив, индекс первого и полседнего элемента.
    
    // если левая не меньше правой границы значит у нас ветка из 1 элемента 
	if (l < r) {
		int m = (r + l) / 2;
        // углуюление ветки влево
		mergeSort(arr, l, m);
        // углубление вправо
		mergeSort(arr, m + 1, r);
        
        // слияние левой и правой ветки (левая и правая ветка уже внутри себя отсортированные)
        // левая - arr[l..m], правая - arr[m+1..r]
		merge(arr, l, m, r);
	}
}

void merge(int * arr, int l, int m, int r){
    // Слияние двух участвков массива arr[l..m] и arr[m+1..r]
    
    int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// временные левый и правый массив
	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// проходим по временным массивам и берем в основной меньшее значение
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// копируем оставшиеся элементы из левого массива если правый уже закончился
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// копируем оставшиеся элементы из правого массива если левый уже закончился
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

int main(int argc, char const *argv[])
{
    int array[7] = {4,3,2,1,7,6,5,};
    int size = 7;
    sort(array, size); 
    for (int i = 0; i < 7; i++){
        std::cout << array[i] << ' ';
    }
    return 0;
}
