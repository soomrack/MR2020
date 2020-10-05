// tictactoe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// tictactoe.cpp : Эта программа позволяет поиграть в крестики нолики с компьютером.

#include <iostream>
#include <ctime>
using namespace std;

char board[9] = { '_','_','_','_','_','_',' ',' ',' ' }; // Наша доска ходов
bool board_bool[9] = {false,false, false, false, false, false, false, false, false}; // Заполненность поля
bool someone_won = false; // Выиграл ли кто-нибудь

void show_options() { // Эта функция (1) показывает варианты ходов, нумерует клетки для удобства, приветствует.
    cout << "Okey, let's start playing tic-tac-toe with your computer!\n";
    cout << "Here is your options: \n";
    cout << " _1_|_2_|_3_ \n";
    cout << " _4_|_5_|_6_ \n";
    cout << "  7 | 8 | 9  \n";
    cout << "Now, make the first move!\n";
   }

void show_board() { // Эта функция (2) будет выводить на экран игровое поле
    cout << " _" << board[0] << "_|_" << board[1] << "_|_" << board[2] << "_ \n";
    cout << " _" << board[3] << "_|_" << board[4] << "_|_" << board[5] << "_ \n";
    cout << "  " << board[6] << " | " << board[7] << " | " << board[8] << "  \n";
}

int get_move() {
    int move; //Эта функция (3) будет считывать ходы 
    cin >> move;
    while (move > 9||move < 1||board_bool[move-1]==true) {
         cout << "Incorrect data. Choose the number between 1 and 9.\n";
          cin >> move;
    }
    return move;
}

bool check_won_bool() { // Эта функция (4) будет проверять, есть ли победитель
    int winners[8][3] = { {0,4,8},{2,4,6},{0,3,6},{1,4,7},{2,5,8},{0,1,2},{3,4,5},{6,7,8} };
    int k = 0;
    for (int i = 0; i < 8; i++) {
        int one = winners[i][0];
        int two = winners[i][1];
        int three = winners[i][2];
        if ((board[one] == board[two])&&(board[one]== board[three])) {
            if ((board_bool[one] == board_bool[two])&&(board_bool[one] == board_bool[three])&&(board_bool[one] ==true)) {
               someone_won = true;
               k = i;
            }
        }
    }
    if (someone_won == true) {
        cout <<"\nThe winner is " << board[winners[k][0]] << endl;
        return true;
    }
    else return false;
}

int get_random_move() { // Это функция (5) делает рандомные ходя за компьютер
    int random_move;
    srand(static_cast<unsigned int>(time(0)));
    random_move = rand() % 9;
    while (board_bool[random_move - 1] == true) {
        random_move = rand() % 9;
    }
    return random_move;
}

int main()
{
   //setlocale(LC_ALL, "Rus");
    show_options(); // показываем варианты ходов (1)
    int k = 0; // количество ходов в целом
    show_board(); //показываем игровое поле (*2)
    while (someone_won == false) { // Если никто не выиграл
        int move; // (3)
        if ((k % 2) == 0) {
            move = get_move(); // первым ходит юзер
            board[move - 1] = 'x';
            cout << "Your move: \n";
        }
        else {
            move = get_random_move(); // вторым ходит (рандомный наш) компьютер
            board[move - 1] = 'o';
            cout << "Your opponent's move: \n";
        }
        board_bool[move - 1] = true;
        show_board(); // Показываем обновлённое поле (2)
        check_won_bool(); // Проверяем выигрыш одного из игроков (4)
        k++;
    }
}


// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
