﻿#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	int a = 0;
	int b = 0;
	cout << "Добро пожаловать на викторину!" << endl << "Тема викторины - столицы стран мира" << endl <<
		"Cтолица Сирии: 1)Латакия 2)Дамаск 3)Алеппо 4)Идлиб" << endl << "Ваш ответ: ";
	cin >> a;
	if (a == 2) { b = b + 1; }
	else { b = b; };
	cout << "Cтолица Австралии: 1)Канберра 2)Сидней 3)Мельбурн 4)Сейл" << endl << "Ваш ответ: ";
	cin >> a;
	if (a == 1) { b = b + 1; }
	else {
		b = b;
	};

	cout << "Cтолица Аргентины: 1)Асуньон 2)Сантьяго 3)Сан-Паулу 4)Буэнос-Айрес" << endl << "Ваш ответ: ";
	cin >> a;
	if (a == 4) { b = b + 1; }
	else {
		b = b;
	};

	cout << "Cтолица Колумбии: 1)Каракас 2)Кито 3)Богота 4)Лима" << endl << "Ваш ответ: ";
	cin >> a;
	if (a == 3) { b = b + 1; }
	else {
		b = b;
	};

	cout << "Cтолица Узбекистана: 1)Ашхабат 2)Ташкент 3)Бишкек 4)Душанбе" << endl << "Ваш ответ: ";
	cin >> a;
	if (a == 1) { b = b + 1; }
	else {
		b = b;
	};
	cout << "Ваша оценка:" << b << endl;
}