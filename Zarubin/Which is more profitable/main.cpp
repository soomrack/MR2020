#include <iostream>
using namespace std;
int main() {
    long long int startkap;
    cout << "Enter the starting capital (penny):" << endl;
    cin >> startkap;
    int periodIP;
    cout << "Enter the period Ipoteka (years):" << endl;
    cin >> periodIP;
    long long int cost;
    cout << "Enter the cost of the apartment (penny):" << endl;
    cin >> cost;
    cost=cost-startkap;
    int procIP;
    cout << "Enter your mortgage percentage:" << endl;
    cin >> procIP;
    int procVk;
    cout << "Enter the percentage of the deposit:" << endl;
    cin >> procVk;
    procVk = procVk / 12;
    int Rost;
    cout << "Enter the rise in the cost of the apartment:" << endl;
    cin >> Rost;
    int ipoteka;
    ipoteka =cost*100/(procIP*periodIP);
    long long int trataIP;
    trataIP=ipoteka*periodIP;
    trataIP=-cost-startkap-trataIP+((cost+startkap)*((1+Rost/100)^periodIP));
    cout << trataIP << endl;
    long long int plusVK=startkap;
    for (int i; i<=periodIP; i++) {
        plusVK=(plusVK+ipoteka*12)*(1+procVk/100);
    }
    long long int trataVK;
    trataVK=plusVK-((cost+startkap)*((1+Rost/100)^periodIP));
    cout << trataVK << endl;
    if (trataIP>trataVK) {
        cout << "More profitable is Ipoteka" << endl;
    } else cout << "More profitable is Vklad" << endl;
    return 0;
}
