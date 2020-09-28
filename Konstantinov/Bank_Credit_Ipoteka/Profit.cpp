//
// Created by Alex on 21.09.2020.
//
#include "Profit.h"
#include <iostream>

using namespace std;

Credit Flat;
Credit Debet;

//uint32_t CalcCapital(){
uint32_t Calc_Capital(uint32_t First_Part, double Credit_Percent, double Vklad_Percent, uint8_t Years, uint32_t Salary, uint32_t Flat_Cost){
    //Vklad
    uint32_t Vklad = 0;
    Vklad += First_Part;
    for(uint8_t i = 0; i<= Years*12; i++){
        Vklad += Salary;
        Vklad *= (1+Vklad_Percent/12);
    }

    uint32_t Flat = 0;
    Flat = Flat_Cost;
    return Vklad;
/*
    while(Flat > 0){
        uint32_t Flat_Old = Flat;
        Flat -= Salary*12;
        Flat *= (1+Credit_Percent);
        if (Flat_Old < Flat){
            Flat_Cost = 0;

        }
    }
    */
}

uint32_t Calc_Credit(uint32_t First_Part, double Credit_Percent, uint8_t Years, uint32_t Salary, uint32_t Flat_Cost) {

    int64_t Flat = 0;
    Flat = Flat_Cost;
    Flat -= First_Part;
    uint16_t Months = Years*12;
    while (Flat > 0 && Months) {
        uint32_t Flat_Old = Flat;
        Flat -= Salary;
        Flat *= (1 + Credit_Percent/12);
        if (Flat_Old < Flat) {
            std::cout << "Flat_Old<Flat " << Flat_Old << std::endl;
            return 0;

        }
        Months--;

    }
    std::cout << Months << std::endl;
    return Flat;
}
/*
Credit Calc_Flat(struct Credit *Flat){


    uint64_t Dolg = Flat->Flat_Cost;
    uint64_t *ptrNew_Cost = &Flat->New_Flat_Cost;
    //*ptrNew_Cost = Flat->Flat_Cost;
    Flat->New_Flat_Cost = Flat->Flat_Cost;
    uint16_t * ptrMonths = &Flat->Months;
    *ptrMonths = 0;
    uint16_t PotrMotnhs = 0;
    uint16_t Months = Flat->Years*12;
    uint64_t * ptrPotr = &Flat->Potracheno;
    *ptrPotr = 0;
    *ptrPotr += Flat->First_Part;
    Dolg -= Flat->First_Part;
    uint64_t Last_Dolg;

    for (uint16_t i = 0; i < Flat->Years; i++)
        Flat->New_Flat_Cost *= ( 1+ Flat->Flat_Percent); //New Cost of the Flat

    while (Dolg > 0 && (Dolg < Flat->Flat_Cost or Flat->First_Part == 0) && Dolg > Flat->Salary && Months){
        Last_Dolg = Dolg;
        Dolg -= Flat->Salary;
        *ptrPotr += Flat->Salary;
        Dolg *= (1+(Flat->Credit_Percent)/12);
        if(Last_Dolg < Dolg){
            //You should have a bigger salary(); ))
            std::cout << "Last_Dolg = " << Last_Dolg << " Dolg = " << Dolg << std::endl;
            break;
        }
        *ptrMonths += 1;
        //PotrMotnhs++;
        Months--;

    }

    if (Dolg > 0 && Dolg <= Flat->Salary){
        *ptrPotr += Dolg;
        Dolg = 0;
    }
    if(Dolg > 0){
        std::cout << "Dolg = " << Dolg << std::endl;
    }
    if(Months > 0 ){
        Flat->Debet_Months = Months;
        cout << "Months = " << Months << endl;
        cout << "ptrMonths = " << *ptrMonths << endl;

        Flat->First_Part = Flat->Salary;

        Calc_Debet(Flat);

    }
    Flat->Cash += *ptrNew_Cost;
    Flat->Cash += Flat->Cash;
//    Flat->Months = PotrMotnhs;
return *Flat;
}

*/

