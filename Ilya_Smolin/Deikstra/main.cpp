#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

const int cols =7;
const int rows =7;
int matrix [cols][rows]={{0, 0, 0, 0, 0, 0, 0},
                         {9, 0, 0, 0, 0, 0, 0},
                         {0, 9, 0, 9, 9, 0, 0},
                         {0, 9, 9, 0, 9, 0, 0},
                         {0, 0, 0, 0, 0, 9, 0},
                         {0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0}};

int rowgraal = 6;
int colgraal = 4;
int startpointcol = 0;
int startpointrow = 0;
int count;
//Функция вывода двумерного массива (колонки, строки, адрес первого элемента)
void pri_arr () {
    cout << "Map" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == rowgraal && j == colgraal)||(i == startpointrow && j == startpointcol)) {
                cout << "*"; continue;

            }
            cout << matrix[i][j];
        }
        cout << endl;
    }
}
void fillin(){
    vector<pair<int,int>>Vn; //Вектор,содержащий адреса соседей
    vector<pair<int,int>>Vnn;//Вектор, содержащий адреса соседей соседей
    matrix[startpointrow][startpointcol]=1;//Заносим в помеченные точки
    Vn.push_back(make_pair(startpointrow,startpointcol));
    count = 1;
    int breakpoint;
while (breakpoint!=1) {
    for (int i = 0; i < Vn.size(); i++) {
        int sosed_k = Vn[i].first;
        int sosed_j = Vn[i].second;
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                if (((sosed_k + k) < rows) && ((sosed_k + k) >= 0) && ((sosed_j + j) < cols) && ((sosed_j + j) >= 0) &&
                    matrix[sosed_k + k][sosed_j + j] == 0) {
                    Vnn.emplace_back(sosed_k + k, sosed_j + j);
                    if (((sosed_k + k) != rowgraal) || ((sosed_j + j) != colgraal)) {
                        matrix[sosed_k + k][sosed_j + j] = count;
                    } else breakpoint = 1;
                }
            }
        }
    }
    Vn = Vnn;
    count++;
    }
}
void trackback(){
    vector<pair<int,int>>Trace;
    Trace.emplace_back(rowgraal,colgraal);
    for (int i = 0; i < count; ++i) {
        int sosed_k = Trace[i].first;
        int sosed_j = Trace[i].second;
        for (int k = -1; k <= 1; k++) {
            for (int j = -1; j <= 1; j++) {
                if (((sosed_k + k) < rows) && ((sosed_k + k) >= 0) && ((sosed_j + j) < cols) &&
                        ((sosed_j + j) >= 0) &&
                        matrix[sosed_k + k][sosed_j + j] == count-i-2) {
                    Trace.emplace_back(sosed_k + k, sosed_j + j);
                    goto a;
                }
            }
        }
        a:;
    }
    Trace.emplace_back(startpointrow,startpointcol);
    cout<<"Way:"<<endl;
    for(auto & i : Trace)
    {
        cout << i.first << ", " << i.second << endl;
    }
}
int main() {
    pri_arr();
    fillin();
    pri_arr();
    trackback();
    return 0;
}
