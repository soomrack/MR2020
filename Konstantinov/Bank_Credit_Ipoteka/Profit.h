//
// Created by Alex on 21.09.2020.
//

#ifndef BANK_CREDIT_IPOTEKA_PROFIT_H
#define BANK_CREDIT_IPOTEKA_PROFIT_H
#include <iostream>

struct Credit{

    float Credit_Percent; //Процент кредита
    float Flat_Percent; //Инфляция
    uint64_t Flat_Cost; //Стоимость квартиры
    uint64_t Flat_Dolg; // Долг по квартире
    uint64_t New_Flat_Cost; //Стоимость с учётом инфляции
    uint64_t Salary; // ЗП
    uint64_t First_Part; //Первый взнос
    uint8_t Years; //Кол-во лет
    uint64_t Potracheno; //Потрачено денег
    uint16_t Months; // Выплачен кредит
    uint16_t Debet_Months; // Месяцев для вклада
    uint64_t Cash; // Кол-во денег в конце срока вклада/кредита
    //uint64_t Flat_Cash;
    float Debet_Percent; // Процент по вкладу
    //uint64_t Debet_Sum; // Сумма вклада. Нужна ли?
    int64_t Profit;
};

//uint8_t Years;

uint32_t Calc_Capital(uint32_t First_Part, double Credit_Percent, double Vklad_Percent, uint8_t Years, uint32_t Salary);
uint32_t Calc_Credit(uint32_t First_Part, double Credit_Percent, uint8_t Years, uint32_t Salary, uint32_t Flat_Cost);
Credit Calc_Flat(struct Credit *Flat);
Credit Calc_Debet(struct Credit *Debet);
void Credit_Debet_Init();

#endif //BANK_CREDIT_IPOTEKA_PROFIT_H
