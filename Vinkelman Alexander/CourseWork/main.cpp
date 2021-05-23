#include <iostream>
#include <ctime>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <ctime>

using namespace std;

typedef vector <int> Mass;

int main() {
    unsigned int a = 0, b = 0;
    int Amount = 0;

    // Создание итераторов
    Mass::iterator LagA;
    Mass::iterator LagB;
    Mass::iterator Lag;

    // Запрос у пользователя на ввод параметров
    cout << "Lag a = ";
    cin >> a;
    cout << "Lag b = ";
    cin >> b;
    cout << "Amount of numbers ";
    cin >> Amount;

    // Начало отсчёта времени работы
    unsigned int start_time = clock();

    // Создание массива
    Mass massive(1);
    massive.resize(max(a,b) + Amount + 1);

    // Инициализация лагов и сдвиг
    // на значения a и b
    LagA = massive.begin();
    advance(LagA, a);
    LagB = massive.begin();
    advance(LagB, b);

    // Инициализация дополнительного итератора
    // для коорректной работы цикла
    if (LagA > LagB) {
        Lag = LagA;
    } else {
        Lag = LagB;
    }

    // Основной итератор для движения по массиву
    Mass::iterator index;
    index = massive.begin();

    // Заполнение первой части массива
    // случайными значениями
    srand(time(nullptr));
    while (index <= Lag) {
        *index = rand();
        cout << "Number = " << *index << endl;
        index++;
    }

    // Получение последовательности методом
    // Фибоначчи с запаздыванием
    for (; index != massive.end(); index++, LagA++, LagB++) {
        if (*LagA >= *LagB) {
            *index = *LagA - *LagB;
        } else {
            *index = *LagB - *LagA;
        }
        cout << *index << endl;
    }

    unsigned int end_time = clock();   // Конец отсчёта времени работы
    // Вычисление конечного времени работы
    unsigned int search_time = end_time - start_time;
    cout << "Run time = " << search_time << endl;
    return 0;
}
