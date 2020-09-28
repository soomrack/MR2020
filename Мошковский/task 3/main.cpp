#include <iostream>
using namespace std;
int main() {
    long long int startup; //стартовый капитал
    cout << "Enter the start-up capital:";
    cin >> startup;
    int periodIP; //время ипотеки
    cout << "Enter the period of mortgage (years):";
    cin >> periodIP;
    long long int cost; //стоимость квартиры
    cout << "Enter the cost of the apartment (penny):";
    cin >> cost;
    cost=cost-startup;
    int procIP; //процент ипотеки
    cout << "Enter your mortgage percentage:";
    cin >> procIP;
    int procVk; //процент вклада
    cout << "Enter the percentage of the deposit:";
    cin >> procVk;
    procVk = procVk / 12;
    int rost; //рост стоимости квартиры
    cout << "Enter the rise in the cost of the department:";
    cin >> rost;
    int ipot;
    ipot = cost*100/(procIP*periodIP);
    long long int trataIP; //затраты на ипотеку
    trataIP = ipot*periodIP;
    trataIP = -cost-startup-trataIP+((cost+startup)*((1+rost/100)^periodIP));
    cout << trataIP << endl;
    long long int plusVK = startup; //вложение во вклад
    for (int i; i<=periodIP; i++) {
        plusVK=(plusVK+ipot*12)*(1+procVk/100);    }
    long long int trataVK; //затраты на вклад
    trataVK = plusVK-((cost+startup)*((1+rost/100)^periodIP));
    cout << trataVK << endl;
    if (trataIP>trataVK) {
        cout << "More economical is mortgage: " << trataIP << " penny" << endl;
    } else cout << "More economical is deposit: " << trataVK << " penny" << endl;

    return 0;
}
