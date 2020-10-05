#include <stdio.h>
#include <stdbool.h>

char board[4][4];   // рабочая матрица

// функция выводит в консоль текущее игровое поле
void pokazat_hod_igri() {
    printf("%c | %c | %c\n--+---+--\n%c | %c | %c\n--+---+--\n%c | %c | %c\n",
           board[1][1], board[1][2], board[1][3], board[2][1], board[2][2], board[2][3], board[3][1], board[3][2], board[3][3]);
}

// Начало работы программы (ознакомление с условиями)
void start() {
    for (int i=1; i<=3; i++) {        //
        for (int j=1; j<=3; j++) {    // первоначально заполнение рабочего поля пустыми символами
            board[i][j]=' ';          //
        }
    }
    printf("1 | 2 | 3\n--+---+--\n4 | 5 | 6\n--+---+--\n7 | 8 | 9\n") ;
    board[2][2] = 'X';   // первый ход всегда за комьютером, и он всегда ставит крестик в середину
    printf("First move by computer (cross)\n");
    pokazat_hod_igri();
}

//Функция считывание номера клетки, в которую ходит игрок. И возвращает этот номер
int read() {
    int cell_number;
    printf("Enter the number of cell\n");
    scanf("%d" , &cell_number);
    return cell_number;
}

// Записать введеные пользователем данные на доску
void write(int a) {
    if (a==1) board[1][1]='O';
    if (a==2) board[1][2]='O';
    if (a==3) board[1][3]='O';
    if (a==4) board[2][1]='O';
    if (a==5) board[2][2]='O';
    if (a==6) board[2][3]='O';
    if (a==7) board[3][1]='O';
    if (a==8) board[3][2]='O';
    if (a==9) board[3][3]='O';
}

// Проверка условия на занято ли место ввода
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
    //printf("Proverka succesfuly\n");  отладка
    return  proverka;
}

// если компьютер видит, что есть выйгрышная ситуация, то он делает победный ход
bool win_move() {
    bool win = false;
    for (int i=1; i<=3; i++) // проверка по столбикам
    {
        if (board[1][i]=='X' && board[2][i]=='X' && board[3][i]==' ') {board[3][i]='X'; win = true;}
        if (board[1][i]==' ' && board[2][i]==' ' && board[3][i]=='X') {board[1][i]='X'; win = true;}
        if (board[1][i]=='X' && board[2][i]==' ' && board[3][i]=='X') {board[2][i]='X'; win = true;}
    }
    for ( int i=1; i<=3; i++) // проверка по горизонтали
    {
        if (board[i][1]=='X' && board[i][2]=='X' && board[i][3]==' ') {board[i][3]='X'; win = true;}
        if (board[i][1]==' ' && board[i][2]=='X' && board[i][3]=='X') {board[i][1]='X'; win = true;}
        if (board[i][1]=='X' && board[i][2]==' ' && board[i][3]=='X') {board[i][2]='X'; win = true;}
    }
    // проверка диагонали
    if (board[1][1]=='X' && board[2][2]=='X' && board[3][3]==' ') {board[3][3]='X'; win = true;}
    if (board[1][1]=='X' && board[2][2]==' ' && board[3][3]=='X') {board[2][2]='X'; win = true;}
    if (board[1][1]==' ' && board[2][2]=='X' && board[3][3]=='X') {board[1][1]='X'; win = true;}
    // проверка другой диагонали
    if (board[3][1]=='X' && board[2][2]=='X' && board[1][3]==' ') {board[1][3]='X'; win = true;}
    if (board[3][1]=='X' && board[2][2]==' ' && board[1][3]=='X') {board[2][2]='X'; win = true;}
    if (board[3][1]==' ' && board[2][2]=='X' && board[1][3]=='X') {board[3][1]='X'; win = true;}
    return win;
}

