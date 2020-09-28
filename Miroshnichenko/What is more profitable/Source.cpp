#include <iostream>
using namespace std;

long int Percent,Rise,Time,Mrtr,SumDep,Mnth, Initial, SumIp, Mrtp, Add,ValueAp;
double otv1,otv2,otv3;

void Init() {
	cout << "Enter your available funds every month\n";
	cin >> Mnth;
	cout << "Enter your initial capital\n";
	cin >> Initial;
	cout << "Enter interest rate\n";
	cin >> Percent;
	cout << "Enter rise in apartment value\n";
	cin >> Rise;
	cout << "Enter time (years)\n";
	cin >> Time;
	cout << "Enter mortrage rate\n";
	cin >> Mrtr;
	cout << "Enter mortrage payment\n";
	cin >> Mrtp;
	cout << "Enter additional income\n";
	cin >> Add;
	Mnth = Mnth * 100;
	Initial = Initial * 100;
	Mrtp = Mrtp * 100;
	Add = Add * 100;

}

void Sumwithout() {//Доход с депозита
	SumDep = Initial;//Первоначальный взнос
	for (int i = 0; i < Time; i++) {
		SumDep += (SumDep * Percent/100 + 12 * Mnth);
	}
}

void Sumwith() {//Доход с ипотеки (после выплаты кладём деньги на депозит)
	long int Debt;
	SumIp = 0;
	Debt = Mrtp;//Первоначальный долг
	Debt -= Initial;//Первоначальный взнос
	
	for (int i = 0; i <Time; i++) {
		for (int j = 0; j < 12; j++) {
			//Пока есть долг платим ипотеку ежемесячно
			if (Debt > 0) {
				Debt -= (Mnth + Add);
				Debt += (Debt * Mrtr / 1200);
			}
			else {
				//Если долга нет ежегодно получаем проценты с депозита
				if (j != 11) {
					SumIp += (Mnth + Add);
				}
				else {
					SumIp = SumIp * Percent/100 + Mnth + Add;
				}
			}
		}
	}
	cout << "Debt left " << Debt/100 << "\n";

}

void Stkv() {//Стоимость квартиры (растёт в цене)
	ValueAp = Mrtp;
	for (int i = 0; i < Time; i++) {
		ValueAp += (ValueAp * Rise/100);
	}
}

int main() {
	Init();
	Stkv();
	Sumwith();
	Sumwithout();
	cout << "Deneg posle deposita ";
	cout << SumDep/100; 
	cout << "\n";
	cout << "Deneg posle ipoteki ";
	cout << SumIp/100; 
	cout << "\n";
	cout << "Deneg stoit kvartira ";
	cout << ValueAp/100;
	return 0;

}