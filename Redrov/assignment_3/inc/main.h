#include "stdio.h"
#include <math.h>

#define ENTER_PRICE "Enter the price of apartment\n"
#define ENTER_LOAN_RATE "Enter loan rate\n"
#define ENTER_DEPOSIT_RATE "Enter deposit rate\n"
#define ENTER_TERM "Enter term\n"
#define ENTER_RISE_OF_PRICE "Enter rise in value of apartment\n"
#define ENTER_INITIAL_CAPITAL "Enter initial capital\n"
#define ENTER_AVER_EXPS "Enter average expenses on apartment\n"

int calc_credit(int price, float rate, int term,
                float rise_in_value, int initial_capital,
                int aver_exps);

int calc_deposit(int initail_capital, float rate, int term);
