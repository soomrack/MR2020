#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>

char board[4][4];
int turn_number = 0;
bool wwin = false;
bool server_work = true;

void pokazat_hod_igri() {
    printf("\n %c | %c | %c \n---+---+---\n %c | %c | %c \n---+---+---\n %c | %c | %c \n\n",
           board[1][1], board[1][2], board[1][3], board[2][1], board[2][2], board[2][3], board[3][1], board[3][2], board[3][3]);
}

void game_start(){
    for (int i=1; i<=3; i++) {        //
        for (int j=1; j<=3; j++) {    //
            board[i][j]=' ';          //
        }
    }
    printf(" 1 | 2 | 3 \n---+---+---\n 4 | 5 | 6 \n---+---+---\n 7 | 8 | 9 \n\n");
    pokazat_hod_igri();
}

int read() {    // не используетс€ в программе, т.к. отсутвует ввод в консоль
    int cell_number;
    printf("Your turn\nEnter the number of cell\n");
    scanf("%d" , &cell_number);
    return cell_number;
}

void write(int b, int player) {
    if (player == 0) {
        if (b == 1) board[1][1]='O';
        if (b == 2) board[1][2]='O';
        if (b == 3) board[1][3]='O';
        if (b == 4) board[2][1]='O';
        if (b == 5) board[2][2]='O';
        if (b == 6) board[2][3]='O';
        if (b == 7) board[3][1]='O';
        if (b == 8) board[3][2]='O';
        if (b == 9) board[3][3]='O';
    }
    if (player == 1) {
        if (b == 1) board[1][1] = 'X';
        if (b == 2) board[1][2] = 'X';
        if (b == 3) board[1][3] = 'X';
        if (b == 4) board[2][1] = 'X';
        if (b == 5) board[2][2] = 'X';
        if (b == 6) board[2][3] = 'X';
        if (b == 7) board[3][1] = 'X';
        if (b == 8) board[3][2] = 'X';
        if (b == 9) board[3][3] = 'X';
    }
}

bool place_available(int a) {
    bool proverka = true;
    int i,j;
    if (a == 1) {i=1; j=1;}
    if (a == 2) {i=1; j=2;}
    if (a == 3) {i=1; j=3;}
    if (a == 4) {i=2; j=1;}
    if (a == 5) {i=2; j=2;}
    if (a == 6) {i=2; j=3;}
    if (a == 7) {i=3; j=1;}
    if (a == 8) {i=3; j=2;}
    if (a == 9) {i=3; j=3;}
    if (board[i][j] == 'X' || board[i][j] == 'O') {
        proverka = false;
    }
    return  proverka;
}

int decrypto(int a, int b) {
    int res;
    if (a==1 && b==1) res = 1;
    if (a==1 && b==2) res = 2;
    if (a==1 && b==3) res = 3;
    if (a==2 && b==1) res = 4;
    if (a==2 && b==2) res = 5;
    if (a==2 && b==3) res = 6;
    if (a==3 && b==1) res = 7;
    if (a==3 && b==2) res = 8;
    if (a==3 && b==3) res = 9;
    return res;
}

int win_move(int igrok) {
    int res = 0;
    char player;
    if (igrok==1) player='X';
    if (igrok==0) player='O';
    for (int i=1; i<=3; i++) // €®ютх®ър €ю Є™юысшърь
    {
        if (board[1][i]==player && board[2][i]==player && board[3][i]==' ') {board[3][i]=player; return decrypto(3,i);}
        if (board[1][i]==' ' && board[2][i]==player && board[3][i]==player) {board[1][i]=player; return decrypto(1,i);}
        if (board[1][i]==player && board[2][i]==' ' && board[3][i]==player) {board[2][i]=player; return decrypto(2,i);}
    }
    for ( int i=1; i<=3; i++)
    {
        if (board[i][1]==player && board[i][2]==player && board[i][3]==' ') {board[i][3]=player; return decrypto(i,3);}
        if (board[i][1]==' ' && board[i][2]==player && board[i][3]==player) {board[i][1]=player; return decrypto(i,1);}
        if (board[i][1]==player && board[i][2]==' ' && board[i][3]==player) {board[i][2]=player; return decrypto(i,2);}
    }
    if (board[1][1]==player && board[2][2]==player && board[3][3]==' ') {board[3][3]=player; return decrypto(3,3);}
    if (board[1][1]==player && board[2][2]==' ' && board[3][3]==player) {board[2][2]=player; return decrypto(2,2);}
    if (board[1][1]==' ' && board[2][2]==player && board[3][3]==player) {board[1][1]=player; return decrypto(1,1);}
    if (board[3][1]==player && board[2][2]==player && board[1][3]==' ') {board[1][3]=player; return decrypto(1,3);}
    if (board[3][1]==player && board[2][2]==' ' && board[1][3]==player) {board[2][2]=player; return decrypto(2,2);}
    if (board[3][1]==' ' && board[2][2]==player && board[1][3]==player) {board[3][1]=player; return decrypto(3,1);}
    return res;
}

