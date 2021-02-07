#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int  a[3][3];
int w=0;
int sozdpole(){  //создаем поле
int i=0;
int j=0;
while (i<3){
    while (j<3){
    a[i][j]=1;
    j++;
    }
i++;
    j=0;
}
}
void korrpole(int stolb, int str){ //изменение поля для игрока
    int i=0;
    int j=0;
    while (i<3){
        if (i==str){
            while (j<3){
                if (j==stolb) {
                    a[i][j] = 2;
                              }
                j++;
            }
        }
    i++;
    j=0;
    }
}
void korrpole2(int stolb, int str){ //изменение поля для компьютера
    srand(time(NULL));
    A: stolb = rand() %3+1;
    stolb=stolb-1;
    str=rand() %3+1;
    str=str-1;
    int i=0;
    int j=0;
    while (i<3){
        if (i==str){
            while (j<3){
                if (j==stolb) {
                    if (a[i][j]==2 || a[i][j]==0)
                        goto A;
                    else
                    a[i][j] = 0;
                }
                j++;
            }
        }
        i++;
        j=0;
    }
}
void vivodpolya(){ //вывод поля игроку
int i=0;
int j=0;
while (i<3){
    printf("|");
    while (j<3) {
        if (a[i][j] == 1)
            printf(" ");
        if (a[i][j] == 2)
            printf("X");
        if (a[i][j] == 0)
            printf("O");
    printf("|");
        j++;
    }
    printf("\n");
    i++;
    j=0;
        }
}
void win (){ //проверка победы игрока
    if ((a[0][0]==2) && (a[0][1]==2) && (a[0][2]==2))
        w=1;
    if ((a[1][0]==2) && (a[1][1]==2) && (a[1][2]==2))
        w=1;
    if ((a[2][0]==2) && (a[2][1]==2) && (a[2][2]==2))
        w=1;
    if ((a[0][0]==2) && (a[1][0]==2) && (a[2][0]==2))
        w=1;
    if ((a[0][1]==2) && (a[1][1]==2) && (a[2][1]==2))
        w=1;
    if ((a[0][2]==2) && (a[1][2]==2) && (a[2][2]==2))
        w=1;
    if ((a[0][0]==2) && (a[1][1]==2) && (a[2][2]==2))
        w=1;
    if ((a[2][0]==2) && (a[1][1]==2) && (a[0][2]==2))
        w=1;
}
void lose(){ //проверка победы компьютера
    if ((a[0][0]==0) && (a[0][1]==0) && (a[0][2]==0))
        w=1;
    if ((a[1][0]==0) && (a[1][1]==0) && (a[1][2]==0))
        w=1;
    if ((a[2][0]==0) && (a[2][1]==0) && (a[2][2]==0))
        w=1;
    if ((a[0][0]==0) && (a[1][0]==0) && (a[2][0]==0))
        w=1;
    if ((a[0][1]==0) && (a[1][1]==0) && (a[2][1]==0))
        w=1;
    if ((a[0][2]==0) && (a[1][2]==0) && (a[2][2]==0))
        w=1;
    if ((a[0][0]==0) && (a[1][1]==0) && (a[2][2]==0))
        w=1;
    if ((a[2][0]==0) && (a[1][1]==0) && (a[0][2]==0))
        w=1;
}
int main (){
    int stolb=0;
    int str=0;
    int k=0;
    sozdpole();
    vivodpolya();
    while (k<9){ //Собственно, сама игра
        if (k%2==0) {
            printf("Player 1 turn\n");
            B: printf("Vvedite stolbets\n");
            scanf("%d", &stolb);
            stolb = stolb - 1;
            printf("Vvedite stroku\n");
            scanf("%d", &str);
            str = str - 1;
                if ((a[str][stolb] !=1) | (stolb>2) | (str>2) | (stolb<0) | (str<0)){
                    printf("Vvedite korrektnye dannye\n");
                goto B;
            }

            korrpole(stolb, str);
            vivodpolya();
            win();
            if (w == 1) {
                printf("You won :)");
                exit(main);
            }
        }
        if (k%2==1){
            printf("Computer turn\n");
            korrpole2(stolb, str);
            vivodpolya();
        lose();
            if (w==1){
                printf("Computer won :(");
                exit(main);
        }
    }


        k++;
    }
printf("Pobedila drujba");
}

