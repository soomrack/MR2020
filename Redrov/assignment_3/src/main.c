#include "../inc/main.h"

int main(void){

    int price;
    float loan_rate;
    float deposit_rate;
    int term;
    float rise_in_value;
    int initial_capital;
    int aver_exps;

    printf(ENTER_PRICE);
    scanf("%d", &price);
    printf(ENTER_LOAN_RATE);
    scanf("%f", &loan_rate);
    printf(ENTER_DEPOSIT_RATE);
    scanf("%f", &deposit_rate);
    printf(ENTER_TERM);
    scanf("%d", &term);
    printf(ENTER_RISE_OF_PRICE);
    scanf("%f", &rise_in_value);
    printf(ENTER_INITIAL_CAPITAL);
    scanf("%d", &initial_capital);
    printf(ENTER_AVER_EXPS);
    scanf("%d", &aver_exps);

    printf("Let's figure this shit out!\n");

    int income_from_credit = calc_credit(price, loan_rate, term, rise_in_value, 
                initial_capital, aver_exps);

    int income_from_deposit = calc_deposit(initial_capital, deposit_rate, term);

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

    // Calculating of payment per month
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
