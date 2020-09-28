#include <iostream>
#include <cmath>
using namespace std;

//Функция Ипотека - возвращает, cколько выплатим по ипотеке (стоимость квартиры, т.е., наш капитал), меняет (задаёт) срок ипотеки (переменная t_mor)
double Ipoteka(double Sum, double x, double y, double p_mor) {
	double Sum_Mortgage = Sum - y; //вычитаем первоначальный взнос
 	Sum_Mortgage = (Sum_Mortgage * p_mor) / (1 - (1 / (1 + p_mor ))); //сколько будем платить по ипотеке
	double t_mor = Sum_Mortgage / x ; //срок ипотеки при выплатах Х в месяц
	return Sum_Mortgage;
}
//Функция - Выгода с оставшихся с ипотеки денег, положенных под депозит.
double Ipoteka_Dep(double Sum, double x, double y, double &t_mor, double t_dep, double z_dep, double p_mor) {
	double sum_mor_last = Ipoteka(Sum, x,y, p_mor) -x* floor(t_mor); //последняя выплата
	t_mor = ceil(t_mor);
	int tt_mor = (int)t_mor;
	double remainder_mor = x - sum_mor_last; //положим под депозит в банк остаток после последнего взноса по ипотеке
	double Sum_dep_mor;
		if (tt_mor < (t_dep * 12)) {
			Sum_dep_mor = remainder_mor + x * (tt_mor % 12); //и до конца года ещё будем вносить платежи на вклад 
			Sum_dep_mor = Sum_dep_mor * pow((z_dep + 1), (t_dep - (tt_mor/12))); //проценты начислены в конце года
			for (int i = 1; i <= (t_dep - (tt_mor / 12)); i++) { //и платим оставшийся срок
				Sum_dep_mor = Sum_dep_mor + x * 12 * pow((z_dep + 1), i);
			}
		}
		Sum_dep_mor = Sum_dep_mor + x * (tt_mor % 12);
		return Sum_dep_mor;
}
//Функция - Увеличение стоимости квартиры из-за инфляции
double Inflation(double Sum, double r_inflation, double t_dep) {
	double Sum_inflation = Sum * pow((r_inflation + 1), t_dep);
	return Sum_inflation;
}
//Функция - Сколько будет на депозите
double Deposite(double y, double x, double z_dep, double t_dep) {
	double Sum_dep = y * pow((z_dep + 1), t_dep);
	for (int i = 1; i < t_dep; i++) {
		Sum_dep += x * 12 * pow((z_dep + 1), i);
	}
	return Sum_dep;
}

int main() {
	setlocale(LC_ALL, "Rus");
	//Входные данные (вводятся пользователем, но конкретно сейчас - уже введены мной)
	double x = 50000;         //Доход в месяц - Х рублей/мес
	double y = 1000000;       //Начальный капитал - У руб
	double t_dep = 10;        //Срок - T лет
	double Sum = 2100000;     //Цена квартиры - Sum руб
	double z_dep = 0.04;      //Депозит - Z %/год
	double v_mor = 1000000;   //Ипотека: первоначальный взнос - V руб. Для простоты - совпадает с суммой накопленного.
	double p_mor = 0.2;        //Ипотека: процент - P %/год
	double r_inflation = 0.03; //Рост стоимости квартиры - R %/год
	double VI=0, VD=0;        //Выгода по ипотеке и по депозиту соответственно
	double t_mor = Ipoteka(Sum, x, y, p_mor) / x;        //Срок выплаты ипотеки, месяцев

	VD = Deposite(y, x, z_dep, t_dep)-y-x*t_dep*12;
	VI = Inflation(Sum, r_inflation, t_dep) - y - Ipoteka(Sum, x, y, p_mor) + Ipoteka_Dep(Sum, x,y, t_mor, t_dep, z_dep, p_mor) - x * (t_dep - Ipoteka(Sum, x, y, p_mor) / x);
	cout << VD << " " << VI;
	return 0;
}