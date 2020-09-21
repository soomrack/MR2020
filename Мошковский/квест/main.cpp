#include <iostream>
using namespace std;
int main() {
    string ans;
    cout << "Hi, my dear friend! Would you like to play?" << endl;
    cin >> ans;
    if (ans == "yes" || ans == "ok") {
        cout << "Let's start already" << endl;
        cout << "1) Who was the first to win two unshared Nobel Prizes?" << endl;
        cout << "A)Marie Curie    B)Ivan Pavlov" << endl;
        cout << "C)Linus Pauling  D)Albert Schweitzer" << endl;
        cin >> ans;
        if(ans=="C" || ans=="c") {cout << "Very good! The next question:" << endl;
            cout << "2) How many humans have set foot on the moon?" << endl;
            cout << "A)10    B)12" << endl;
            cout << "C)14    D)16" << endl;
            cin >> ans;
            if(ans=="B" || ans=="b") {cout << "Smart! The next question:" << endl;
                cout << "3) What was the original name of Dorothea Mackellar’s poem ‘My Country’?" << endl;
                cout << "A)The Wide Brown Land    B)‘Tis my home" << endl;
                cout << "C)A Sunburnt Country     D)Core of my heart" << endl;
                cin >> ans;
                if(ans=="D" || ans=="d") {cout << "Outstanding! The next question:" << endl;
                    cout << "4) Who was the first to win two unshared Nobel Prizes?" << endl;
                    cout << "A)The Photos    B)The Hunter" << endl;
                    cout << "C)The Punch     D)The Cook" << endl;
                    cin >> ans;
                    if(ans=="B" || ans=="b") {cout << "Fantastic! The next question:" << endl;
                        cout << "5) How many Dalai Lamas ruled Tibet?" << endl;
                        cout << "A)13    B)14" << endl;
                        cout << "C)15    D)16" << endl;
                        cin >> ans;
                        if(ans=="B" || ans=="b") {cout << "Are you a genius? My congratulation, you've answered all 5 questions correctly!" << endl;
                        }else cout << "You're a fool" << endl;
                    }else cout << "You're a fool" << endl;
                }else cout << "You're a fool" << endl;
            }else cout << "You're a fool" << endl;
        }else cout << "You're a fool" << endl;
    }else cout << "You're a fool" << endl;

    return 0;
}
