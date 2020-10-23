#include <stdio.h>
#include <stdlib.h>
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h> //Библиотека для работы с сетью
#include <iostream>  //Библиотека для работы с вводом-выводом
SOCKET Connection;
int input; //цифра, в которую пользователь ходит
int Npovorotov; //количество поворотов матрицы для приведения к стандартному виду
char gameboard [32]={'1','2','3','4','5','6','7','8','9',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',};
char fakeboard [9]; //Побочная матрица
//Поворот матрицы на 90 градусов по часовой
int povorot90min () {
    fakeboard[0] = gameboard[6];
    fakeboard[1] = gameboard[3];
    fakeboard[2] = gameboard[0];
    fakeboard[3] = gameboard[7];
    fakeboard[4] = gameboard[4];
    fakeboard[5] = gameboard[1];
    fakeboard[6] = gameboard[8];
    fakeboard[7] = gameboard[5];
    fakeboard[8] = gameboard[2];
    for (int i = 0; i <= 8; i++) {
        gameboard[i] = fakeboard[i];
    }
    return 0;
}
//Поворот матрицы на 90 градусов против часовой
int povorot90 () {
    fakeboard[0] = gameboard[2];
    fakeboard[1] = gameboard[5];
    fakeboard[2] = gameboard[8];
    fakeboard[3] = gameboard[1];
    fakeboard[4] = gameboard[4];
    fakeboard[5] = gameboard[7];
    fakeboard[6] = gameboard[0];
    fakeboard[7] = gameboard[3];
    fakeboard[8] = gameboard[6];

    for (int i = 0; i <= 8; i++) {
        gameboard[i] = fakeboard[i];
    }

    return 0;
}
//Повороты по циклам
int povorot9 (){
    for (int i=0; i<Npovorotov; i++){
        povorot90();
    }
    return 0;
}
int povorot9min (){
    for (int i=0; i<Npovorotov; i++){
        povorot90min();
    }
    return 0;
}
//В данном случае - это отправка геймборда в ответ
int vyvod(){
    send(Connection,gameboard, sizeof(gameboard),0);
    Sleep (100);
    return 0;
}
//В данном случае нам надо прочитать данные из сокета
int vvod(){
    char msg1 [256];
    recv(Connection, msg1, sizeof(msg1),0);
    input = atoi(msg1); //Перевод из строки в инт
    gameboard[input-1]='o';
    return 0;
}
int ZeroNotInCorner(){
    povorot9();
    gameboard [1] = 'o';
    povorot9min();
    vyvod();
    //Наш ответ
    povorot9();
    gameboard [6] = 'X';
    povorot9min();
    vyvod();
    //2й ввод пользователя
    vvod();
    povorot9();
    if (gameboard[2]!='o'){
        gameboard[2] ='X';
        send(Connection,"You lose)", 9,0);
        system ("pause");
    }
    else {
        gameboard[0] ='X';
    }
    povorot9min();
    vyvod();
    printf("Put in number from 1 to 9\n");
    scanf("%d",&input);
    gameboard[input-1]='o';
    vyvod();
    povorot9();
    if (gameboard[3]=='o'){
        gameboard[8]='X';
    }
    else {
        gameboard[3]='X';
    }
    povorot9min();
    vyvod();
    send(Connection,"You lose)", 9,0);
    system ("pause");
    return 0;
}
int Zero2or8(){
    gameboard [2] = 'X';
    povorot9min();
    vyvod();
    //ПОльзовательский ввод + реакция
    vvod();
    vyvod();
    povorot9();
    if (gameboard[5]=='o'){
        gameboard [6] = 'X';
        povorot9min();
    }
    else {
        povorot9();
        gameboard[5] = 'X';
        povorot9min();
    }
    vyvod();
    send(Connection,"You lose)", 9,0);
    system ("pause");
}
int Zero4or6(){
    povorot9();
    gameboard [6] = 'X';
    povorot9min();
    vyvod();
    //ПОльзовательский ввод + реакция
    vvod();
    vyvod();
    povorot9();
    if (gameboard[7]=='o'){
        gameboard [2] = 'X';
        povorot9min();
    }
    else {
        gameboard[7] = 'X';
        povorot9min();
    }
    vyvod();
    send(Connection,"You lose)", 9,0);
    system ("pause");
}
int Zero3(){
    gameboard[1]='X';
    povorot9min();
    vyvod();
    vvod();
    vyvod();
    povorot9();
    if (gameboard[7]!='o'){
        gameboard[7]='X';
        povorot9min();
        vyvod();
        send(Connection,"You lose)", 9,0);
        system ("pause");
    }
    else {
        gameboard[5]='X';
        povorot9min();
        vyvod();
        vvod();
        vyvod();
        povorot9();
        if (gameboard[3]!='o'){
            gameboard[3]='X';
            povorot9min();
            vyvod();
            send(Connection,"You lose)", 9,0);
            system ("pause");
        }
        else {
            gameboard[6]='X';
            vyvod();
            send(Connection,"Lucky you)", 9,0);
            system ("pause");
        }
    }
}
int Zero7(){
    gameboard[3]='X';
    povorot9min();
    vyvod();
    vvod();
    vyvod();
    povorot9();
    if (gameboard[5]!='o'){
        gameboard[5]='X';
        povorot9min();
        vyvod();
        send(Connection,"You lose)", 9,0);
        system ("pause");
    }
    else {
        gameboard[1]='X';
        povorot9min();
        vyvod();
        vvod();
        vyvod();
        povorot9();
        if (gameboard[7]!='o'){
            gameboard[7]='X';
            povorot9min();
            vyvod();
            send(Connection,"You lose)", 9,0);
            system ("pause");
        }
        else {
            gameboard[2]='X';
            povorot9min();
            vyvod();
            send(Connection,"Lucky you)",9 ,0);
            system ("pause");
        }
    }
}
//Функция алгоритма при игре Юзера за нолик
int usernolik (){
    char msg1[256];
    gameboard[4]='X';
    vyvod();
    send(Connection,"Print number from 1 to 9", 24,0);
    recv(Connection, msg1, sizeof(msg1),0);
    input = atoi(msg1);
//Определение количества поворотов
    if (input==2 || input==1){
        Npovorotov = 0;
    }
    else if (input==6 || input==3 ){
        Npovorotov = 1;
    }
    else if (input==8 || input==9 ){
        Npovorotov = 2;
    }
    else if (input==4 || input==7 ){
        Npovorotov = 3;
    }
    else {
        send(Connection,"Put in correct answer pls)...", 30,0);
    }
    //Алгоритм при игре 0 не в углу0
    if (input%2==0 ){
       ZeroNotInCorner();
    }
        //Алгоритм при 0 в угол
    else {
        povorot9();
        gameboard [0] = 'o';
        povorot9min();
        vyvod();
        //Наш ответ
        povorot9();
        gameboard [8] = 'X';
        povorot9min();
        vyvod();
        vvod();
        //Когда Нолик идет в 2 или 8
        povorot9();
        if (gameboard[1]=='o' || gameboard[7]=='o'){
            Zero2or8();
        }
            //Когда Нолик идет в 4 или 6
        else if (gameboard[3]=='o' || gameboard[5]=='o'){
            Zero4or6();
        }

        else if(gameboard[2]=='o' || gameboard[6]=='o'){
            //Нолик на 3
            if (gameboard[2]=='o'){
                Zero3();
            }
            //Нолик на 7
            else {
                Zero7();
            }
        }
    }
    return 0;
}
int main() {
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1); //Запрашиваемая версия библиотеки
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }; //Функция загрузки библиотеки + проверка на ошибку

    SOCKADDR_IN addr; //Структура для хранения интернет адреса
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP адрес
    addr.sin_port = htons(1111); //Порт
    addr.sin_family = AF_INET; //Семейство протоколов

    Connection = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0){
        std::cout << "Error: failed connection to server.\n" << std::endl;
        return 1;
    };
    std::cout << "Connected!";
    usernolik();
    return 0;
}