Credit Calc_Flat(struct Credit *Flat){

    uint64_t Dolg_Old; // Older value of Dolg, to compare it with new value
//    uint64_t Months_Ostlos; // Not needed?
    uint64_t Ostalos_ot_Salary = 0; // If it will be needed
    Flat->Months = 0;
    Flat->Flat_Dolg = Flat->Flat_Cost;
    Flat->Flat_Dolg -= Flat->First_Part;
    Flat->New_Flat_Cost = Flat->Flat_Cost;
    for (uint16_t i = 0; i < Flat->Years; i++)
        Flat->New_Flat_Cost *= ( 1 + Flat->Flat_Percent); //New Cost of the Flat


    while((Flat->Flat_Dolg < Flat->Flat_Cost or Flat->First_Part == 0) && Flat->Flat_Dolg > Flat->Salary && Flat->Months <= Flat->Years * 12){
        Dolg_Old = Flat->Flat_Dolg;
        Flat->Flat_Dolg -= Flat->Salary;
        Flat->Potracheno += Flat->Salary;
        Flat->Flat_Dolg *= (1+Flat->Credit_Percent/12);
        if (Dolg_Old < Flat->Flat_Dolg){
            cout << "Needed a bigger salary))" << endl;
            break;
        }
        Flat->Months += 1;

    }

    if (Flat->Flat_Dolg > 0 && Flat->Flat_Dolg <= Flat->Salary){
        Ostalos_ot_Salary = Flat->Salary - Flat->Flat_Dolg;
        Flat->Potracheno += Flat->Flat_Dolg;
        Flat->Flat_Dolg = 0;

    }
    if (Flat->Months < Flat->Years*12){
        Flat->First_Part = Ostalos_ot_Salary;
        Flat->Debet_Months = Flat->Years*12 - Flat->Months;
        Calc_Debet(Flat);
    }

    Flat->Cash += Flat->New_Flat_Cost;
    Flat->Cash -= Flat->Flat_Dolg;

    return *Flat;
}



Credit Calc_Debet(struct Credit *Debet){
    uint64_t *ptrCash = &Debet->Cash;
    *ptrCash = 0;

    *ptrCash = Debet->First_Part;

    uint64_t *ptrPotr = &Debet->Potracheno;
    //uint16_t Months = Debet->Years*12;
    //Debet->Months = 0;
    uint16_t *ptrMonths = &Debet->Debet_Months;
    //*ptrMonths = 0;

    while(*ptrMonths){
        *ptrCash += Debet->Salary;
        *ptrCash *= (1 + Debet->Debet_Percent/12);
        *ptrPotr += Debet->Salary;
        *ptrMonths -= 1;
    //    Debet->Months += 1;
    }
    return *Debet;
}


void Credit_Debet_Init(void){
    Credit Situation;
    struct Credit * ptrCredit = &Situation;
    cout << "Credit-Debet Properties" << endl;
    cout << "Flat Cost: " << endl;
    //cin >> ptrCredit->Flat_Cost;
    ptrCredit->Flat_Cost = 10000000;
    ptrCredit->Flat_Cost *= 100;
    cout << "Credit percent: " << endl;
    //cin >> ptrCredit->Credit_Percent;
    ptrCredit->Credit_Percent = 0.1;
    cout << "Flat cost increasing percent: " << endl;
    //cin >> ptrCredit->Flat_Percent;
    ptrCredit->Flat_Percent = 0.05;
    cout << "First part: " << endl;
    //cin >> ptrCredit->First_Part;
    ptrCredit->First_Part = 1000000;
    ptrCredit->First_Part *= 100;
    cout << "Salary: " << endl;
    //cin >> ptrCredit->Salary;
    ptrCredit->Salary = 250000;
    ptrCredit->Salary *= 100;
    cout << "Vklad percent: " << endl;
    //cin >> ptrCredit->Debet_Percent;
    ptrCredit->Debet_Percent = 0.05;
    cout << "Years: " << endl;
    //cin >> ptrCredit->Years;
    ptrCredit->Years = 20;
    ptrCredit->Debet_Months = ptrCredit->Years*12;

    Calc_Flat(ptrCredit);
    //ptrCredit->Debet_Cash = 0;
    Calc_Debet(ptrCredit);
    cout << "Debet Cash = " << ptrCredit->Cash << endl;
    cout << "Flat Cash = " << ptrCredit->Cash << endl;
    cout << "Flat Months = " << ptrCredit->Months << endl;



}