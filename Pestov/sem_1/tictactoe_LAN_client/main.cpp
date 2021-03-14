#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

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

void board2buf(char (&buf)[4096], board_t board){
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            // MB wrong 
            buf[i*3+j] = board.A[i][j]; 
        }
    }

}

board_t buf2board(char (&buf)[4096]){
    board_t board;
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            // MB wrong 
            board.A[i][j] = buf[i*3+j];
        }
    }
    return board;
}

int main(int argc, char const *argv[])
{
      // Создание доски и начало игры для LAN версии первых ходит всегда клиент, тестовая проверка на победителя
    bool end = false;
    bool pr_move = false; 
    bool hum_move = true;
    bool choice = true;
    board_t board = create_board();
    print_board(board);
    int win = find_winner(board);
    int win_help = win;









    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Can't create a socket";
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    std::string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        std::cerr << "Can't connect a socket";
        return 1;
    }

    //	While loop:
    char buf[4096];
    std::string userInput;














    do {
        //		Enter lines of text
        std::cout << "Client move: " << std::endl;
        board = prog_move(board, !choice);
        print_board(board);
        memset(buf, 0, 4096);
        board2buf(buf, board);


        //		Send to server
        int sendRes = send(sock, buf, 10, 0);
        if (sendRes == -1)
        {
            std::cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cout << "There was an error getting response from server\r\n";
        }
        else
        {
            std::cout << "Server move: " << std::endl;
            board = buf2board(buf);
            print_board(board); 

        }
        
        int win = find_winner(board);
        win_help = win;
        if (win != -1){
            break;
        }


    } while(true);














    if (win_help == 2){
        std::cout << "Draw!" << std::endl;

    }
    else if ((win_help == 1) and choice){
        std::cout << "You win!!!" << std::endl;
    }
    else {
        std::cout << "You lose!!!" << std::endl;
    }
    
    //	Close the socket
    close(sock);


    return 0;
}
