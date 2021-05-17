#include <iostream>

void InsertionSort(int n, int mass[])
{
    int newElement, location;
 
    for (int i = 1; i < n; i++)
    {
        newElement = mass[i];
        location = i - 1;
        while(location >= 0 && mass[location] > newElement)
        {
            mass[location+1] = mass[location];
            location = location - 1;
        }
        mass[location+1] = newElement;
    }
}
 
int main()
{
    int array[7] = {4, 3, 2, 1, 7, 6, 5,};
    int size = 7;
    InsertionSort(size, array);
    for (int i = 0; i < 7; i++) {
        std::cout << array[i] << ' ';
    }
    return 0;

}