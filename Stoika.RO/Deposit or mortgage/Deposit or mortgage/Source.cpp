#include <iostream>
using namespace std;
//копейки
double a = 0;//option a
double b = 0;//option b
int otvet;
int n = 12;//mounth
int perc = 6;//percentage 
int income1 = 3000000;
int income2 = 5000000;
unsigned long long int house_price = 500000000;
double deposit(int mounth,int income,int money,double option) 
{
	int perc = 600;//percentage
	long long int deposit = money;
	for (int  current_mounth = 0; current_mounth < mounth; current_mounth++)
	{
		deposit += income;
		deposit *= (10000 + perc/12);
		deposit /= 10000;
	}
	option += (deposit);
	return option;
}

void mortgage_house_price(int mounth)
{
	int perc = 400;
	for (int current_mounth = 0; current_mounth < mounth; current_mounth++)
	{
		house_price *= (1000 + perc / 12);
		house_price /= 1000;
	}
	b +=house_price;
}

void mortgage(int mounth,int income)
{
	int i = 0;
	int perc = 1;
	long long int debt_reduction = income * 12;
	long long int otr= (500000000 * perc);
	otr /= 100;
	debt_reduction -= otr;

	if (debt_reduction<0)
	{
		otvet = 1;
		return;
	}
	long long int payout=0;
	while ((payout < 500000000) && (i < mounth))
	{
		payout += debt_reduction/12;
		i++;
	
	}
	if (payout < 500000000) 
	{
		otvet = 1;
		return;
	}
	payout=payout- 500000000;
	b=deposit((n - i), income2, payout, b);
}

int main() 
{ 
	a=deposit(n,income1,0,a);
	mortgage_house_price(n);
	mortgage(n, income2);
	if ((otvet==1)|| (a >= b))
	{
	cout << a <<  "better deposit";
	}
	else 
	{
		cout << b  << "better mortgage";
	}
}