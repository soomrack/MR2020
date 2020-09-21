// Game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;
int main() {
    string name;
    string DD;
    string A;
    string QW;
    int a=0;
    int z;
    cout << "Hi, bro! What is your name?" << endl;
    cin >> name;
    cout << " You wanna play? " << name << ", Lets play!" << endl;
    cout << "Answer the questions!" << endl;
    cout << "You a ready?" << endl;
    cin >> DD;
    cout << "Count 2+2*2!" << endl;
    cin >> z;
    if (z == 6) {
        ++a;
        cout << "Oh... my... God. You are very smart! Points - " << a << endl;
    }
    else {
        cout << "No!" << endl;
    }
    cout << "Shaverma is tasty?"<<endl;
    cin >> QW;
    if ((QW=="yes")||(QW=="y")) {
        a++;
        cout << "you're goddamn right! Points - " << a << endl;
    }
    else {
        cout << "NO!";
    }
    cout << "Who is the best teachers in world?" << endl;
    cin >> A;
    if ((A == "Mikhail Sergeevich") || (A == "Ananevskiy")) {
        ++a;
    }
    if (a==3){
        cout << "You won this game! All answer was true! You are krasavchik!";
    }
    else {
        cout << "Well, your points = " << a << ". Ne rastraivaysya" << endl;
    }
    return 0;
}

