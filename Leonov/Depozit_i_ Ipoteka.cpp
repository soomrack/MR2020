#include <iostream>
#include <clocale>
// Всё считаем в копейках
using namespace std;
unsigned long int capital;//Начальный капитал
unsigned long int house_price_initial;//Первоночальная стоимость жилья
unsigned long int house_price;//Стоимость жилья
unsigned long int house_price1;//Тоже самое что и стоимость жилья, только нужное для подсчёта иптеки
unsigned long int total_mortgage_pay;//Сколько всего заплатит за ипотеку
unsigned int ph;//Процент на который возростает стоимость квартиры в год в сотых долях
unsigned int pd;//Процент по депзиту в год в сотых долях
unsigned int pi;//Процент по ипотеке в год в сотых долях
int deposit(const unsigned long int money, const unsigned long int month) // Функция по рассчёту сколько будет добавляться каждый месяц к капиталу
{
    unsigned long int increment;
    increment = 0;
    increment = (money * (pd * 0.0001)) / 12;
    return increment;
};
int house_price_value(const unsigned long int money, const unsigned long int month)// Функция которая считает на сколько будет расти стоимось жилья
{
    unsigned long int increment;
    increment = 0;
    increment = (money * (ph * 0.0001)) / 12;
    return increment;
};
int mortgage_pay(const unsigned long int money, const unsigned long int months)// Функция для подсчёта ипотеки
{
    unsigned long int month_mortgage_pay = money / months;
    unsigned long int mortgage = money;
    unsigned long int pay = 0;
    for (int month = 1; month <= months; month++)
    {
        mortgage = (mortgage * (pi * 0.0001)) / 12;
    }
    pay = mortgage/months;
    return pay;
};
int calculation (int months) {
    capital = capital * 100;
    house_price = house_price_initial * 100;
    house_price1 = house_price_initial * 100;
    for (unsigned int month = 1 ; month <= months ; month++) {//Главный цикл по расчёту
        capital += deposit(capital, month);
        house_price += house_price_value(house_price, month);
        total_mortgage_pay += mortgage_pay(house_price1,month);
    }
    cout << "Количество денег на депозите: "<< capital << endl;
    cout << "Стоимость квартиры: " << house_price << endl;
    cout << "Количество денег потраченое на ипотеку: " << total_mortgage_pay << endl;
    return 0;
}
int main()
{
    setlocale(LC_CTYPE, "rus");
    int time;
    cout << "Укажите на какое на какое количество месяцев вы будете открывать депозит/брать ипотеку: \n";
    cin >> time;
    cout << "Укажите начальный капитал: \n";
    cin >> capital;
    cout << "Укажите стоимость жилья: \n";
    cin >> house_price_initial;
    cout << "процент на который возростает стоимость квартиры в год: \n";
    cin >> ph;
    cout << "Какой процент по депозиту (укажите в сотых долях): \n";
    cin >> pd;
    cout << "Какой процент по ипотеке (укажите в сотых долях): \n";
    cin >> pi;
    calculation(time);
    
}

