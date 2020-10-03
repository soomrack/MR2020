#include <stdio.h>
int input; //цифра, в которую пользователь ходит
int Npovorotov; //количество поворотов матрицы для приведения к стандартному виду
char gameboard [9]={'1','2','3','4','5','6','7','8','9'};
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
int vyvod(){
    printf("\n%c|%c|%c\n%c|%c|%c\n%c|%c|%c\n",
           gameboard [0],gameboard [1],gameboard [2],
           gameboard [3],gameboard [4],gameboard [5],
           gameboard [6],gameboard [7],gameboard [8]
            );
    return 0;
}
int vvod(){
    printf("Put in number from 1 to 9\n");
    scanf("%d",&input);
    gameboard[input-1]='o';
    return 0;
}
//Функция алгоритма при игре Юзера за нолик
int usernolik (){
    gameboard[4]='X';
    vyvod();
    printf("Put in number from 1 to 9\n");
    tryagain:
    scanf("%d",&input);
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
        printf("%s\n", "Put in correct answer pls)...");
        goto tryagain;
    }
    //Алгоритм при игре 0 не в углу0
    if (input%2==0 ){
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
            printf("Ty proigral)\n");
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
        printf("Ty proigral)\n");
            return 0;
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
            printf("Ty proigral)\n");
        }
        //Когда Нолик идет в 4 или 6
        else if (gameboard[3]=='o' || gameboard[5]=='o'){
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
            printf("Ty proigral)\n");
        }

        else if(gameboard[2]=='o' || gameboard[6]=='o'){
            //Нолик на 3
            if (gameboard[2]=='o'){
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
                    printf("Ty proigral)\n");
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
                        printf("Ty proigral)\n");
                    }
                    else {
                        gameboard[6]='X';
                        vyvod();
                        printf("Na etot raz tebe povezlo)\n");
                    }
                }
            }
            else {gameboard[3]='X';
                povorot9min();
                vyvod();
                vvod();
                vyvod();
                povorot9();
                if (gameboard[5]!='o'){
                    gameboard[5]='X';
                    povorot9min();
                    vyvod();
                    printf("Ty proigral)\n");
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
                        printf("Ty proigral)\n");
                    }
                    else {
                        gameboard[2]='X';
                        povorot9min();
                        vyvod();
                        printf("Na etot raz tebe povezlo)\n");
                    }
                }
            }
        }
}
}
int main() {
usernolik();
    return 0;
}
