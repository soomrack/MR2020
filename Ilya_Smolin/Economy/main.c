#include <stdio.h>
int monthskredit = 12*10;  //количество месяцев на которые берется кредит
int monthsoverall = 5*12; //количество месяцев на протяжении которых ведется анализ
float price = 3500000; //стоимость квартиры
float vznos = 500000; //стоимость первоначального взноса
float percent = 3.5; //процент по вкладу
float inflatia = 0.03; //процент инфляции
float kreditp = 0.09; //процент по кредиту годовой
int timebuild = 12*3; //количество месяцев на постройку квартиры
int timebuy = 12*2; //количество месяцев на постройку с момента покупки
int dohod = 15000; //ежемесячный доход с квартиры
float  boost = 0.2; //доход от повышения цены квартиры при покупке раньше, чем ее сдача
float kreditmonth; //ежемесячная сумма платежа
float stoimost; //Конечная стоимость квартиры
float dohodd; //Доход с квартиры
float stonkss; //Доход от вкладов

//Пользовательская функция расчета ежемесячного платежа (вклада)
float monthvklad (float qq, float kredit, int monthskredi, float vzno ){
   float ee =((qq-vzno)*(1+kredit)/12)/monthskredi;
    return ee;
}

//Пользовательская функция расчета конечной стоимости квартиры
float endflat (float pric, float boos, int timebuil, int timebu){
    float enfla = pric*(1+(boos-(boos/timebuil)*(timebuil-timebu)));
    return enfla;
}

//Пользовательская функция расчета дохода от квартиры после постройки
float dohodhata (float doho, int monthsoveral, int timeb){
    float dohodhat = doho*(monthsoveral-timeb);
    return dohodhat;
}

//Пользовательская функция расчета дохода от вклада
float stonks (float vzno, int monthsovera,float monthvkla, float percen, float inflat){
    float stonk = vzno;
    for (int i=1; i<=monthsovera;i=i+1 ){
        stonk = stonk*(1+(percen/(12*100)));
        stonk = stonk + monthvkla;
    }
        stonk = stonk*((1-inflat)*monthsovera/12);
    return stonk;
}
int main(void) {
kreditmonth = monthvklad (price, kreditp,monthskredit, vznos); //Cчитаем ежемесячный платеж (вклад)
stoimost = endflat (price, boost, timebuild, timebuy); //Считаем конечную стоимость квартиры
dohodd = dohodhata (dohod,monthsoverall,timebuy); //Считаем доход от квартиры
stonkss = stonks (vznos, monthsoverall, kreditmonth, percent, inflatia); //Считаем доход от вклада
printf("Dohod po kreditu:,%f\n",dohodd+stoimost);
    printf("Dohod po vkladu:,%f",stonkss);
}
