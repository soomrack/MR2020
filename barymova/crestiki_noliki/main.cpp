#include <iostream>

//Пользователь играет за нолики, компьютер - за крестики.

int array[3][3];
bool cmp_win = false; //победа компьютера
bool gmr_win = false; //победа игрока

//Обнуление массива как в начале игры так и при повторном запуске
void Zeroing_Array (int Array[3][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Array[i][j] = 10;
        }
    }
}

//Вывод массива
void Output_Array (int Array[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (Array[i][j] == 0){
                std::cout << 'O' << "  ";
            } else if (Array[i][j] == 1){
                std::cout << 'X' << "  ";
            } else if (Array[i][j] == 10){
                std::cout << '*' << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//Проверка индекса ячейки и приведение к программистской записи (считаем с 0, а не с 1)
//UPD: Идея не удалась, поэтому этот код повторяется в Move_Gamer(..)
/*
int Check_Arr (int Arr_k, bool Error){
    if (Arr_k == 1 || Arr_k == 2 ||Arr_k == 3){
        Arr_k--;
    } else {
        std::cout << "The field number can only be an integer in the range 1 to 3";
        Error = true;
    }
    return Arr_k;
}
*/

//Ход компьютера: его логика не совершенна, но многое предусмотрено
void Move_Computer(int Array[3][3]){
    bool comp_moved = false;
    while(!comp_moved){
        if (Array[1][1] == 10){  //если центральная ячейка пустая, то ходим в неё
            Array[1][1] = 1;
            break;
        }
        //Проверяем нет ли какой-то строчки, столбца или диагонали, в которой(ом)
        //нужно сделать всего один ход для ПОБЕДЫ КОМПЬЮТЕРА
        for (int k = 0; k < 3; k++){     //проверка строк
            if (Array[k][0] + Array[k][1] + Array[k][2] == 12){ //пустая=10, занятые комп.=1
                if (Array[k][0] == 10){
                    Array[k][0] = 1;
                } else if (Array[k][1] == 10){
                    Array[k][1] = 1;
                } else{
                    Array[k][2] = 1;
                }
                comp_moved = true;
                break;
            }
        }
        if (comp_moved){  //Это костыль
            break;
        }
        for (int k = 0; k < 3; k++){     //проверка столбцов
            if (Array[0][k] + Array[1][k] + Array[2][k] == 12){
                if (Array[0][k] == 10){
                    Array[0][k] = 1;
                } else if (Array[1][k] == 10){
                    Array[1][k] = 1;
                } else{
                    Array[2][k] = 1;
                }
                comp_moved = true;
                break;
            }
        }
        if (comp_moved){
            break;
        }
        if (Array[0][0] + Array[1][1] + Array[2][2] == 12){  //проверяем главную диагональ
            if (Array[0][0] == 10){
                Array[0][0] = 1;
            } else if (Array[1][1] == 10){
                Array[1][1] = 1;
            } else{
                Array[2][2] = 1;
            }
            break;
        } else if (Array[0][2] + Array[1][1] + Array[2][0] == 12){ //проверяем побочную диагональ
            if (Array[0][2] == 10){
                Array[0][2] = 1;
            } else if (Array[1][1] == 10){
                Array[1][1] = 1;
            } else{
                Array[2][0] = 1;
            }
            break;
        }
        //Проверяем, нет ли какой-то строчки, столбца или диагонали, в которой(ом)
        //игроку нужно сделать всего один ход для ПОБЕДЫ ИГРОКА (мешаем победить)
        for (int k = 0; k < 3; k++){     //проверка строк
            if (Array[k][0] + Array[k][1] + Array[k][2] == 10){ //в двух ячейках 0, в третьей пусто=10
                if (Array[k][0] == 10){
                    Array[k][0] = 1;
                } else if (Array[k][1] == 10){
                    Array[k][1] = 1;
                } else{
                    Array[k][2] = 1;
                }
                comp_moved = true;
                break;
            }
        }
        if (comp_moved){
            break;
        }
        for (int k = 0; k < 3; k++){     //проверка столбцов
             if (Array[0][k] + Array[1][k] + Array[2][k] == 10){
                if (Array[0][k] == 10){
                    Array[0][k] = 1;
                } else if (Array[1][k] == 10){
                    Array[1][k] = 1;
                } else{
                    Array[2][k] = 1;
                }
                comp_moved = true;
                break;
            }
        }
        if (comp_moved){
            break;
        }
        if (Array[0][0] + Array[1][1] + Array[2][2] == 10){  //проверяем главную диагональ
            if (Array[0][0] == 10){
                Array[0][0] = 1;
            } else if (Array[1][1] == 10){
                Array[1][1] = 1;
            } else{
                Array[2][2] = 1;
            }
            break;
        } else if (Array[0][2] + Array[1][1] + Array[2][0] == 10){ //проверяем побочную диагональ
            if (Array[0][2] == 10){
                Array[0][2] = 1;
            } else if (Array[1][1] == 10){
                Array[1][1] = 1;
            } else{
                Array[2][0] = 1;
            }
            break;
        }
        //Если центр занят, не нужно мешать победить и нет возможности победить самому
        //то компьютер рандомно выбриает клетку в углу
        //пока реализации лучше не придумала
        if (Array[0][0] == 10){ //проверяем, чтобы поле было пустым
            Array[0][0] = 1;    //заполняем его
            break;
        } else if (Array[0][2] == 10){
            Array[0][2] = 1;
            break;
        } else if (Array[2][0] == 10){
            Array[2][0] = 1;
            break;
        } else if (Array[2][2] == 10){
            Array[2][2] = 1;
            break;
        }
        break;
    }
    Output_Array(Array);
}

//Ход игрока: принимаем и проверяем индексы, меняем значение ячейки и выводим массив
void Move_Gamer(int Array[3][3]){
    int Arr_i = 0; //в эту переменную вводится строка хода игрока
    int Arr_j = 0; //в эту переменную вводится столбец хода игрока
    bool typing_error = true; //переменная для проверки ввода индексов,
    while(typing_error){      //true, чтобы выполнить цикл хотя бы раз
        typing_error = false;
        std::cin >> Arr_i;
        if (Arr_i == 1 || Arr_i == 2 ||Arr_i == 3){
            Arr_i--;
        } else {
            std::cout << "The field number can only be an integer in the range 1 to 3";
            typing_error = true;
            continue;
        }
        std::cin >> Arr_j;
        if (Arr_j == 1 || Arr_j == 2 ||Arr_j == 3){
            Arr_j--;
        } else {
            std::cout << "The field number can only be an integer in the range 1 to 3" << std::endl;
            typing_error = true;
            continue;
        }
        if (Array[Arr_i][Arr_j] == 10){
            Array[Arr_i][Arr_j] = 0;
            Output_Array(Array);
        } else if (Array[Arr_i][Arr_j] == 0 || Array[Arr_i][Arr_j] == 1){
            std::cout << "This field is already taken" << std::endl;
            typing_error = true;
        }
    }
}

//Проверяем не победил ли кто-нибудь
void Is_Smb_Win(int Array[3][3]){
    gmr_win = false;
    cmp_win = false;
    for (int k = 0; k < 3; k++){     //проверяем строки
        if (Array[k][0] + Array[k][1] + Array[k][2] == 0){
            gmr_win = true;
            break;
        } else if (Array[k][0] + Array[k][1] + Array[k][2] == 3){
            cmp_win = true;
            break;
        }
    }
    for (int i = 0; i < 3; i++){    //проверяем столбцы
        if (Array[0][i] + Array[1][i] + Array[2][i] == 0){
            gmr_win = true;
            break;
        } else if (Array[0][i] + Array[1][i] + Array[2][i] == 3){
            cmp_win = true;
            break;
        }
    }
    if (Array[0][0] + Array[1][1] + Array[2][2] == 0){  //проверяем главную диагональ
        gmr_win = true;
    } else if (Array[0][2] + Array[1][1] + Array[2][0] == 3){ //проверяем побочную диагональ
        cmp_win = true;
    }
}

//Если все строки заняты ходами, то возвращает true
bool All_Fields_Filled (int Array[3][3]){
    bool filled = true;
    for (int k = 0; k < 3; k++){     //проверяем строки
        if (Array[k][0] + Array[k][1] + Array[k][2] > 3) {
            filled = false;
            break;
        }
    }
    return filled;
}

//Цикл игры: обнуление массива, его вывод, ход игрока и т.д
void Game (int Array[3][3]){
    std::cout << "Let's start!" << std::endl;
    Zeroing_Array(Array);
    Output_Array(Array);
    int move_number = 1;
    while((!gmr_win || !cmp_win) & !All_Fields_Filled(Array)){
        if (move_number % 2 == 1){
            Move_Gamer(Array);
        } else {
            Move_Computer(Array);
        }
        move_number++;
        Is_Smb_Win(Array);
        if (gmr_win){
            std::cout << "Gamer win!" << std::endl;
            break;
        }
        if (cmp_win){
            std::cout << "Computer win!" << std::endl;
            break;
        }
    }
    if (All_Fields_Filled(Array) & !cmp_win & !gmr_win){
        std::cout << "Draw!" << std::endl;
    }
    std::cout << "Thanks for the game!" << std::endl;
}

int main(){
    while (true){
        Game(array);
        std::cout << "Do you want to play more?" << std::endl;
        std::cout << "If answer is 'Yes', please write '1'; else write '0'." << std::endl;
        int check;
        std::cin >> check;
        if (check != 1){
            break;
        }
    }
    return 0;
}