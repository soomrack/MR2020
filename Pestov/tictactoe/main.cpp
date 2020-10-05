/* 
The 4th assignment of programming in a high level language

Console application - game tic tac toe.

Principle of operation:
    // The game board is created. 
    // The user chooses who he wants to play for (X or 0)
    // Human move
    // Program move (random)
    // The end
    Debag
    Smart proram move
*/

#include <iostream>
#include <cstdlib> 
#include <ctime>


struct board_t {
    char A[3][3];
};

board_t create_board(){
    board_t board;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            board.A[i][j] = '-';
        }
    }

    return board;
}

void print_board(board_t board){
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            std::cout << board.A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool user_choice(){
    // return is_user_X;
    bool x;
    std::cout << "Choose your sym (X or 0):" << std::endl;
    char sym;
    std::cin >> sym;
    if (sym == 'X'){
        return true;
    }
    else if (sym == '0') {
        return false;
    }
    else {
        std::cout << "Invalid sym, re-enter:" << std::endl;
        return user_choice();
    }
}

board_t human_move(board_t board, bool is_gamemode_X){
    int row, col;
    std::cout << "Your move(enter col and row):" << std::endl;
    std::cin >> row >> col;
    row--;
    col--;
    char temp = board.A[col][row];
    if (temp == '-'){
        if (is_gamemode_X){
            board.A[col][row] = 'X';
        }
        else {
            board.A[col][row] = '0';
        }
        
    }
    else {
        std::cout << "Place already occupied, enter another value." << std::endl;
        board = human_move(board, is_gamemode_X);
    }

    return board;
} 

board_t prog_move(board_t board, bool is_gamemode_X){
    // srand(static_cast<unsigned int>(time(0)));
    int row = (rand() % 3);
    int col = (rand() % 3);
    // std::cout << row << "   " << col << std::endl;
    char temp = board.A[col][row];
    if (temp == '-'){
        std::cout << "My move:" << std::endl;
        std::cout << row << " " << col << std::endl;
        if (!is_gamemode_X){
            board.A[col][row] = 'X';
        }
        else {
            board.A[col][row] = '0';
        }
        
    }
    else {
        board = prog_move(board, is_gamemode_X);
    }

    return board;

}

int find_winner(board_t board){
    // return 1 - X win
    // return 0 - 0 win
    // return 2 - draw
    // return -1 - no end
    int count = 0;
    // find X win
    
    for (int i = 0; i < 3; i++){
        // horizontal
        for (int j = 0; j < 3; j++){
            if (board.A[i][j] == 'X'){
                count++;
            }
        
        }
        if (count == 3){
            return 1;
        }
        count = 0;
        // vertical 
        for (int j = 0; j < 3; j++){
            if (board.A[j][i] == 'X'){
                count++;
            }
        
        }
         if (count == 3){
            return 1;
        }
        count = 0;
    }
    // main diagonal 
    for (int j = 0; j < 3; j++){
        if (board.A[j][j] == 'X'){
            count++;
        }
    
    }
    if (count == 3){
        return 1;
    }
    count = 0;
    // second diagonal
    for (int j = 0; j < 3; j++){
        if (board.A[j][2 - j] == 'X'){
            count++;
        }
    
    }
    if (count == 3){
        return 1;
    }
    count = 0;
    
    // find 0 win
    for (int i = 0; i < 3; i++){
        // horizontal
        for (int j = 0; j < 3; j++){
            if (board.A[i][j] == '0'){
                count++;
            }
        
        }
        if (count == 3){
            return 0;
        }
        count = 0;
        // vertical 
        for (int j = 0; j < 3; j++){
            if (board.A[j][i] == '0'){
                count++;
            }
        
        }
         if (count == 3){
            return 0;
        }
        count = 0;
    }
    // main diagonal 
    for (int j = 0; j < 3; j++){
        if (board.A[j][j] == '0'){
            count++;
        }
    
    }
    if (count == 3){
        return 0;
    }
    count = 0;
    // second diagonal
    for (int j = 0; j < 3; j++){
        if (board.A[j][2 - j] == '0'){
            count++;
        }
    
    }
    if (count == 3){
        return 0;
    }
    count = 0;

    // find end game

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board.A[i][j] == '-'){
                count++;
            }
        }
    }
    if (count == 0){
        return 2;
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    bool end = false;
    bool pr_move = false;
    bool hum_move = false;
    board_t board = create_board();
    print_board(board);
    bool choice = user_choice();
    if (choice){
        hum_move = true;
    }
    else {
        pr_move = true;
    }
    
    int win = find_winner(board);
    int win_help = win;
    while (!end){
        if (hum_move){
            board = human_move(board, choice);
            hum_move = false;
            pr_move = true;
        }
        else if (pr_move){
            board = prog_move(board, choice);
            pr_move = false;
            hum_move = true;
        }
        print_board(board);
        
        int win = find_winner(board);
        win_help = win;
        if (win != -1){
            end = true;
        }
    }

    if (win_help == 2){
        std::cout << "Draw!" << std::endl;

    }
    else if ((win_help == 1) and choice){
        std::cout << "You win!!!" << std::endl;
    }
    else {
        std::cout << "You lose!!!" << std::endl;
    }

    return 0;
}
