//
// Created by Alex on 29.09.2020.
//
#include <iostream>

#ifndef XO_XO_H
#define XO_XO_H
#define UserMark '0'
#define ComputerMark 'X'
#define EmptyMark '.'

#define RANDOM

using namespace std;

    const uint8_t n = 3;
    uint8_t Field[n + 1][n + 1];
    bool isUserWin(void);
    bool IsSomeoneWin(uint8_t Mark);
    void IsSomeoneWin(void);
    void FieldInit(void);
    void ShowField(void);
    void ComputersMove(void);
    void UsersMove(void);


#endif //XO_XO_H