int enemy_win_block (int igrok) {
    int res = 0;
    char enemy;
    char player;
    if (igrok == 1) {
        enemy = 'O';
        player = 'X';
    }
    if (igrok == 0) {
        enemy = 'X';
        player = 'O';
    }
    for (int i=1; i<=3; i++) {
        if (board[1][i]==enemy && board[2][i]==enemy && board[3][i]==' ') {board[3][i]= player; return decrypto(3,i);}
        if (board[1][i]==' ' && board[2][i]==enemy && board[3][i]==enemy) {board[1][i]= player; return decrypto(1,i);}
        if (board[1][i]==enemy && board[2][i]==' ' && board[3][i]==enemy) {board[2][i]= player; return decrypto(2,i);}
    }
    for ( int i=1; i<=3; i++) {
        if (board[i][1]==enemy && board[i][2]==enemy && board[i][3]==' ') {board[i][3]= player; return decrypto(i,3);}
        if (board[i][1]==' ' && board[i][2]==enemy && board[i][3]==enemy) {board[i][1]= player; return decrypto(i,1);}
        if (board[i][1]==enemy && board[i][2]==' ' && board[i][3]==enemy) {board[i][2]= player; return decrypto(i,2);}
    }
    if (board[1][1]==enemy && board[2][2]==enemy && board[3][3]==' ') {board[3][3]= player; return decrypto(3,3);}
    if (board[1][1]==enemy && board[2][2]==' ' && board[3][3]==enemy) {board[2][2]= player; return decrypto(2,2);}
    if (board[1][1]==' ' && board[2][2]==enemy && board[3][3]==enemy) {board[1][1]= player; return decrypto(1,1);}

    if (board[3][1]==enemy && board[2][2]==enemy && board[1][3]==' ') {board[1][3]= player; return decrypto(1,3);}
    if (board[3][1]==enemy && board[2][2]==' ' && board[1][3]==enemy) {board[2][2]= player; return decrypto(2,2);}
    if (board[3][1]==' ' && board[2][2]==enemy && board[1][3]==enemy) {board[3][1]= player; return decrypto(3,1);}
    //printf("blocked result is "); отладка
    //("%d\n", res); отладка
    return res;
}


int computer_turn (int igrok) {
    char player;
    if (igrok==1) player='X';
    if (igrok==0) player='O';
    int res = 0;
    // занимаем центр
    if (place_available(5)) {board[2][2] = player; return decrypto(2,2);}
    // угловые с сочетанием
    if (board[1][1]== player && place_available(3)) {board[1][3] = player; return decrypto(1,3);}
    if (board[1][3]== player && place_available(9)) {board[3][3] = player; return decrypto(3,3);}
    if (board[3][3]== player && place_available(7)) {board[3][1] = player; return decrypto(3,1);}
    if (board[3][1]== player && place_available(1)) {board[1][1] = player; return decrypto(1,1);}
    // угловые
    if (place_available(1)) {board[1][1] = player; return decrypto(1,1);}
    if (place_available(3)) {board[1][3] = player; return decrypto(1,3);}
    if (place_available(7)) {board[3][1] = player; return decrypto(3,1);}
    if (place_available(9)) {board[3][3] = player; return decrypto(3,3);}
    // оставшиес€
    if (place_available(2)) {board[1][2] = player; return decrypto(1,2);}
    if (place_available(6)) {board[2][3] = player; return decrypto(2,3);}
    if (place_available(8)) {board[3][2] = player; return decrypto(3,2);}
    if (place_available(4)) {board[2][1] = player; return decrypto(2,1);}
    return res;
}


