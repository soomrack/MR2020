#include<iostream>
using namespace std;

int main()
{
	int otvet[5];
	otvet[0] = 1;
	otvet[1] = 2;
	otvet[2] = 1;
	otvet[3] = 2;
	otvet[4] = 1;
	int j = 0, ans[5];
	//тест
		setlocale(LC_ALL, "Rus");
		//1
		cout << "Дата Бородинского сражения\n";
		cout << "1) 7 сентебря 1812 г.\n";
		cout << "2) 18 июня 1815 г. \n";
		cin >> ans[0];
		//2
		cout << "Дата крещение Руси\n";
		cout << "1) 24 июля 962 г.\n";
		cout << "2) 31 мая 988 г.\n";
		cin >> ans[1];
		//3
		cout << "Отмена крепостного права\n";
		cout << "1) 19 февралая 1861 г.\n";
		cout << "2) 17 августа 1879 г.\n";
		cin >> ans[2];
		//4
		cout << "Начало второй мировой войны\n";
		cout << "1) 22 июня 1941 г.\n";
		cout << "2) 1 сентября 1939 г.\n";
		cin >> ans[3];
		//5
		cout << "Распад СССР\n";
		cout << "1) 19 декабря 1993 г.\n";
		cout << "2) 26 декабря 1991 г.\n";
		cin >> ans[4];

		for (int i = 0; i < 5; i++) {
			if (otvet[i] == ans[i]) {
				j++;
			}
		}
		cout << "Правильных ответов\t" << j << "\n";
		return 0;
}