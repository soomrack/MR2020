//
// Created by Alex on 29.09.2020.
//
//#include <iostream>
#include "XO.h"
#include "stdio.h"

extern volatile bool IsGameOver;
void FieldInit(void){
    for (uint8_t x = 1; x <= n; x++){
        for(uint8_t y = 1; y <= n; y++){
            Field[x][y] = EmptyMark;  // Маркировка всех клеток пустыми
        }
      /*Field[1][3] = ComputerMark;
        Field[2][2] = ComputerMark;
        Field[3][1] = UserMark;*/
    }
ShowField(); // Вывод поля
}

void ShowField(void) {
    for (uint8_t y = 0; y <= n; y++) {
        for (uint8_t x = 0; x <= n; x++) {
            if (y == 0) {
                if ( x == 0){
                    cout << "    ";
                    continue;
                }
                cout << "X" << (uint16_t) x << "  ";
            } else if (x == 0) {
                cout << "Y" << (uint16_t) y << " ";
            } else {
                cout << "[" << Field[x][y] << "] ";
            }
        }
        cout << endl;
    }
}

/*
bool IsUserWin(void){
    bool winFlag = false;
    bool xFlag = true;
    bool yFlag = true;
    bool xyFlag = true;

    for (uint8_t y = 1; y <= n; y++){
        if(!winFlag) {
            xFlag = true;
            for (uint8_t x = 1; x <= n; x++) {
                if (Field[x][y] == UserMark && xFlag) {
                    xFlag = true;
                } else xFlag = false;
            }
            if (xFlag) winFlag = true;
        }
    }

    for (uint8_t x = 1; x <= n; x++){
        if(!winFlag) {
            yFlag = true;
            for (uint8_t y = 1; y <= n; y++) {
                if (Field[x][y] == UserMark && yFlag) {
//                    yFlag = true;
                } else yFlag = false;
            }
            if (yFlag) winFlag = true;
        }
    }

    for (uint8_t xy = 1; xy <= n; xy++){
        if(!winFlag){
            xyFlag = true;
            if (Field[xy][xy] == UserMark && xyFlag){ }
            else xyFlag = false;
        }
    } if (xyFlag) winFlag = true;

    for (uint8_t xy = n; xy >= 1; xy--){
        if(!winFlag){
            xyFlag = true;
            if (Field[xy][n - xy + 1] == UserMark && xyFlag){ }
            else xyFlag = false;
        }
    } if (xyFlag) winFlag = true;


    return winFlag;
}
*/

void IsSomeoneWin(void){
    if (IsSomeoneWin(UserMark)) {
        cout << "User Win!";
        IsGameOver = true;
    }
    else if (IsSomeoneWin(ComputerMark)) {
        cout << "Computer Win!";
        IsGameOver = true;
    }

}

bool IsSomeoneWin(uint8_t Mark){
    bool winFlag = false;
    bool xFlag = true;
    bool yFlag = true;
    bool xyFlag = true;

    // Проверка по строкам
    for (uint8_t y = 1; y <= n; y++){
        if(!winFlag) {
            xFlag = true;
            for (uint8_t x = 1; x <= n; x++) {
                if (Field[x][y] == Mark && xFlag) {
                    xFlag = true;
                } else xFlag = false;
            }
            if (xFlag) winFlag = true;
        }
    }
    //Проверка по строкам
    for (uint8_t x = 1; x <= n; x++){
        if(!winFlag) {
            yFlag = true;
            for (uint8_t y = 1; y <= n; y++) {
                if (Field[x][y] == Mark && yFlag) {
//                    yFlag = true;
                } else yFlag = false;
            }
            if (yFlag) winFlag = true;
        }
    }
    // Проверка по диагонали слева направо, сверху вниз
    xyFlag = true;
    for (uint8_t xy = 1; xy <= n; xy++){
        if(!winFlag){
            if (Field[xy][xy] == Mark && xyFlag){ }
            else xyFlag = false;
        }
    } if (xyFlag) winFlag = true;
    // Проверка по диагонали, справо налево, сверху вниз
    xyFlag = true;
    for (uint8_t xy = n; xy >= 1; xy--){
        if(!winFlag){
            if (Field[xy][n - xy + 1] == Mark && xyFlag){ }
            else xyFlag = false;
        }
    } if (xyFlag) winFlag = true;
    // Возврат значения флага
    return winFlag;
}

void UsersMove(void) {
    uint16_t X;
    uint16_t Y;
    cout << "Choose X coordinate" << endl;
    cin >> X;
    cout << "Choose Y coordinate" << endl;
    cin >> Y;

    if (Field[X][Y] == EmptyMark){
        Field[X][Y] = UserMark;
        ShowField();
    }
    else {
        cout << "You must choose empty cell!" << endl;
        UsersMove();
    }

}

#ifdef RANDOM
#include "random"
#include "ctime"
void ComputersMove(void){
    srand(time(0));
    //uint8_t Temp_Array[n*n][2];
    uint8_t **ptrArray = new uint8_t* [n*n];

    for (uint8_t Counter = 0; Counter < n*n; Counter ++){
        ptrArray[Counter] = new uint8_t [2];
    }

    uint8_t Counter = 0;

    for (uint8_t x = 1; x <= n; x++){
        for (uint8_t y = 1; y <= n; y++){
            if (Field[x][y] == EmptyMark){
                ptrArray[Counter][0] = x;
                ptrArray[Counter][1] = y;
                Counter ++;
            }
        }
    }
//cout << endl << "Count = " << (uint16_t) Counter << endl;

//for (uint8_t i = 0; i < Counter; i++){
//    cout << "X = " << (uint16_t) ptrArray[i][0] << " Y = " << (uint16_t) ptrArray[i][1] << endl;
//}

uint8_t Coordinate =  rand() % Counter;

Field[ptrArray[Coordinate][0]][ptrArray[Coordinate][1]] = ComputerMark;
ShowField();

}

#endif