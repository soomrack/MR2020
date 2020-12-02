#include <iostream>
#include <time.h>

#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
#define CROSS "\u2A2F"
#define ZERO "\u0E50"
#define MAX_GAME_MOVE 9
using namespace std;

int fields[9] = {0};
int gameMove = 0;

string showCrossOrZero(int field) {
    if (field == 0) {
        return " ";
    } else if (field == 1) {
        return CROSS;
    } else {
        return ZERO;
    }
}

int showTheField() {
    cout << UNDERLINE << showCrossOrZero(fields[0]) << "|" << showCrossOrZero(fields[1]) << "|" << showCrossOrZero(fields[2]) << CLOSEUNDERLINE << '\n';
    cout << UNDERLINE << showCrossOrZero(fields[3]) << "|" << showCrossOrZero(fields[4]) << "|" << showCrossOrZero(fields[5]) << CLOSEUNDERLINE << '\n';
    cout << showCrossOrZero(fields[6]) << "|" << showCrossOrZero(fields[7]) << "|" << showCrossOrZero(fields[8]) << '\n';

    return 0;
}

void deletePreviousMessage() {
    cout << "\033[A";
}

int startWords() {

    char answer = '0';

    cout << "Hi, this is a really popular game. It names tic tac toe. To win you have to put crosses or zeros in a row. You will play with crosses. Now you see a field with numbers." << '\n' << "Each number refers to the special place of the field. To put the cross you have to choose a number from the field." << '\n';
    cout << UNDERLINE << 1 << "|" << 2 << "|" << 3 << CLOSEUNDERLINE << '\n';
    cout << UNDERLINE << 4 << "|" << 5 << "|" << 6 << CLOSEUNDERLINE << '\n';
    cout << 7 << "|" << 8 << "|" << 9 << '\n';
    cout << "Are you ready to start? (choose an answer number)" << '\n' << "1. Yes" << "\t\t" << "2. No" << '\n';

    do{
        
        cin >> answer;
        deletePreviousMessage();
        
        if (answer == '1') {
            showTheField();
            cout << "Choose a certain place using numbers where you want to put the cross." << '\n';
            return 1;
        } else if (answer == '2') {
            cout << "OK. See you soon!" << '\n';
            return 0;
        } else {
            cout << "You have to choose 1 or 2." << '\n';
        }
    }
    while (answer != '1' || answer != '2');

}

int humanMove(){
    
    int field;
    int presentMove = gameMove;

    while (presentMove == gameMove){

        cin >> field;
        
        deletePreviousMessage();
        
        if (fields[field - 1] == 0){

            fields[field - 1] = 1;
            gameMove++;
        
        } else{

            cout << "You have to choose another cell" << '\n';

        }
                 
        showTheField();

    }
    
    return 0;

}

int computerMove(){
    
    srand(time(NULL));
    
    int field = 0;
    int presentMove = gameMove;

    while (presentMove == gameMove){

        field = rand() % 9;
        if (fields[field] == 0){

            fields[field] = 2;
            gameMove++;
        
        } 

    }

    showTheField();

    return 0;

}

int winFinder() {

    if (fields[0] == 1 && fields[1] == 1 && fields[2] == 1 || fields[3] == 1 && fields[4] == 1 && fields[5] == 1 || 
        fields[6] == 1 && fields[7] == 1 && fields[8] == 1 || fields[0] == 1 && fields[3] == 1 && fields[6] == 1 ||
        fields[1] == 1 && fields[4] == 1 && fields[7] == 1 || fields[2] == 1 && fields[5] == 1 && fields[8] == 1 ||
        fields[0] == 1 && fields[4] == 1 && fields[8] == 1 || fields[2] == 1 && fields[4] == 1 && fields[6] == 1) {

        return 1;

    }

    if (fields[0] == 2 && fields[1] == 2 && fields[2] == 2 || fields[3] == 2 && fields[4] == 2 && fields[5] == 2 || 
        fields[6] == 2 && fields[7] == 2 && fields[8] == 2 || fields[0] == 2 && fields[3] == 2 && fields[6] == 2 ||
        fields[1] == 2 && fields[4] == 2 && fields[7] == 2 || fields[2] == 2 && fields[5] == 2 && fields[8] == 2 ||
        fields[0] == 2 && fields[4] == 2 && fields[8] == 2 || fields[2] == 2 && fields[4] == 2 && fields[6] == 2) {

        return 2;

    }

    return 0;

}

int main() {
    char answer;

    
    if (startWords()) {

        while (gameMove < MAX_GAME_MOVE) {
            
            humanMove();
            
            if (winFinder() == 1){

                cout << "Human win!";
                break;

            }

            if (winFinder() == 2){

                cout << "Computer win!";
                break;

            }

            if (gameMove == MAX_GAME_MOVE){

                cout << "Nobody won.";
                break;

            }

            computerMove();

        }

    }
    
    return 0;
    
}
