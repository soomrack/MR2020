#include <stdio.h>
#include <math.h>

int main() {
int n = 10; //срок кредитования в годах
float kvartira = 1000000.0; //стоимость квартиры
float dohod = 10000.0;//зарплата
float kapital = 100000.0;//деньги на начало задачи
float kredit = 904500;//кредит с учетом процент до выдачи
float pribal = 0.0;

for (int i = 1; i <= 12*n; i++){
kapital = (kapital+dohod)*1.01;//рост суммы каждый месяц
if (i%12 == 0){
kapital =   kapital*0.97;//падение ценности накопленных денег
}
}
printf("Itogovaia summa na schetu - %.2f\n",kapital);

int i = 1;
int plata;
while (kredit > 0){
    kredit = (kredit - dohod)*1.005;//ставка 6%
            i++;
}
plata = dohod*i+kredit+kapital;
kvartira *=powf(1.02,10.0);//подорожание квартиры на рынке
printf("Summa za kvartiru: %d\nKolichestvo let: %.2f\nStoimost' kvartiri:%.2f\n",plata,(float)i/12,kvartira);

for (i =1; i<=12*5;i++){
    pribal += 20000;
    if (i%12 == 0){
        pribal *=0.97;
    }
}
printf("Pribil s kvartiri za 5 let: %.2f\nItogo kvartira: %.2f\n",pribal,kvartira+pribal);
    return 0;
}
