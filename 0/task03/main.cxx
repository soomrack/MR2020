#include <iostream>

// Все деньги в копейках

struct Person {
     unsigned long int deposit;
     unsigned long int month_income;  // зарплата, раз в месяц
     unsigned long int house_value;  // текущая стоимость жилья
     unsigned long int house_value_init;  // певоначальная стоимость жилья
     unsigned long int month_mortgage_pay;  // месячный платеж по ипотеке
     unsigned long int init_pay;  // первоначальный взнос по ипотеке
};


unsigned long int deposit_month_income(const unsigned long int money,
                                       const unsigned long int month) {
     unsigned int pp = 600;  // сотые доли процентного пункта
     unsigned long int income = 0;
     income = (unsigned long int) (money * (pp * 0.0001) / 12.0);
     return income;
}


unsigned long int house_value_month_income(const unsigned long int value,
                                           const unsigned long int month) {
     unsigned int pp = 300;  // сотые доли поцентного пункта
     unsigned long int income = 0;
     income = (unsigned long int) (value * (pp * 0.0001) / 12.0);     
     return income;
}


unsigned long int month_mortgage_pay(const unsigned long int value,
                                     const unsigned long int month,
                                     const unsigned long int init_pay) {
     unsigned long int pay = 0;
     // сложная функция для расчета ежемесячной выплаты по ипотеке
     unsigned long int total_pay = value - init_pay;
     for(int k = 0; k < 10; k++) {  // 10 лет под 12% годовых
          total_pay = (unsigned long int)(total_pay * 1.12);
     }
     pay = (unsigned long int)(total_pay / 120);
     return pay;
}


int simulate(const unsigned int months){     
     Person Bob;
     Bob.deposit = 1000000 * 100;
     Bob.month_income = 50000 * 100;

     Person Alice;
     Alice.deposit = 1000000 * 100;
     Alice.month_income = 50000 * 100;

     // Покупка жилья
     Alice.init_pay = 1000000 * 100;
     Alice.deposit -= Alice.init_pay;  // Первоначальный взноз
     Alice.house_value_init = 12000000 * 100;
     Alice.house_value = Alice.house_value_init;     

     // Главный цикл
     for(unsigned int current_month = 1; current_month <= months; current_month++) {
          // Alice
          Alice.deposit += deposit_month_income(Alice.deposit, current_month);
          Alice.house_value += house_value_month_income(Alice.house_value, current_month);
          Alice.month_mortgage_pay = month_mortgage_pay(Alice.house_value_init, current_month, Alice.init_pay);
          
          // Bob
          Bob.deposit += deposit_month_income(Bob.deposit, current_month);
          Bob.deposit += Alice.month_mortgage_pay;
     }

     std::cout << "  Bob value: " << Bob.deposit << std::endl;
     std::cout << "Alice value: " << Alice.house_value << std::endl;
     std::cout << "Alice month pay: " << Alice.month_mortgage_pay << std::endl;
     return 0;
}



int main() {
     simulate(120);
     
     std::cout << "Finished!" << std::endl;
}
