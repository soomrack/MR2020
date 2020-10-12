#include <iostream>
//#include "XO.h"

#include "XO.cpp"

using namespace std;

volatile bool IsGameOver = false;


int main() {

    //std::cout << "Hello, World!" << std::endl;
    //FieldInit();
    FieldInit();
    while (!IsGameOver) {
        cout << "Your turn!" << endl;
        UsersMove();
        IsSomeoneWin();
        cout << "Computer`s turn" << endl;

        ComputersMove();
        IsSomeoneWin();
    /*    if (IsSomeoneWin(UserMark)) {
            cout << "User Win!";
            IsGameOver = true;
        }
        else if (IsSomeoneWin(ComputerMark)) {
            cout << "Computer Win!";
            IsGameOver = true;
        }*/
        //cout << "No one is win ))" << endl;
    }
    cout << endl << "Game is over!";
    return 0;
}
