#include <iostream>
#include <Math.h>

int Salary; 
int Ipoteka;
int month;
float   interest_rate;
float monthly_payment;
float payment;
float S = 0;
int money;

float annuity_payment(int Ipoteka, int month, float interest_rate) {
    interest_rate = interest_rate / 100;
    monthly_payment = Ipoteka * (interest_rate + (interest_rate / (((1.0 + pow(interest_rate, month)) - 1))));
    payment = monthly_payment * month - Ipoteka;
    return payment;
}

float the_differentiated_payment(float iterest_rate, int month, int Ipoteka) {
    payment = (interest_rate / 200) * (month + 1) * Ipoteka;
    return payment;
}

float deposit(int month, int Salary, int money) {
    int i = month;
    S = money * ((1 + ((0.136 * 30) / 365)));
    while (i == 1) {
        S = (S + (0.5 * Salary)) * ((1 + ((0.136 * 30) / 365)));
        --i;
    }
    float deposit_pay = Ipoteka - S;
    return deposit_pay;
}

void WHATAAA() {
    if ((money > 0.2 * Ipoteka) || (month > 6)) {
        float a = annuity_payment(Ipoteka, month, interest_rate);
        float b = the_differentiated_payment(interest_rate, month, Ipoteka);
        float c = deposit(month, Salary, money);
        if (a < b) {
            if (a < c) {
                std::cout << "More profitable annuity payment";
            }
            else {
                std::cout << "More profitable deposit";
            }
        }
        else {
            if (b < c) {
                std::cout << "More profitable the differentiated paymen";
            }
            else {
                std::cout << "More profitable deposit";
            }
        }
    }
    else {
        std::cout << "More profitable deposit" ;
    }
}

int main()
{
    std::cout << "Salary\n";
    std::cin >> Salary; 
    std::cout << "How much ipoteka\n";
    std::cin >> Ipoteka;
    std::cout << "loan period (month)\n";
    std::cin >> month;
    std::cout << "Interest rate\n";
    std::cin >> interest_rate;
    std::cout << "How many money you have?\n";
    std::cin >> money;
    std::cout << "Youer  salary " << Salary << "\n"
        << "Loan amount " << Ipoteka << "\n"
        << "Loan period " << month << "\n"
        << "Interest rate " << interest_rate << "\n";
        WHATAAA();
        
}

