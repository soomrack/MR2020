#include <iostream>
using namespace std;

// #define MORTGAGE_PARAMETERS 5;
// #define DEPOSIT_PARAMETERS 3;

int salary = 150020;
int initialCapital = 2000000;
int timeInMonths = 180;
float annualCostIncrease = 0.01;
int rental = 20000;

struct Mortgage{

    int initialFlatCost = 7000000;
    float annualInterest = 0.15;
    float monthlyPayments = 0.4 * salary;
    int initialFee = initialCapital;
    int months = timeInMonths;

};  

struct Deposit{
    
    int initialDeposit = initialCapital;
    float annualInterest = 0.1;
    int months = timeInMonths;

};

float calculateMortgageIncome(Mortgage mortgage){
    
    float debt = mortgage.initialFlatCost - mortgage.initialFee;
    
    if (mortgage.monthlyPayments < debt * mortgage.annualInterest / 12){
        
        return -1;

    }

    float flatCost = mortgage.initialFlatCost;
    float account = 0;

    for (int i = 0; i < mortgage.months ; i++){
        
        debt += debt * mortgage.annualInterest / 12 - mortgage.monthlyPayments; 
        flatCost += mortgage.initialFlatCost * annualCostIncrease / 12;
        account += rental;

    }
    
    if (debt > 0) {
        
        account += flatCost - debt;

    }

    account += flatCost; 

    return account;

}

float calculateDepositIncome(Deposit deposit){

    float account = deposit.initialDeposit;

    for (int i = 0; i < deposit.months; i++){

        account += account * deposit.annualInterest / 12;

    }

    return account;

}

int main() {
    
    Mortgage myMortgage;
    Deposit myDeposit;

    if (calculateDepositIncome(myDeposit) > calculateMortgageIncome(myMortgage)){

        cout << "Deposit is more profitable. You will get " << calculateDepositIncome(myDeposit);

    } else {

        cout << "Mortgage is more profitable. You will get " << calculateMortgageIncome(myMortgage);

    }

    return 0;

}
