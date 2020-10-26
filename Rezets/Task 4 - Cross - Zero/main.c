#include <stdio.h>
#include <stdbool.h>

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

typedef struct{ // Структура для массивов c номером клетки и очков полученных при ходе в нее
    int index[9];
    int score[9];
} move_mass;

typedef struct{ // Структура для возврата номера клетки и очков за ход в нее из функции minimax
    int index;
    int score;
} minimaxstr;

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

// Минимакс функция
minimaxstr* minimax(int newBoard[9], int player){ // Принимает текущее поле и игрока. Выводит номер лучшей клетки для хода и количество очков при ходе в эту клетку
    minimaxstr *mms_p = NULL;
    minimaxstr MMreturn;

    // Вызов функции определения пустых клеток
    inputemptyInd *ms_p = NULL;
    ms_p = emptyIndices(origBoard);

    // Заполнение массива с номерами пустых клеток
    int *availSpotsPtr = ms_p->availSpotsPtr;
    int k = ms_p->k;
    int availSpots[k]; // Массив с номерами пустых клеток
    for (int i = 0; i < k; i++){
        availSpots[i] = *(availSpotsPtr + i);}

    // Проверка на терминальное состояние (победа / поражение / ничья) и запись соответсвующего количества очков
    if (winning(newBoard, huPlayer)){
        MMreturn.score = -10; // Победа человека = -10 очков
        mms_p = &MMreturn;
        return mms_p;
    }
    else if (winning(newBoard, aiPlayer)){
        MMreturn.score = 10; // Победа компьютера = 10 очков
        mms_p = &MMreturn;
        return mms_p;
    }
    else if (k == 0){
        MMreturn.score = 0; // Ничья = 0 очков
        mms_p = &MMreturn;
        return mms_p;
    };

    // Массив(видимый в функции) с местом куда походили и сколько за это очков получили
    struct{
        int index[9];
        int score[9];
    } moves;

    int moves_size = 0; // Размер этого массива

    // Цикл гипотетического хода в свободную клетку и записи очков за этот ход
    for (int i = 0; i < k; i++){ // Цикл повторится столько раз, сколько пустых клеток(возможных ходов)

        // Массив(для цикла) с местом куда походили и сколько за это очков получили
        struct{
            int index[9];
            int score[9];
        } move;

        move.index[i] = newBoard[ availSpots[i] ]; // Записываем номер свободной клетки в которую будем ходить
        newBoard[ availSpots[i] ] = player; // Делаем ход за текущего игрока

        // Записываем очки после этого хода
        if (player == aiPlayer){ // Если текущий игрок компьтер

            minimaxstr *mms_p = NULL;
            mms_p = minimax(newBoard, huPlayer); // Ходим за человека и погружаемся на уровень ниже
            // Но если ход был конечным, то погружения не произойдет, и на моменте проверки на терминальное состояние нам вернет очки за ход компьютера
            move.score[i] = mms_p -> score; // Тут мы и записываем эти очки победа компьютера 10, победа человека -10, ничья 0
        }
        else{ // Если ход человека
            minimaxstr *mms_p = NULL;
            mms_p = minimax(newBoard, aiPlayer); // Ходим за компьютер и погружаемся на уровень ниже
            // Но если ход был конечным, то погружения не произойдет, и на моменте проверки на терминальное состояние нам вернет очки за ход человека
            move.score[i] = mms_p -> score; // Тут мы и записываем эти очки победа компьютера 10, победа человека -10, ничья 0
        }

        newBoard[availSpots[i]] = move.index[i]; // Возваращаем в ячейку значение, которое было до гипотетического хода, чтобы можно было походить в следующую клетку и посмотреть очки
        moves.index[i] = move.index[i]; // Выводим из цикла значение поля куда ходили
        moves.score[i] = move.score[i]; // Выводим из цикла значение очков которые получили
        moves_size++;
    }

    // Определение лучшего хода
    int bestMove = 0; // Номер лучшего хода

    if(player == aiPlayer){ // Если ход компьютера
        int bestScore = -10; // Граница для сравнения
        for(int i = 0; i < moves_size; i++){
            if(moves.score[i] > bestScore){ // Сравниваем очки с границей
                bestScore = moves.score[i];
                bestMove = i; // В bestMove передается номер клетки с наибольшим количеством очков
            }
        }
    }
    else{ // Если ход человека
        int bestScore = 10; // Граница для сравнения
        for(int i = 0; i < moves_size; i++){
            if(moves.score[i] < bestScore){ // Сравниваем очки с границей
                bestScore = moves.score[i];
                bestMove = i; // В bestMove передается номер клетки с наименьшим количеством очков
            }
        }
    }
    // Итог сравнения: Определяется лучший ход для компьютера. !!! Также определяется лучший ход и для человека, когда компьютер ходит от его лица. Т.к. от лица компьютера лучший ход - тот что принес 10, а от лица человека лучший ход - тот что принес -10. То есть когда алгоритм моделирует поведение человека, он представляет что соревнуется с самым умным человеком, который не проигрывает.

    // Передача лучшего хода с его счетом из функции
    MMreturn.index = moves.index[bestMove];
    MMreturn.score = moves.score[bestMove];
    mms_p = &MMreturn;
    return mms_p;
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
        printf("AI won!!!\n\n");
        return true;
    }
    else if (winning(newBoard, huPlayer)){ // Если победил человек
        printf("LOL it's imposible\n)");
        return true;
    }
    else if (k == 0){ // Если пустых клеток нет и никто не победил, то ничья
        printf("Draw)\n\n");
        return true;
    }
    else // Если игра не закончилась
        return false;
}

