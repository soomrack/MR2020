#include <iostream>
#include <time.h> 
#include <vector>

using namespace std;

vector <int> sort(vector <int> parray, int array_size)
{
    vector < vector <int> > arr(10, vector <int>());
    // main loop for each digit position
    for (int digit = 1; digit <= 1000000000; digit *= 10)
    {
        for (int i = 0; i < 10; i++)
            std::vector<int>().swap(arr[i]);
        // array to bucket
        for (int i = 0; i < array_size; i++)
        {
            // get the digit 0-9
            int dig = (parray[i] / digit) % 10;
            // add to bucket and increment count
            arr[dig].push_back(parray[i]);
        }
        // bucket to array
        int idx = 0;
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < arr[x].size(); y++)
                parray[idx++] = arr[x][y];
        }
    }
    return parray;
}

void bucketsort(int origin_array[], int array_size)
{
    //divide array into ng=egative and positive
    vector <int> negative_array;
    vector <int> positive_array;
    for (int i = 0; i < array_size; i++)
    {
        if (origin_array[i] >= 0)
            positive_array.push_back(origin_array[i]);
        else
            negative_array.push_back(-origin_array[i]);
    }
    negative_array = sort(negative_array, negative_array.size());
    for (int i = negative_array.size() - 1, j = 0; i >= 0; j++, i--)
        origin_array[i] = -negative_array[j];
    positive_array = sort(positive_array, positive_array.size());
    for (int i = negative_array.size(), j = 0; i < array_size; j++, i++)
        origin_array[i] = positive_array[j];
}

int main()
{
    const int num = 150000;
    int sarray[num];
    bucketsort(sarray, num);
}