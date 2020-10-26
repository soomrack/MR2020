#include <stdio.h>
#include <stdbool.h>
#include <winsock2.h>

int start_cell = 4; // Первая клетка в которой будет крестик

int huPlayer = 10; // Обозначение О
int aiPlayer = 11; // Обозначение Х

// Текущее содержимое поля
int origBoard[9] = { 0,  1,  2,
                     3,  4,  5,
                     6,  7,  8};

typedef struct{ // Структура для возврата из функции значения k и массива
    int k; // Количество свободных клеток на поле
    int *availSpotsPtr; // Указатель на массив номеров свободных клеток
} inputemptyInd;

// Победные комбинации
bool winning(int board[9], int player){ // Принимает текущее поле и игрока на победу которого мы проверяем, возвращает true если победил, false если нет
    if (
            (board[0] == player && board[1] == player && board[2] == player) ||
            (board[3] == player && board[4] == player && board[5] == player) ||
            (board[6] == player && board[7] == player && board[8] == player) ||
            (board[0] == player && board[3] == player && board[6] == player) ||
            (board[1] == player && board[4] == player && board[7] == player) ||
            (board[2] == player && board[5] == player && board[8] == player) ||
            (board[0] == player && board[4] == player && board[8] == player) ||
            (board[2] == player && board[4] == player && board[6] == player)
            )
        return true;
    else
        return false;
}

// Функция определения номеров пустых клеток
inputemptyInd* emptyIndices(int board[9]){ // Принимает текущее поле
    inputemptyInd *ms_p = NULL;
    inputemptyInd Ms;

    // Определение размера массива для хранения количества пустых клеток
    int size = 0;
    for (int i = 0; i <= 8; i++){
        if (board[i] != 11 && board[i] != 10)
            size++;
    }

    // Запись в массив номеров пустых клеток
    Ms.k = 0; // Номер ячейки массива в которую будет записан номер свободной клетки на поле
    int availSpotsloc[size];
    for (int i = 0; i <= 8; i++){
        if (board[i] != 11 && board[i] != 10){
            availSpotsloc[Ms.k] = i; // Запись номеров свободных клеток
            Ms.k++; // k при выходе из этого цикла совпадает с размером массива
        }
    }

    Ms.availSpotsPtr = availSpotsloc; // Передача массива для вывода из функции
    ms_p = &Ms;
    return ms_p;
}

// Функция изменения поля
void input (int Player, int spot){ // Принимает игрока и клетку куда он ходит
    if (Player == 11)
        origBoard[spot] = 11;
    else if (Player == 10)
        origBoard[spot] = 10;
}

// Массив для перевода цифры от 0 до 8 в ее символ
char int_to_str[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

// Функция вывода поля
void output (){
    char cell[9];
    for (int i = 0; i < 9; i++){
        if (origBoard[i] == 11)
            cell[i] = 'X';
        else if (origBoard[i] == 10)
            cell[i] = 'O';
        else // Если не О и не Х то ставит номер клетки, для удобства пользователя
            cell[i] = int_to_str[i];
    }
    printf("\n  %c|%c|%c\n  -+-+-\n  %c|%c|%c\n  -+-+-\n  %c|%c|%c\n\n", cell[0], cell[1], cell[2], cell[3], cell[4], cell[5], cell[6], cell[7], cell[8]);
}

// Функция проверки поля на предмет конца игры
bool End (int newBoard[9]){ // Принимает поле, возвращает true если конец игры, false если нет

// Вызываем функцию определения пустых клеток с целью получить k(количество пустых клеток)
    inputemptyInd *ms_p = NULL;
    ms_p = emptyIndices(origBoard);

// Получаем k(количество пустых клеток)
    int k = ms_p->k;

    if (winning(newBoard, aiPlayer)){ // Если победил компьютер
        printf("Server won!!!\n\n");
        return true;
    }
    else if (winning(newBoard, huPlayer)){ // Если победил человек
        printf("Client won!!!\n\n");
        return true;
    }
    else if (k == 0){ // Если пустых клеток нет и никто не победил, то ничья
        printf("Draw)\n\n");
        return true;
    }
    else // Если игра не закончилась
        return false;
}

// Номер первой свободной клетки
int aiCell(int origBoard[9]){
    // Вызов функции определения пустых клеток
    inputemptyInd *ms_p = NULL;
    ms_p = emptyIndices(origBoard);

    // Заполнение массива с номерами пустых клеток
    int *availSpotsPtr = ms_p->availSpotsPtr;
    int k = ms_p->k;
    int availSpots[k]; // Массив с номерами пустых клеток
    for (int i = 0; i < k; i++){
        availSpots[i] = *(availSpotsPtr + i);}
    return availSpots[0];
}

void game_end(){
    int res;
    printf("Enter 1 to exit\n");
    Sleep(2000);
    scanf("%d\n", res);
    if (res==1) {
        printf("closing\n");
        Sleep(1000);
    }
}

bool server_work = true;

int main()
{
    WSADATA ws;
    WSAStartup( MAKEWORD(2,2), &ws);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1234);

    char c;
    printf("s - server\nc - client\n");
    scanf("%c", &c);

    int buf[9]; // Передаваемый массив
    memset(buf, 0, sizeof(buf));

    aiPlayer = 11; //Сервер крестик
    huPlayer = 10; //Клиент нолик

    int spot_ai; //Клетка хода
    printf("CROSS-ZERO\n\n");

    if (c == 'c') {
        sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        connect(s, &sa, sizeof(sa));
        printf("Client plays for zero\n");
        printf("Board\n");
        output();

        while (server_work) {
            // Клиент играет за нолик
            recv(s, buf, sizeof(buf), 0); // Получить поле

            printf("Server's turn\n");

            for (int i = 0; i < 9; i++){
                origBoard[i] = buf[i];
            }
            Sleep(2000);
            output(); // Выводим поле

            // Проверяем на конец игры
            if (End(origBoard)){
                game_end();
                return 0;
            }

            printf("Client's turn\n");

            spot_ai = aiCell(origBoard);
            input(huPlayer, spot_ai);
            output();
            for (int i = 0; i < 9; i++){
                buf[i] = origBoard[i];
            }
            send(s, buf, sizeof(buf), 0);

            if (End(origBoard)) {
                game_end();
                return 0;
            }
        }
    }

    if (c == 's') {
        bind(s, &sa, sizeof(sa));
        listen(s, 100);
        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);

        while (client_socket = accept(s, &client_addr, &client_addr_size)) {
            printf("Players are connected\n");
            printf("Server plays for crosses\n");

            origBoard[start_cell] = aiPlayer;
            for (int i = 0; i < 9; i++){
                buf[i] = origBoard[i];
            }

            send(client_socket, buf, sizeof(buf), 0); //
            printf("Server's turn\n");
            output();
            while(server_work) {
                recv(client_socket, buf, sizeof(buf), 0);

                printf("Client's turn\n");

                for (int i = 0; i < 9; i++){
                    origBoard[i] = buf[i];
                }
                Sleep(2000);
                output(); // Выводим поле

                // Проверяем на конец игры
                if (End(origBoard)){
                    game_end();
                    return 0;
                }

                printf("Server's turn\n");

                spot_ai = aiCell(origBoard);
                input(aiPlayer, spot_ai);
                output();
                for (int i = 0; i < 9; i++){
                    buf[i] = origBoard[i];
                }
                send(client_socket, buf, sizeof(buf), 0);
                if (End(origBoard)) {
                    game_end();
                    return 0;
                }
            }
        }
    }
    closesocket(s);
    return 0;
}