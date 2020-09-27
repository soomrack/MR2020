#include <iostream>
using namespace std;
/*
 * Что выгоднее ипотека или вклад?
 *
 * Регулярно откладывается money либо в ипотеку, либо на вклад
 * Ипотека - раходы plateg, есть первоначальный взнос nakopleniya, срок srok
 * Депозит даёт pr_dep % годовых, накопления
 * Квартира растет в цене pr_kv %
 *
 * Капитал состоит из: фин. активов и квартиры
 *
 * Дополнительно: квартиру можно сдавать в аренду за arenda
 */
int main() {

    int money = 20000; // сколько можем откладывать/платить за ипотеку
    int nakopleniya = 500000; //сколько уже накоплено

    int P_kv = 2300000; //стоимость квартиры
    int pr_kv = 7; //ставка по ипотеке
    int inf_kv = 3; //процент ежегодного повышения стоимости квартиры
    int pr_dep = 4; //процент по депозиту
    int inf_mon = 5; //денежная инфляция
    int mes = 120; //количество месяцев, которые рассмотрим

    //рассчитаем ниже
    int ipoteka = 0; //общая сумма, которую должны банку, когда только взяли ипотеку
    int dolg_pr = 0; //долг по процентам, когда только взяли ипотеку
    int srok = 0; //срок ипотеки в месяцах

    int ostatok = 0; //остаток по ипотеке
    int kapital_ip = nakopleniya; //накопленный капитал, если берем ипотеку
    //после того, как погасим ипотеку, создаём вклад
    int kapital_ip_dep = 0; // в этой переменной будет хранится эта часть капитала
    int kapital_dep = nakopleniya;//накопленный капитал, если создаём вклад

    //Общая сумма, которую должны банку
    ipoteka = (P_kv - nakopleniya)*(1 + pr_kv*0.01);

    //Долг по процентам
    dolg_pr = (P_kv - nakopleniya)*pr_kv*0.01;

    //Рассчитаем срок ипотеки
    srok = ipoteka/money;     // Так как srok - int, запишется только целая часть от деления
    if (ipoteka/money > 0) {  // Проверяем есть ли остаток, который надо учесть
        srok++;
    }

    //ИПОТЕКА
    cout << "IPOTEKA"<< endl;
    cout << "month....payment......general debt......debt %......capital" << endl;
    for (int i = 1; i <= mes; i++){ //сначала гасим долг по проц, по том за саму кв
        kapital_ip += kapital_ip*0.01*inf_kv/12; //квартира ежемесячно растёт в цене
        if (i < srok){
            ostatok = ipoteka - money*i;
            if (dolg_pr == 0){ //если погасили долг по проц, начинаем деньги вкладывать в саму кварт.
                kapital_ip += money;
            }
            if (dolg_pr >= money){ //проверяем, чтобы долг по процентам был больше платежа
                dolg_pr -= money; //сначала платим проценты, потом за саму квартиру
            } else if (dolg_pr > 0){ //долг по проц. меньше платежа, поэтому погашаем долг по проц., а остаольное по кв.
                kapital_ip += (money - dolg_pr);
                dolg_pr = 0;
            }
        } else if (i == srok){
            // money = ostatok; платеж равен остатку
            kapital_ip +=money;
            ostatok = 0;
        } else{ //т.е. когда ипотека погашена, создаём вклад
            kapital_ip_dep += kapital_ip_dep*pr_dep*0.01/12; //Добавляем процент
            kapital_ip_dep += money; //кладём деньги
            kapital_ip_dep *= (1 - inf_mon*0.01/12); //инфляция съедает часть средств
        }
        cout<<i<<"........."<<money<<"........."<<ostatok<<"........."<<dolg_pr<<"........."<<kapital_ip+kapital_ip_dep<<endl;
    }

    //ДЕПОЗИТ
    cout << "DEPOSIT"<< endl;
    cout << "month....payment......capital" << endl;
    for (int i = 1; i <= mes; i++){
        kapital_dep += kapital_dep*pr_dep*0.01/12; //Добавляем процент
        kapital_dep += money; //кладём деньги
        kapital_dep *= (1 - inf_mon*0.01/12); //инфляция съедает часть средств
        cout<<i<<"........."<<money<<"........."<<kapital_dep<<endl;
    }

    if (kapital_dep > kapital_ip+kapital_ip_dep){
        cout << "Deposit";
    } else{
        cout << "Ipoteka";
    }
    return 0;
}
