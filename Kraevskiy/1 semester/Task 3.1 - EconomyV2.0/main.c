#include <stdio.h>
#include <math.h>
int main(void){
    int MunthBezBabok1 = 5;   // номер месяца в котором не хватило денег для кредита/ипотеки
    int MunthBezBabok2 = 45;   // пусть их будет два
    int SrokProsrochki1 = 20;  // сколько дней осталось до зп или на сколько брать микрозайм или насколько просрочена дата платежа
    int SrokProsrochki2 = 6;
    float kap = 1000000.0, doh = 20000.0; // капитал, доход
    int i, n = 9;
    int Pereplata1 = doh*powf(1.007, SrokProsrochki1)-doh; // переплата слуае отсутсвия денег для кредита/депозита
    int Pereplata2 = doh*powf(1.007, SrokProsrochki2)-doh;
    for (i = 1; i <= 12*n; i++){
        if (i==MunthBezBabok1) kap += Pereplata1;
        if (i==MunthBezBabok2) kap += Pereplata2;

        kap = (kap + doh)*1.0055; // под процент годовых 6,6 (месячный 0,55)

        //if (i%12 == 0)2
        //    kap *=0.96; // ежегодная инфляция 4% (итоговая сумма будет в рублях = рублям на момент покупки)
    }
    printf("Itogovaya summa na vklade: %.2f\n", kap);

    int vpl; // выплаты за квартиру
    float kr = 1510500.0, stkv = 2500000.0; // кредит с учетом облажения процентом до начала выплат, стоимость квартиры
    i = 1;
    while (kr > 0){ // пока не погасим кредит
        if (i==MunthBezBabok1) doh += Pereplata1; // учет внепланого получения микрозайма
        if (i==MunthBezBabok2) doh += Pereplata2;
        kr = (kr - doh)*1.007; // ставка по кредиту 8,4%
        i++
                ;
    }
    vpl = doh*i + kr + 1000000; // средства потраченные на квартиру(+kr - вычет переплаты при последнем платеже)
    stkv *= powf(1.05, 8.0);    // стоимость квартиры в начальных рублях с учетом удорожания на 5% в год
    //stkv *= 1.3;

    printf("Summ viplat za kv: %d\nKolichestvo let %.2f\nStoimist' kv na prodazhu:%.2f\n", vpl, (float)i/12, stkv);

    float sdach = 0.0;
    for (i = 1; i <= 12*7; i++){ // если квартира 2 года строилась, а в ее сумму мы включили отделку и минимум мебели
        sdach += 15000; // тк квартира с отделкой и мебелью 2,5 млн, то и аренда 15к
    //    if (i%12 == 0)
    //        sdach *=0.96; // деньги которые получали с квартиры просто лежали
    }
    printf("Den'gi so sdachi kvartiri: %.2f\nItogo plan s kvartiroi: %.2f\n", sdach, sdach+stkv);
    return 0;
}
