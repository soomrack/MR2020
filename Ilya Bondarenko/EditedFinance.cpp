#include <iostream>
#include <cmath>
using namespace std;

// Edited by Panteleev M. D.

int main()
{
	setlocale(LC_ALL, "Rus");
	float d1=0;
	float x, y,z, t, n;
    n = 0;
	// программа для подсчета выполаты по ипотеке 
	//начало

	float stavka, ttt, mstavka, os, emp, od, pch, och, x2, sk, pow1, time, total,total1;
	int n1, n2;
	cout << "Введите процентную ставку годовых: ";
	cin >> stavka;
	cout << "Введите количество лет ипотеки: ";
	cin >> ttt;
	cout << "Введите сумму кредита: ";
	cin >> sk;
	cout << endl << "Введите ежемесячный доход: ";
	cin >> x2;
	n1 = 0;
	n2 = 0;
	mstavka = stavka / 12 / 100;    // находим ежемесячную ставку
	ttt = ttt * 12; // срок ипотеки в месяцах
	pow1 = 1 + mstavka;
	os = pow(pow1, ttt); //находим общую ставку 
	emp = sk * mstavka * os / (os - 1);// находим ежемесячный платеж
	od = sk;// приравниваем остаток долка к сумме кредита
	total = emp * ttt;
	total1 = total;
	cout << "Ежемесячный платеж :  " << emp << endl;
	cout << "Количество долга :  " << total << endl;
	n1 = 0;
    while (total >= 0 )
	{
		total = total - emp-x2;
		n1 = n1 + 1;
		n2 = n2 + 1;
	}
	n1 = n1/12;
	n2 = n2 ;
	n2 = n2 % 12;
	cout << "Количество времени, через которое будет выплачена вся сумма: " << n1 <<" лет" << endl <<n2 <<" месяцев"<< endl;
	cout << "остаток: " << (total1 - n1 * 12 * (emp + x2) - (n2) * (emp + x2)) * (-1) << endl << endl;
	//конец

		// программа для подсчета стоимости квартиры после инфляции
	// начало
	float ct, tt, a = 0, prozent;
	cout << "Введите процент инфляции: ";
	cin >> prozent;
	cout << "Введите стоимость квартиры: ";
	cin >> ct;
	cout << "Введите количество лет: ";
	cin >> tt;
	
	
	
	int month = rand() % (int)tt+1;
	while (a < tt)
	{ 
		if (a==month)		//В один из месяцев недвижимость растет в цене (открыли рядом метро)
		{
			cout << "Wow! Your property greatly increased in price!" << '\n';
			ct += 300000;
		}
		
		ct = ct * (1 + prozent / 100);
		a = a + 1;
	}
	cout << "Стоимость квартиры через " << tt << " лет (года)" << ct << endl << endl;
	//конец

	// программа для подсчета средств при депозите
	//начало
	cout << "Введите начальный капитал: ";
	cin >> d1;
	cout <<  "Введите доход: ";
	cin >> x;
    cout <<  "Введите процент годовых депозита: ";
	cin >> z;
	cout <<  "Введите срок депозита: ";
	cin >> t;
	
	int probability = rand()%100+1;
	
	
	int year = rand() % (int)t +1;
	while (n<t)
	{   
		if (probability >= 92 && year == n) 		//С определенной вероятностью в один из годов может обанкротиться банк
		{
			cout << "Bank went buckrupt! You lost some of your money" << '\n';
			d1 -= 600000;
		}
		
		
		d1 = d1* (1 + z / 100);
		d1 = d1 + x * 12;
		n = n + 1;
	}
	cout << d1 << endl;
	//конец

	if (d1>=ct)
	{
		cout << endl << "Сумма,находящаяся в банке позволяет купить квартиру.";
	}
	else {
		cout << "Сумма,находящаяся в банке не позволяет купить квартиру.";
	}
}

