// Project "Optimization of investments - what is more profitable than a mortgage or a deposit?"


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>


int calc_credit(int price, float rate, int term,
                float rise_in_value, int initial_capital,
                int aver_exps);

int calc_deposit(int initail_capital, float rate, int term);


int main(int argc, char const *argv[])
{
    using namespace std;
    
    // init veriables
    int income = 0;
    int mort_init_pay = 0;
    int mort_costs = 0;
    int init_cap = 0;
    int dep_perc = 0;
    int dep_cap = 0;
    int apart_incr = 0;
    int apart_rent = 0;
    int initial_capital = 0;
    int term = 0;
    int price = 0;
    int loan_rate = 0;
    
    // input data
    cout << "Enter your unconditional income:" << endl;
    cin >> income;
    cout << "Enter mortgage data:" << endl;
    cout << "initial payment:" << endl;
    cin >> mort_init_pay;
    cout << "costs:" << endl;
    cin >> mort_costs;
    cout << "due date (n year):" << endl;
    cin >> term;
    cout << "price of apartment:";
    cin >> price;
    cout << "Enter mortgage rate" << endl;
    cin >> loan_rate;
    cout << "Enter deposit percentage:" << endl;
    cin >> dep_perc;
    cout << "Enter deposit monthly capitalization:" << endl;
    cin >> dep_cap;
    cout << "Enter the annual increase in the cost of the apartment (percentage):" << endl;
    cin >> apart_incr;
    cout << "Enter the income from the apartment per month (for example, renting the apartment):" << endl;
    cin >> apart_rent;
    cout << "Enter initial capital" << endl;
    cin >> initial_capital;
    
    // Calling Calculation Functions and Comparing Results  
    int income_from_credit = calc_credit(price, loan_rate, term, apart_incr, 
                initial_capital, mort_costs);

    int income_from_deposit = calc_deposit(initial_capital, dep_perc, term);

    if (income_from_credit > income_from_deposit){
        printf("Credit is more profitable\n");
        printf("Income from credit is %d\nIncome from deposit is %d\n", 
                income_from_credit, income_from_deposit);
    }

    else if (income_from_credit < income_from_deposit){
        printf("Deposit is more profitable\n");
        printf("Income from credit is %d\nIncome from deposit is %d\n", 
                income_from_credit, income_from_deposit);
    }

    else{
        printf("Deposit is equal to credit\n");
        printf("Income from credit is %d\nIncome from deposit is %d\n", 
                income_from_credit, income_from_deposit);
    }    

    return 0;
}


// calculating of credit
int calc_credit(int price, float rate, int term,
                float rise_in_value, int initial_capital,
                int aver_exps){

    float credit_value = price - initial_capital;

    // Calculating of payment per month asdasd
    float rate_per_month = rate / 12 / 100;
    float annuate = rate_per_month * (1 + rate_per_month) /
                    (pow((1 + rate_per_month), term * 12) - 1);
    float payment = credit_value * annuate;

    // Adding aver_axps to payment
    payment += aver_exps;

    //Calculating of apartment price at the end of term
    float apartment_price = price;
    for (int i = 0 ; i < term; i++){
        apartment_price += apartment_price * rise_in_value / 100;
    }

    float income = apartment_price;
    float loss = initial_capital + payment * 12 * term;



    return income - loss;
    
}

//calculating of deposit
int calc_deposit(int initail_capital, float rate, int term){
    
    float deposit = initail_capital;

    for (int i = 0; i < term; i++){
        deposit += deposit * rate/100;
    }

    return deposit;
}