// Для завершения функции main
bool end_game = false;

int main(void) {

    int Player, spot_hu, spot_ai; // Игрок, клетка хода человека, клетка хода компьютера

    printf("CROSS-ZERO\n\nName of cells:\n\n  0|1|2\n  -+-+-\n  3|4|5\n  -+-+-\n  6|7|8\n\nChose your fighter: 11 - cross or 10 - zero\n");

    // Считываем за кого будет играть пользователь
    scanf("%d", &Player);
    huPlayer = Player;

    // Определяем за кого играет компьютер
    if (huPlayer == 11)
        aiPlayer = 10;
    else
        aiPlayer = 11;

    // Если пользователь нолик
    if (huPlayer == 10){
        while (1){
            // Вызываем минимакс
            minimaxstr *mms_p = NULL;
            mms_p = minimax(origBoard, aiPlayer);

            printf("AI's turn\n");

            spot_ai = mms_p -> index; // Клетка хода компьютера - лучший ход из минимакса
            input(aiPlayer, spot_ai); // Ходим за компьютер в клетку лучшего хода
            output(); // Выводим поле

            // Проверяем на конец игры
            if (End(origBoard))
                return 0;

            printf("Your turn\n");

            scanf("%d", &spot_hu); // Считываем клетку хода пользователя
            input(huPlayer, spot_hu); // Ходим в эту клетку
            output(); // Выводим поле

            // Проверяем на конец игры
            if (End(origBoard))
                return 0;
        }
    }

    // Если пользователь крестик
    if (huPlayer == 11){
        while (1){

            printf("Your turn\n");

            scanf("%d", &spot_hu); // Считываем клетку хода пользователя
            input(huPlayer, spot_hu); // Ходим в эту клетку
            output(); // Выводим поле

            // Проверяем на конец игры
            if (End(origBoard))
                return 0;

            // Вызываем минимакс
            minimaxstr *mms_p = NULL;
            mms_p = minimax(origBoard, aiPlayer);

            printf("AI's turn\n");

            spot_ai = mms_p -> index; // Клетка хода компьютера - лучший ход из минимакса
            input(aiPlayer, spot_ai); // Ходим за компьютер в клетку лучшего хода
            output(); // Выводим поле

            // Проверяем на конец игры
            if (End(origBoard))
                return 0;
        }
    }
    return 0;
}
