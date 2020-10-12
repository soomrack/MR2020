#include <iostream>
#include <cstdlib>
#include <ctime>

void player(void);
void computer(void);
void output_pole(void);
void checking(void);
int i, j, ii;
int counter = 0;
int jj=0;
char pole [3][3] = {
        {'_','_','_'},
        {'_','_','_'},
        {'_','_','_'}
};

int main() {
    using namespace std;
    for (i = 0; i < 20; i++) {
        player();
        computer();
        output_pole();
        checking();
        cout << "\n";
    }
    return 0;
}

void player() {
    using namespace std;
    int row, column;
    cout << "enter a raw\n";
    cin >> row;
    cout << "enter a column\n";
    cin >> column;
    while (pole[row][column] != '_') {
        if (pole[row][column] == 'X' or pole[row][column] == 'O') {
            cout << "This cell is already taken. Please choose another one\n";
            cout << "enter a raw\n";
            cin >> row;
            cout << "enter a column\n";
            cin >> column;
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (i == row and j == column){
                pole[row][column] = 'X';
            }
        }
    }
}

void computer() {
    int k = 0;
    for (i = 0; i < 3; i++) {
        if (k == 1) {
            break;
        }
        for (j = 0; j < 3; j++) {
            if (pole[i][j] == 'X' and pole[i][j + 1] == 'X' and pole[i][j + 2] == '_') {
                pole[i][j + 2] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == '_' and pole[i][j + 1] == 'X' and pole[i][j + 2] == 'X') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == 'X' and pole[i][j + 1] == '_' and pole[i][j + 2] == 'X') {
                pole[i][j + 1] = 'O';
                k += 1;
                break;
            }
        }
    }

    for (j = 0; j < 3; j++) {
        if (k == 1) {
            break;
        }
        for (i = 0; i < 3; i++) {
            if (pole[i][j] == 'X' and pole[i + 1][j] == 'X' and pole[i + 2][j] == '_') {
                pole[i + 2][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == '_' and pole[i + 1][j] == 'X' and pole[i + 2][j] == 'X') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == 'X' and pole[i + 1][j] == '_' and pole[i + 2][j] == 'X') {
                pole[i + 1][j] = 'O';
                k += 1;
                break;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (k == 1) {
            break;
        }
        for (j = 0; j < 3; j++) {
            if (i == j and pole[i][j] == 'X' and pole[i + 1][j + 1] == 'X' and pole[i + 2][j + 2] == '_') {
                pole[i + 2][j + 2] = 'O';
                k += 1;
                break;
            }
            if (i == j and pole[i][j] == 'X' and pole[i + 1][j + 1] == '_' and pole[i + 2][j + 2] == 'X') {
                pole[i + 1][j + 1] = 'O';
                k += 1;
                break;
            }
            if (i == j and pole[i][j] == '_' and pole[i + 1][j + 1] == 'X' and pole[i + 2][j + 2] == 'X') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (k == 1) {
            break;
        }
        for (j = 0; j < 3; j++) {
            if (pole[i][j] == 'O' and pole[i][j + 1] == 'O' and pole[i][j + 2] == '_') {
                pole[i][j + 2] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == '_' and pole[i][j + 1] == 'O' and pole[i][j + 2] == 'O') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == 'O' and pole[i][j + 1] == '_' and pole[i][j + 2] == 'O') {
                pole[i][j + 1] = 'O';
                k += 1;
                break;
            }
        }
    }

    for (j = 0; j < 3; j++) {
        if (k == 1) {
            break;
        }
        for (i = 0; i < 3; i++) {
            if (pole[i][j] == 'O' and pole[i + 1][j] == 'O' and pole[i + 2][j] == '_') {
                pole[i + 2][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == '_' and pole[i + 1][j] == 'O' and pole[i + 2][j] == 'O') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
            if (pole[i][j] == 'O' and pole[i + 1][j] == '_' and pole[i + 2][j] == 'O') {
                pole[i + 1][j] = 'O';
                k += 1;
                break;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (k == 1) {
            break;
        }
        for (j = 0; j < 3; j++) {
            if (i == j and pole[i][j] == 'O' and pole[i + 1][j + 1] == 'O' and pole[i + 2][j + 2] == '_') {
                pole[i + 2][j + 2] = 'O';
                k += 1;
                break;
            }
            if (i == j and pole[i][j] == 'O' and pole[i + 1][j + 1] == '_' and pole[i + 2][j + 2] == 'O') {
                pole[i + 1][j + 1] = 'O';
                k += 1;
                break;
            }
            if (i == j and pole[i][j] == '_' and pole[i + 1][j + 1] == 'O' and pole[i + 2][j + 2] == 'O') {
                pole[i][j] = 'O';
                k += 1;
                break;
            }
        }
    }
    ii = 0;
    for (i = 0; i < 3; i++) {
        if (ii == 1) {
            break;
        }
        for (j = 0; j < 3; j++) {
            if (k == 0 and pole[i][j] == '_') {
                pole[i][j] = 'O';
                ii += 1;
                break;
            }
        }
    }
}


void checking(){        //ПРОВЕРКА НА НАЛИЧИЕ ВЫИГРЫША
    using namespace std;
    int k, n, l, p, c;
    c = 0;
    for (i = 0; i < 3; i++) {      //ПРОВЕРКА СТРОКИ
        k = 0;
        n = 0;
        for (j = 0; j < 3; j++){
            if (pole[i][j] == 'X'){
                k++;
            } else if (pole[i][j] == 'O'){
                n++;
            }
            if (k == 3){
                cout << "Player win!";
                exit(0);
            } else if (n == 3){
                cout << "Computer win!";
                exit(0);
            }
        }
    }

    for (j = 0; j < 3; j++) {          //ПРОВЕРКА СТОЛБЦА
        k = 0;
        n = 0;
        for (i = 0; i < 3; i++){
            if (pole[i][j] == 'X'){
                k++;
            } else if (pole[i][j] == 'O'){
                n++;
            }
            if (k == 3){
                cout << "Player win!";
                exit(0);
            } else if (n == 3){
                cout << "Computer win!";
                exit(0);
            }
        }
    }
    k = 0;
    n = 0;
    p = 0;
    l = 0;
    for (i = 0; i < 3; i++){      //ПРОВЕРКА ПО ДИАГОАЛИ
        for (j = 0; j < 3; j++){
            if (i + j == 0 + 2 * i and pole[i][j] == 'X'){
                k++;
            } else if (i + j == 2 and pole[i][j] == 'X'){
                l++;
            } else if (i == j and pole[i][j] == 'O'){
                n++;
            } else if (i + j == 2 and pole[i][j] == 'O'){
                p++;
            }
            if (pole[i][j] != '_') {
                jj+=1;
            }
        }
        if (jj == 20){
                cout << "There is no winner!";
                exit(0);
        }
        if (k == 3 or l == 3){
            cout << "Player win!";
            exit(0);
        } else if (n == 3 or p == 3){
            cout << "Computer win!";
            exit(0);
        }
    }

}
void output_pole() {     //ВЫВОД ИГРОВОГО ПОЛЯ НА ЭКРАН
    using namespace std;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << pole[i][j] << " | ";
        }
        cout << "\n";
    }
}
