//
// Created by vladl on 19.09.2020.
//
#include <iostream>
#include <string>
using namespace std;

//     1 2 3
// 1  |O|-|-|
// 2  |-|X|-|
// 3  |-|O|-|


char table[3][3];


// Initializing table with blank spaces
void init_table(void){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3;j ++) { table[i][j] = '-'; }
    }
}

// print new version of table
void update_screen(void){

    for (int i = 0; i < 3; i++){
        cout << "|"; // starts every row with "|"

        for (int j = 0; j < 3; j++){
            cout << "|" << table[i][j];
        }
        
        cout << endl;; // ends every line with "|\n"
    }

    cout << endl;

}

// inserting move into table
void insert_move(char symbol, int row, int col){

    table[row][col] = symbol;

}

// checking whether game is ended or not
char check_end(void){

    char is_blank = 1;
    short count = 0;

    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (table[i][j] != '-'){ 
                is_blank = 0;
                count ++;
                break;
            }  
        }
    }


    if(!is_blank){
        if ((table[0][0] == table[1][1]) && (table[1][1] == table[2][2]) && (table[0][0] != '-')) {}// return table[0][0]; }
        if ((table[0][2] == table[1][1]) && (table[1][1] == table[2][0]) && (table[0][2] != '-')) {}// return table[0][2]; }
        if ((table[0][0] == table[0][1]) && (table[0][1] == table[0][2]) && (table[0][0] != '-')) {}// return table[0][0]; }
        if ((table[1][0] == table[1][1]) && (table[1][1] == table[1][2]) && (table[1][0] != '-')) {}// return table[1][0]; }
        if ((table[2][0] == table[2][1]) && (table[2][1] == table[2][2]) && (table[2][0] != '-')) {}// return table[2][0]; }
        if ((table[0][0] == table[1][0]) && (table[1][0] == table[2][0]) && (table[0][0] != '-')) {}// return table[0][0]; }
        if ((table[0][1] == table[1][1]) && (table[1][1] == table[2][1]) && (table[0][1] != '-')) {}// return table[0][1]; }
        if ((table[0][2] == table[1][2]) && (table[1][2] == table[2][2]) && (table[0][2] != '-')) {}// return table[0][2]; }
        if (count == 9) {return 1;}
    }

    return 0;
}

// claculating and making turn from the computer's side
string make_turn(void){

    if (table[1][1] == '-') { insert_move('O', 1, 1); return "11";}

    for (int i = 0; i < 3; i++){
        if ((table[i][0] == table[i][2]) && (table[i][0] == 'X') && (table[i][1] != 'O')){
            insert_move('O', i, 1); 
            return ((char) i + 48) + "1";
        }

        if ((table[i][0] == table[i][1]) && (table[i][0] == 'X') && (table[i][2] != 'O')){
            insert_move('O', i, 2); 
            return ((char) i + 48) + "2";
        }

        if ((table[i][1] == table[i][2]) && (table[i][1] == 'X') && (table[i][0] != 'O')){
            insert_move('O', i, 0); 
            return ((char) i + 48) + "0";
        }

        if ((table[0][i] == table[2][i]) && (table[0][i] == 'X') && (table[0][i] != 'O')){
            insert_move('O', 1, i); 
            return "1" + ((char) i + 48);
        }

        if ((table[0][i] == table[1][i]) && (table[0][i] == 'X') && (table[2][i] != 'O')){
            insert_move('O', 2, i); 
            return "2" + ((char) i + 48);
        }

        if ((table[1][i] == table[2][i]) && (table[1][i] == 'X') && (table[0][i] != 'O')){
            insert_move('O', 0, i); 
            return "0" + ((char) i + 48);
        }
    }

    if (table[0][0] == '-') { insert_move('O', 0, 0); return "00"; }
    if (table[0][2] == '-') { insert_move('O', 0, 2); return "02"; }
    if (table[2][0] == '-') { insert_move('O', 2, 0); return "20"; }
    if (table[2][2] == '-') { insert_move('O', 2, 2); return "22"; }

}

// main function of the game, where game actually plays
void play_game(void){

    char is_ended = 0;
    char index[2];

    while (! is_ended){
        cin >> index;
        insert_move('X', index[0] - 48 - 1, index[1] - 48 - 1);
        update_screen();
        is_ended = check_end();
        if (is_ended) {break;}
        make_turn();
        update_screen();
        is_ended = check_end();
    }

    if (is_ended == 1){
        cout << "It is a draw!" << endl;
    }
    else if (is_ended == 'X'){
        cout << "You are winner. Congrats!"  << endl;
    }
    else{
        cout << "We should press F to pay you some respect." << endl << "Unfortunately, you lost :c" << endl;
    }

}


int play(void){

    init_table();      // Initializing table with blank spaces
    update_screen();   // print new version of table

    cout << "Enter the code of the cell without any special symbols or spaces, as shown here: {number_of_row}{number_of_column}" << endl;
    
    play_game();

}