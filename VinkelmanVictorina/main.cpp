#include <iostream>
using namespace std;

int main() {
    int ntruth = 0, n;
    cout << "1. Kakomu zvaniu sootvetstvuet Oberstgrupennfurer?" << endl;
    cout << "1) General" << endl;
    cout << "2) General-polkovnik" << endl;
    cout << "3) General-leytenant" << endl;
    cin >> n;
    if (n == 2){
        ntruth = ntruth + 1;
    }

    cout << "2. Komu prinadlegat slova: Naydi vraga i sbey ego. Vse ostal'noe ne imeet znachenie?" << endl;
    cout << "1) Gunter Rall" << endl;
    cout << "2) Voss Werner" << endl;
    cout << "3) Manfred von Richthofen" << endl;
    cin >> n;
    if (n == 3){
        ntruth = ntruth + 1;
    }

    cout << "3. Kto pridumal slovo vertolet?" << endl;
    cout << "1) Kamov" << endl;
    cout << "2) Mil'" << endl;
    cout << "3) Erlix" << endl;
    cin >> n;
    if (n == 1){
        ntruth = ntruth + 1;

    }

    cout << "4. Gde pohoronen general francuzskoy armii Jean Victor Moreau?" << endl;
    cout << "1) Paris" << endl;
    cout << "2) Saint-Peterburg" << endl;
    cout << "3) Dresden" << endl;
    cin >> n;
    if (n == 2){
        ntruth = ntruth + 1;
    }

    cout << "5. Kogo Davidov nazival angel-hranitelem russkih voysk?" << endl;
    cout << "1) Ermolov" << endl;
    cout << "2) Kutuzov" << endl;
    cout << "3) Suvorov" << endl;
    cin >> n;
    if (n == 1){
        ntruth = ntruth + 1;
    }

    cout << "Your result " << ntruth << endl;

    return 0;
}
