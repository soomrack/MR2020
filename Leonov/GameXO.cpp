#include <iostream>
#include <clocale>
#include <ctime>
using namespace std;
char pole[9] = { '-' , '-' , '-' , '-' , '-' , '-' , '-' , '-' , '-' };
int a;
int p;
int j = 1;
void table ()
{
    cout << "Номера клеток: \n";
    cout << "1 2 3 \n";
    cout << "4 5 6 \n";
    cout << "7 8 9 \n";
    cin >> a;
    };


void writing() {
    cout << pole[0] << " " << pole[1] << " " << pole[2] <<" \n";
    cout << pole[3] << " " << pole[4] << " " << pole[5] << " \n";
    cout << pole[6] << " " << pole[7] << " " << pole[8] << " \n";
};


void user_step() 
{
    cout << "Ход Игрока \n";
    pole[a-1] = 'x';
    writing();
};


void computer_step()
{
    cout << "Ход Компектора \n";
    srand(time(0)); // функция, чтобы при каждом запуске рандомайзер выдовал новое число
    p = 0 + rand() % 9;
    while (pole[p] == 'x' || pole[p] == 'o') {
        p = 0 + rand() % 9;
    };
    pole[p] = 'o'; 
    writing();
};


void check()
{
    if (pole[0] == 'x' && pole[1] == 'x' && pole[2] == 'x' ||
        pole[3] == 'x' && pole[4] == 'x' && pole[5] == 'x' ||
        pole[6] == 'x' && pole[7] == 'x' && pole[8] == 'x' ||
        pole[0] == 'x' && pole[3] == 'x' && pole[6] == 'x' ||
        pole[1] == 'x' && pole[4] == 'x' && pole[7] == 'x' ||
        pole[2] == 'x' && pole[5] == 'x' && pole[8] == 'x' ||
        pole[0] == 'x' && pole[4] == 'x' && pole[8] == 'x' ||
        pole[6] == 'x' && pole[4] == 'x' && pole[2] == 'x') {
        cout << "Игрок победил \n";
        j = j + 1;
    };  
    if (pole[0] == 'o' && pole[1] == 'o' && pole[2] == 'o' ||
        pole[3] == 'o' && pole[4] == 'o' && pole[5] == 'o' ||
        pole[6] == 'o' && pole[7] == 'o' && pole[8] == 'o' ||
        pole[0] == 'o' && pole[3] == 'o' && pole[6] == 'o' ||
        pole[1] == 'o' && pole[4] == 'o' && pole[7] == 'o' ||
        pole[2] == 'o' && pole[5] == 'o' && pole[8] == 'o' ||
        pole[0] == 'o' && pole[4] == 'o' && pole[8] == 'o' ||
        pole[6] == 'o' && pole[4] == 'o' && pole[2] == 'o') {
        cout << "Компектор победил \n";
        j = j + 1;
    };
    if ((pole[0] == 'x' || pole[0] == 'o') && (pole[1] == 'x' || pole[1] == 'o' ) && (pole[2] == 'x' || pole[2] == 'o' ) &&
        (pole[3] == 'x' || pole[3] == 'o') && (pole[4] == 'x' || pole[4] == 'o') && (pole[5] == 'x' || pole[5] == 'o') &&
        (pole[6] == 'x' || pole[6] == 'o') && (pole[7] == 'x' || pole[7] == 'o') && (pole[8] == 'x' || pole[8] == 'o') ) {
        cout << "Ничья \n";
        j = j + 1;
    };
};


int main()
{
    setlocale(LC_CTYPE, "rus");
    while (j == 1) {
        table();
        user_step();
        computer_step();
        check();
    };
};