// брокировка хода противника, если он может выйграть в следующий ход
bool enemy_win_block () {
    bool block = false;
    for (int i=1; i<=3; i++) // по столбикам
    {
        if (board[1][i]=='O' && board[2][i]=='O' && board[3][i]==' ') {board[3][i]='X'; block = true;}
        if (board[1][i]==' ' && board[2][i]=='O' && board[3][i]=='O') {board[1][i]='X'; block = true;}
        if (board[1][i]=='O' && board[2][i]==' ' && board[3][i]=='O') {board[2][i]='X'; block = true;}
    }
    for ( int i=1; i<=3; i++) // по горизонтали
    {
        if (board[i][1]=='O' && board[i][2]=='O' && board[i][3]==' ') {board[i][3]='X'; block = true;}
        if (board[i][1]==' ' && board[i][2]=='O' && board[i][3]=='O') {board[i][1]='X'; block = true;}
        if (board[i][1]=='O' && board[i][2]==' ' && board[i][3]=='O') {board[i][2]='X'; block = true;}
    }
    // по диагонали
    if (board[1][1]=='O' && board[2][2]=='O' && board[3][3]==' ') {board[3][3]='X'; block = true;}
    if (board[1][1]=='O' && board[2][2]==' ' && board[3][3]=='O') {board[2][2]='X'; block = true;}
    if (board[1][1]==' ' && board[2][2]=='O' && board[3][3]=='O') {board[1][1]='X'; block = true;}
    // по другой диагонали
    if (board[3][1]=='O' && board[2][2]=='O' && board[1][3]==' ') {board[1][3]='X'; block = true;}
    if (board[3][1]=='O' && board[2][2]==' ' && board[1][3]=='O') {board[2][2]='X'; block = true;}
    if (board[3][1]==' ' && board[2][2]=='O' && board[1][3]=='O') {board[3][1]='X'; block = true;}
    return block;
}

// ход компьютера при условии, что нет ни победных ходов ни ходов на предотвращение победы противника
int computer_turn () { // приоритетнее занимать угловые клеточки, если они не знаяты
    // приоритетнее занимать угловые клетки у которых в смежном углу уже стоит крестик
    if (board[1][1]=='X' && place_available(3)) {board[1][3] = 'X'; return 0;}
    if (board[1][3]=='X' && place_available(9)) {board[3][3] = 'X'; return 0;}
    if (board[3][3]=='X' && place_available(7)) {board[3][1] = 'X'; return 0;}
    if (board[3][1]=='X' && place_available(1)) {board[1][1] = 'X'; return 0;}
    // далее по приоритету идут любые угловые клетки
    if (place_available(1)) {board[1][1] = 'X'; return 0;}
    if (place_available(3)) {board[1][3] = 'X'; return 0;}
    if (place_available(7)) {board[3][1] = 'X'; return 0;}
    if (place_available(9)) {board[3][3] = 'X'; return 0;}
    // если же все угловые клеточки заняты то ставим крестик в любую свободную ячейку
    if (place_available(2)) {board[1][2] = 'X'; return 0;}
    if (place_available(6)) {board[2][3] = 'X'; return 0;}
    if (place_available(8)) {board[3][2] = 'X'; return 0;}
    if (place_available(4)) {board[2][1] = 'X'; return 0;}
    return 0;
}


// процесс игры
int work () {
    int turn_number = 1;        // количество ходов которое прошло в игре
    while (turn_number <= 8) {  //игра до тех пор пока не закончиться поле
        int turn = read();
        if (place_available(turn)) { // ход игрока
            write(turn);
            turn_number++;
            printf("zeros have turned\n");
            pokazat_hod_igri();
            if (win_move()) {
                pokazat_hod_igri();
                printf("Crosses won!!!\n");
                return 0;
            }
            if (enemy_win_block()) {
                pokazat_hod_igri();
                printf("enemy blocked\n"); //отладка
                turn_number++;
            } else {
                computer_turn();
                pokazat_hod_igri();
                turn_number++;
            }
        } else printf("Cell is busy choose another\n");
        printf("turn number %d\n" , turn_number );
    }
    printf("DRAW\n");
    return 0;
}


int main() {
    start();
    work();
    return 0;
}