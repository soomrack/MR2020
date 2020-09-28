#include <iostream>
#include "Profit.h"

using namespace std;

int main() {
    Credit Flat;
    //Credit_Debet_Init();
    Flat.Flat_Cost = 10000000*100;
    Flat.Salary = 250000*100;
    Flat.Credit_Percent = 0.10;
    Flat.Flat_Percent = 0.05;
    Flat.Debet_Percent = 0.05;
    Flat.Years = 20;
    Flat.First_Part = 1000000*100;
    cout << "Begin" <<endl;
    Calc_Flat(&Flat);
    cout << "Potracheno " << Flat.Potracheno/100 << endl;
    cout << "Months = " << Flat.Months << endl;
    cout << "Cash = " << Flat.Cash/100 << endl;
    cout << "Flat New Cost " << Flat.New_Flat_Cost/100 << endl << endl;

    Credit Debet;
    Debet.Debet_Percent = 0.05;
    Debet.Salary = Flat.Salary;
    Debet.Years = 20;
    Debet.Debet_Months = Debet.Years*12;
    //Debet.Months = 0;
    Debet.Potracheno = 0;
    Debet.First_Part = Flat.First_Part;
    Calc_Debet(&Debet);
    cout << "Potracheno " << Debet.Potracheno/100 << endl;
    cout << "Months = " << Debet.Debet_Months << endl;
    cout << "Cash = " << Debet.Cash/100 << endl << endl;

    Flat.Profit = Flat.Cash - Debet.Cash - (Flat.Potracheno - Debet.Potracheno);
    Debet.Profit = -Flat.Profit;
    //    Debet.Profit = Debet.Cash - Flat.Cash - (Debet.Potracheno - Flat.Potracheno);

    cout << "Flat profit = " << Flat.Profit << endl;
  //  cout << "Debet profit = " << Debet.Profit << endl;

    if (Flat.Profit > 0){
        cout << "Flat profit = " << Flat.Profit / 1000000 << " " << (Flat.Profit % 1000000) / 1000 << " " << (Flat.Profit % 1000) << endl;
    } else if (Debet.Profit > 0 ){
        cout << "Debet profit = " << Debet.Profit << endl;
    } else
        cout << "Profit = 0";

//    cout << "Flat_cost*(Credit_Percent+1) = " << Flat.Flat_Cost * (1 + (Flat.Credit_Percent)/12) << endl;
    /*
    uint32_t First_Part = 100000;
    double Credit_Percent = 0.05;
    double Vklad_Percent = 0.05;
    uint8_t Years = 10;
    uint32_t Salary = 15000;
    uint32_t Flat_Cost = 1000000;
    */
     //int32_t Flat = Calc_Credit(First_Part, Credit_Percent, Years, Salary, Flat_Cost);

    //std::cout << Flat;

        return 0;
}
