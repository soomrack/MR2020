#include <stdio.h>
#include <math.h>

int zp = 50000; // Cумма прибавки к зарплате
int const vz = 1000000; // первоначальный капитал
int const kv = 6000000; // стоимость квартиры
int god = 10; // число годов

int main(void) {
    int prem = 1.3 * zp, vz1, summaitog, kv1 = kv;
    int plateg = kv / (god * 12);
    int summa = 0;
    for (int i = 1; i <= god; i++){
        vz1 += (zp * 12) * 1.06;
        vz1 += prem;// добавление ежегодной премии
    vz1 *= 1.06;}
        for (int i = 1; i <= god; i++){
            summa += kv1 - (kv1 - plateg * 12) * 1.08;// сумма переплаты;
            kv1 -= summa;
        }
        for (int i = 1; i<=god; i++){
    summaitog = kv * 1.03;} // процент инфляции
        summaitog *= 1.3; //девальвация
        summaitog -= 500000;// вычитаем сумму на ремонт и отделку квартитры
        int sdacha = 30000;
    for (int i = 1; i <= (god -2) * 12; i++) {
        summaitog += sdacha; //суммируем сдачу квартиры после 2 лет ремонта
    }
    vz1 -= (vz + (zp * god * 12) + prem * god); //считаем прибыль с вклада
   summaitog -= (kv + summa);// считаем прибыль с квартиры

    printf("Profit s vklada:  %d\n", vz1);
    printf("Profit s vlada:  %d\n", summaitog);// В данных условиях вклад выгоднее
    return 0;
}
