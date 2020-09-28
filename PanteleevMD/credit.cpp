#include <iostream>
#include <cmath>

using namespace std;

struct input
{
    int cap;            //Капитал
    float procDep;      //Проценты депозита
    float procCred;     //Проценты кредита
    float procFlat;     //Переоценка квартиры
    int time;           //Время(мес)
    int initialPay;     //Первый взнос
    int wage;           //
    int estateCost;     //Стоимость квартиры

    float calcDeposit()
    {
        return 1/(procDep - 1) * wage * (pow(procDep, time) - 1) + cap * pow(procDep, time);
    }
};

input randomEvent(input in)
{
    int eventN = rand()%5;
    
    switch (eventN)
    {
        case 1:
            cout << "You were promoted! Your wage is increased by 10%" << '\n';
            in.wage *= 1.1;
            break;
        case 2:
            cout << "You were demoted! Your wage is decreased by 10%" << '\n';
            in.wage *= 0.9;
            brak;
        case 3:
            cout << "";
    }
    
    
}

input checkFacts(input rawData)
{
    float eps = rawData.procCred/rawData.time;
    float Ka = (eps*pow(1+eps, rawData.time))/(pow(1+eps, rawData.time) - 1);
    float maxestateCost = rawData.wage/Ka + rawData.cap;
    float payment = Ka*(rawData.estateCost - rawData.cap);

    if (payment > rawData.wage)
    {
        char answer;
        cout << '\n' << "Seems like you can't afford this property." << '\n';
        cout << "Would you like to calculate profit anyway or find a new place? (1/2)" << '\n';
        cin >> answer;
        if (answer == '2')
        {
            cout << "The maximum price you can afford according to your data is: " << maxestateCost << '\n';
            rawData.estateCost = maxestateCost;
        }
    }

    return rawData;
}

input collectData()
{
    input dataCollector;
    float tempValue = 0.0;
    cout << "$$$$ Investment calculator $$$$";
    cout << '\n' << "How much money do you own?   ";
    cin >> dataCollector.cap;
    cout << '\n' << "How much are you ready to save every month?   ";
    cin >> dataCollector.wage;
    cout << '\n' << "At what percentage you can Deposit your money?   ";
    cin >> tempValue;
    dataCollector.procDep = tempValue/1200 + 1;
    cout << '\n' << "How much does propertry you want to buy cost?   ";
    cin >> dataCollector.estateCost;
    cout << '\n' << "At which rate proprty increases in price in your neighborhood?   ";
    cin >> tempValue;
    dataCollector.procFlat = tempValue/1200 + 1;
    cout << '\n' << "At what percentage can you take a loan?   ";
    cin >> tempValue;
    dataCollector.procCred = tempValue/1200 + 1;
    cout << '\n' << "For how long do you plan to invest your money?   ";
    cin >> dataCollector.time;


    dataCollector = checkFacts(dataCollector);
    return dataCollector;
}



void calculateProfits(input data)
{
    float dep = (float)data.cap * data.procDep;          //deposit
    float estate = (float)data.estateCost;

    float eps = data.procFlat/12;
    float Ka = (eps*pow(1+eps, data.time))/(pow(1+eps, data.time) - 1);
    float payment = Ka*(data.estateCost - data.cap);

    float delta = (float)data.wage - payment;
    float depCombo = delta * data.procDep;

    for (int month = 0; month < data.time; month++)
    {
        //dep = (dep + data.wage)*data.procDep;
        depCombo = (depCombo + delta)*data.procDep;
        estate *= data.procFlat;
    }
    

    dep = data.calcDeposit();
    
    float sum = payment*data.time;

    float depositProfit = dep - data.cap;
    float estateProfit = estate - sum;
    float combinedProfit = estateProfit + depCombo;

    printf("Profits: %f, %f, %f", depositProfit, estateProfit, combinedProfit);
}

int main()
{
    input data;
    data = collectData();

    calculateProfits(data);

    return 0;
}