void game_end(){
    int res;
    printf("All cells are busy\nDRAW!!!\nGAME OVER\nEnter 1 to exit\n");
    Sleep(2000);
    scanf("%d\n", res);
    if (res==1) {
        printf("closing\n");
        Sleep(1000);
    }
}
int first_turn(int player){
    int res;
    res = computer_turn(player);
    pokazat_hod_igri();
    turn_number++;
    return res;
}

int hod(int a, int player) {
    int enemy;
    if (player==1) enemy = 0;
    if (player==0) enemy = 1;
    write(a, enemy);
    printf("enemy cell number is %d\n", a);
    pokazat_hod_igri();
    turn_number++;
    printf("turn number is %d\n", turn_number);
    if (turn_number==9) {
        return 10; // 10 - если псоледний ход был за противником
    }
    Sleep(6000);
    int block;
    int res;
    if (win_move(player)==0) {
        block = enemy_win_block(player);
        if (block==0) {
            //printf("computer turn\n"); отладка
            res = computer_turn(player);
        } else {
            res = block;
            //printf("enemy blocked\n"); отладка
            //printf("%d\n", res);
        }
    } else {
        wwin = true;
        res = win_move(player);
        //printf("win moving\n");  //отладка
    }
    write(res, player);
    printf("my cell number is %d\n", res);
    pokazat_hod_igri();
    turn_number++;
    printf("turn number is %d\n", turn_number);
    Sleep(6000);
    return res;
}




int main(){
    WSADATA ws;
    WSAStartup( MAKEWORD(2,2), &ws);  // инициализаци€ использовани€ сокета

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);  // создание сокета

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;                // работа с адресом IpV4
    sa.sin_port = htons(1234);     // и портом 1234

    char c;
    printf("s - server\nc - client\n");
    scanf("%c", &c);

    int buf[1];
    memset(buf, 0, sizeof(buf));

    if (c == 'c') {
        sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  // адресс подключени€ (сервера)
        connect(s, &sa, sizeof(sa));                          // устанавливаем соединение с сервером

        game_start();
        printf("client plays for zeros\ncrosses go first\n");

        int enemy_turn;
        int our_turn;

        while (server_work) {
            recv(s, buf, sizeof(buf), 0);
            enemy_turn = buf[0];
            our_turn = hod(enemy_turn, 0);
            if (our_turn==10) { // процедура ход возвращает 10 в случае ничьи
                game_end();     // и если последний ход мы прин€ли от противника
                return 0;
            }
            buf[0] = our_turn;
            send(s, buf, sizeof(buf), 0);
            if (turn_number==9) {   // случай если последних ход мы отправили противникку
                game_end();
                return 0;
            }
        }
    }

    if (c == 's') {
        bind(s, &sa, sizeof(sa));
        listen(s, 100);         // прослушка вход€щих сообщений
        // переменные дл€ хранени€ информации о соединении
        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);

        while (client_socket = accept(s, &client_addr, &client_addr_size)) {   // установка соединени€ с клиентом
            printf("players are connected\n");
            game_start();
            printf("server plays for crosses\n");
            buf[0] = first_turn(1);
            int enemy_turn;
            int our_turn;
            send(client_socket, buf, sizeof(buf), 0); // отправка первого хода клиенту
            while(server_work) {
                recv(client_socket, buf, sizeof(buf), 0);
                enemy_turn = buf[0];
                our_turn = hod(enemy_turn, 1);
                if (our_turn==10) { // процедура ход возвращает 10 в случае ничьи
                    game_end();     // и если последний ход мы прин€ли от противника
                    return 0;
                }
                buf[0] = our_turn;
                send(client_socket, buf, sizeof(buf), 0);
                if (turn_number==9) {  // случай если последних ход мы отправили противникку
                    game_end();
                    return 0;
                }
            }
        }
    }
    closesocket(s);
    return 0;
}
