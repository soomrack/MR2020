#include <iostream>
using namespace std;
int main() {
    string ans;
    cout << "Hi!)) Good to see you on my quiz!" << endl;
    cout << "1) Oberon is the satellite of which planet?" << endl;
    cout << "A) Mercury    B) Neptune" << endl;
    cout << "C) Uranus     D) Mars" << endl;
    cin >> ans;
    if(ans=="C" || ans=="c") {
        cout << "Well done! The next question:" << endl;
        cout << "2) A number one followed by one hundred zeros is known by what name?" << endl;
        cout << "A) Googol      B) Megatron" << endl;
        cout << "C) Gigabit     D) Nanomole" << endl;
        cin >> ans;
        if(ans=="A" || ans=="a") {
            cout << "Well done! The next question:" << endl;
            cout << "3) What was the occupation of the compose Borodin?" << endl;
            cout << "A) Naval capitan    B) Chemist" << endl;
            cout << "C) Lawyer           D) Chef" << endl;
            cin >> ans;
            if(ans=="B" || ans=="b") {
                cout << "Well done! The next question:" << endl;
                cout << "4) Which of these UK prime ministers never served as foreign secretary?" << endl;
                cout << "A) Winston Chrchill    B) Alex Home" << endl;
                cout << "C) Anthony Eden        D) Harold Mcmillan" << endl;
                cin >> ans;
                if(ans=="A" || ans=="a") {cout << "Well done! The next question:" << endl;
                    cout << "5) In Welsh, what does 'afon' mean?" << endl;
                    cout << "A) Fort    B) Meadow" << endl;
                    cout << "C) Pool    D) River" << endl;
                    cin >> ans;
                    if(ans=="D" || ans=="d") {
                        cout << "You are very smart! My congratulation for you. You answered 5 qesion correctly)" << endl;
                    }else cout << "You are failed! You answered 4 qesion correctly" << endl;
                } else cout << "You are failed! You answered 3 qesion correctly" << endl;
            }else cout << "You are failed! You answered 2 qesion correctly" << endl;
        } else cout << "You are failed! You answered 1 qesion correctly" << endl;
    } else cout << "You are failed! You answered 0 qesion correctly" << endl;
    return 0;
}
