#include <iostream>
#include <string>
using namespace std;

int answer; 
char board[9] = {};

void clear_console (){
    for (int i=0; i < 50; i++){
        cout << endl;
    }
}

void clear_board (){
    for (int i = 0; i < 9; i++){
        board[i] = '-';
    }
}

void numbers_board ( ) {
    cout <<"A field with numbered cells is displayed below.\n";
    cout << "-7- | -8- | -9-\n";
    cout << "-4- | -5- | -6-\n";
    cout << "-1- | -2- | -3-\n\n\n";
}


string want, clear;  
int foreword (){  
   cout << "Welcome to the game of tic-tac-toe!\nWant to start?\nPlease, enter yes or no.\n";
   cin >> want;
      while (want != "yes" && want != "no"){
          cout << "Please, enter yes or no.\n";
          cin >> want;
        }
      if (want == "yes"){
          cout << "\nYou play for noughts. You need to enter the cell number to put zero into it.\n";
           numbers_board ();
           cout << "All clear? Please, enter yes or no.\n";
              cin >> clear;
              while (clear != "yes" && clear != "no"){
                  cout << "Please, enter yes or no.\n";
                   cin >> clear;
                }
              if (clear == "yes"){
                   cout << "Excellent! Start the game.\n\n";
                }
              else {
                   cout << "Ask the creator)) Start the game.\n\n";
                 }
            return 1;
        }
      else {
          cout << "Have a nice day!\nWe will wait fo you another time.";
          return 0;
        }
}

void game_board (){
    cout << "Your game field: \n";
    cout << "-"<< board[6]<<"- | -"<< board[7]<< "- | -" <<board[8]<< "-\n";
    cout << "-"<< board[3]<<"- | -"<< board[4]<< "- | -" <<board[5]<< "-\n";
    cout << "-"<< board[0]<<"- | -"<< board[1]<< "- | -" <<board[2]<< "-\n\n";
}

void question (){
   numbers_board ();
   game_board ();
   cout <<"Your move: "; 
}
 
void check_answer (){
    cin >> answer;
    while (answer > 9 || answer < 1 ) {
        cout << "Please, enter 1-9.\n";
        cin >> answer;
    }
    while (board[answer-1] != '-'){
        cout << "Please, enter the cell number that is still free.\n";
        cin >> answer; 
    } 
}

bool winner( char X_or_0 ){
    int win [][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {2,4,6}, {0,4,8}};
    for (int i = 0; i < 8; i++){
        int count = 0;
        for (int j = 0; j < 3; j++){
            if (board[win[i][j]] == X_or_0){
            count++; 
            }   
        }
        if (count == 3) {
            return true;
        }
    }
    return false;
}

void resultat () {
    cout << "The final field is: \n";
    game_board ();
}   

int game (){
    int move = 0;
    clear_console ();
    while (!winner( 'X' ) && !winner( '0' )){
        if(move%2 == 0){
            question ();
            check_answer ();
            board[answer-1] = '0';
            if (winner( '0' )){
                cout << "Congratulations! You won!\n";
                resultat ();
                break;
                //return '0';
            }
        }
        else {
            int comp = rand() % 9;
            while (board[comp] != '-'){
            comp = rand() % 9;
            }
            board[comp] = 'X';
            if (winner( 'X' )){
                cout << "Won the computer. Don't be upset, next time you win.\n";
                resultat ();
                break;
                //return 'X';
            }
        }
        move++;
        if (move == 9){
            cout << "Wow! It's a draw!\n";
            resultat ();
            break;
            //return 'D';
        }
    }
    cout << "Thanks for the game!";
   return 1;
}

int main ( ) {
    string continuation;
    do{
        clear_board ();
        if (foreword() == 0){
        return 0;
        }
        else {
        game ();
        cout << "Can we play more?\n";
        cin >> continuation;
            while (continuation != "yes" && continuation != "no"){
                cout << "Please, enter yes or no.\n";
                cin >> continuation;
            }
        }
    } while (continuation == "yes");
    cout << "Have a nice day!\nWe will wait fo you another time.";
   return 0; 
}