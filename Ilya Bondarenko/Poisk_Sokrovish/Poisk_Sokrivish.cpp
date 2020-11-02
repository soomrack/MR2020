#include <iostream>
using namespace std;
char Map[4][2];
int i, j, n;

int Marshrut() {
    if (n == 1) {
        if (Map[i][j - 1] == '0') { i = i; j = j - 1; n = 3; }
        else if (Map[i + 1][j] == '0') { i = i + 1; j = j; n = 1; }
        else if (Map[i][j + 1] == '0') { i = i; j = j + 1; n = 2; }
        else { i = i - 1; j = j; n = 4; }
    }

    else if (n == 2) {
        if (Map[i + 1][j] == '0') { i = i + 1; j = j; n = 1; }
        else if (Map[i][j + 1] == '0') { i = i; j = j + 1; n = 2; }
        else if (Map[i - 1][j] == '0') { i = i - 1; j = j; n = 4; }
        else { i = i; j = j - 1; n = 3; }
    }

    else if (n == 3) {
        if (Map[i - 1][j] == '0') { i = i - 1; j = j; n = 4; }
        else if (Map[i][j - 1] == '0') { i = i; j = j - 1; n = 3; }
        else if (Map[i + 1][j] == '0') { i = i + 1; j = j; n = 1; }
        else { i = i; j = j + 1; n = 2; }
    }


    else if (n == 4) {
        if (Map[i][j + 1] == '0') { i = i; j = j + 1; n = 2; }
        else if (Map[i - 1][j] == '0') { i = i - 1; j = j; n = 4; }
        else if (Map[i][j - 1] == '0') { i = i; j = j - 1; n = 3; }
        else { i = i + 1; j = j; n = 1; }
    }
    if (i == 4 && j == 1) { cout << "Вы нашли сокровище !"; exit(1); }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Map[0][0] = 1; Map[1][0] = 0; Map[2][0] = 1; Map[3][0] = 1; Map[4][0] = 1;
    Map[0][1] = 1; Map[1][1] = 0; Map[2][1] = 0; Map[3][1] = 0; Map[4][1] = 0;
    Map[0][2] = 1; Map[1][2] = 1; Map[2][2] = 1; Map[3][2] = 1; Map[4][2] = 1;

    std::cout << "Найдите сокровище! Вот карта. ";
    std::cout << Map[0][0] << Map[1][0] << Map[2][0] << Map[3][0] << Map[4][0] << endl;
    std::cout << Map[0][1] << Map[1][1] << Map[2][1] << Map[3][1] << Map[4][1] << endl;
    std::cout << Map[0][2] << Map[1][2] << Map[2][2] << Map[3][2] << Map[4][2] << endl;

    i = 1; j = 0;
    if (Map[i + 1][j] == '0') { i = i + 1; j = j; n = 1; }
    else if (Map[i][j + 1] == '0') { i = i; j = j + 1; n = 2; }
    else if (Map[i - 1][j] == '0') { i = i - 1; j = j; n = 4; }
    else { i = i; j = j - 1; n = 3; }

    for (int k = 0; k << 100; k = k + 1)
    {
        int Marshrut();

     }
    return 0;

}
