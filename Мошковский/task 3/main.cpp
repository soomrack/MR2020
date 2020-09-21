#include <iostream>
using namespace std;
int main() {
    int zp;
    cout << "Enter the amount that you are ready to invest:" << endl;
    cin >> zp;
    int startcap;
    cout << "Enter the starting capital (penny):" << endl;
    cin >> startcap;
    int periodIP;
    cout << "Enter the term of the mortage (months):" << endl;
    cin >> periodIP;
    int procIP;
    cout << "Enter your montage percentage:" << endl;
    cin >> procIP;
    procIP=procIP/12;
    int procVk;
    cout << "Enter the percentage of the deposit:" << endl;
    cin >> procVk;
    int rost;
    cout << "Enter the rise i the cost of the department:" << endl;
    cin >> rost;


    return 0;
}
