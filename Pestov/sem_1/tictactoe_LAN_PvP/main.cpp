/*
WARNING --- only linux (socket libs)

git: https://github.com/pestahub/progHL_proj

The 5th assignment of programming in a high level language

LAN application - game tic tac toe (PC vs PC). 

Principle of operation:
    // The game board is created. 
    // The user chooses who he wants to play for (X or 0)
    // Human move
    // Program move (random)
    // The end
    
    //Debag
    Merge with test_ server: 
        // - The first message to interprint as a first move
        // - I make the first move if I fail to return the error otherwise
        // - Making a move
        // - Sending a move
        // - Waiting for client's trace

    Another version:
        Resive and send full board instead of movement

    Debag
    Smart program move

*/

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>

struct board_t {
    char A[3][3];
};
struct move_t
{
    int row;
    int col;
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

board_t simple_move(board_t board, bool is_gamemode_X, move_t move_){
    char temp = board.A[move_.col][move_.row];
    if (temp == '-'){
        if (is_gamemode_X){
            board.A[move_.col][move_.row] = 'X';
        }
        else {
            board.A[move_.col][move_.row] = '0';
        }
        
    }
    else {
        board.A[move_.col][move_.row] = 'F';
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

void s2buf(char (&buf)[4096], std::string sbuf){
    for (int i = 0; i < sbuf.length(); i++){
        buf[i] = sbuf[i];
    }
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



move_t str2move(std::string smove){
    move_t move_;
    move_.row = smove[0] - '0';
    move_.col = smove[2] - '0';
    return move_;
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








    // Create a socket connection
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1){
        std::cerr << "Can't create a socket";
        return -1;
    }    
    
    // Binf the socket to a IP / port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1){
        std::cerr << "Can't bind to IP/port";
        return -2;
    }

    // Mark the socket for listening in
    if (listen(listening, SOMAXCONN) == -1){
        std::cerr << "Can't listen!";
        return -3;
    } 

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == -1){
        std::cerr << "Problem with client connecting!";
        return -4;
    }
    // Close the listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result){
        std::cout << host << " connected on " << svc << std::endl;

    } 
    else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;
    } 











    // Цикл обработки запроса
    // While receving - desplay message, echo message
    char buf[4096];
    while (true){
        //Clear the buffer
        memset(buf, 0, 4096);
        // Wait for message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1){
            std::cerr << "These was a connetion issue" << std::endl;
            break;

        }

        if (bytesRecv == 0){
            std::cout << "The client disconnected" << std::endl;
            break;
        }
        


        // // Make move from client
        // std::string hum_mov = std::string(buf, 0, bytesRecv);
        // move_t current_move = str2move(hum_mov);
        // char temp = board.A[current_move.col][current_move.row];
        // board = simple_move(board, choice, current_move);
        // if ((board.A[current_move.col][current_move.row] == 'F') || (current_move.col > 2) || (current_move.row > 2) || (current_move.col < 0) || (current_move.row < 0)){
        //     memset(buf, 0, 4096);
        //     std::string message = "Incorrect possition!";
        //     s2buf(buf, message);
        //     // Resend message
        //     send(clientSocket, buf, message.length() + 1, 0);
        //     board.A[current_move.col][current_move.row] = temp;
        //     continue;
        // }
        // std::cout << "Client move: " << std::endl;

        int win = find_winner(board);
        win_help = win;
        if (win != -1){
            break;
        }



        board = buf2board(buf);
        print_board(board);
        memset(buf, 0, 4096);
        board = human_move(board, choice);
        std::cout << "Server move: " << std::endl;
        print_board(board);
        board2buf(buf, board);

        // Отправляем ход сервера
        send(clientSocket, buf, 9 + 1, 0);

        
        

        
       
    }    

    // Обработка итога игры
    if (win_help == 2){
        std::cout << "Draw!" << std::endl;

    }
    else if ((win_help == 1) and choice){
        std::cout << "You win!!!" << std::endl;
    }
    else {
        std::cout << "You lose!!!" << std::endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}
