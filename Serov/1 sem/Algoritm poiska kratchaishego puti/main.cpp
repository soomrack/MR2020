#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void sozdpole (int length, int height, int array [][6]){ //создаем поле из рандомных чисел
    srand(time(NULL));
    int i = 0;
    int j = 0;
    while (i<length){
        while (j<height){
            array[i][j]= rand() % 2;
            j++;
        }
        j = 0;
        i++;
    }
}

void vivodpolya(int length, int height, int array [][6]){ // вывод поля игроку в доступном варианте
    int i=0;
    int j=0;
    while (i<6){
        printf("|");
        while (j<6) {
            if (array[i][j] == 1)
                printf("+");
            if (array[i][j] == 0)
                printf ("-");
            printf("|");
            j++;
        }
        printf("\n");
        i++;
        j=0;
    }
}

void preobrpolya(int array [][6]){  //меняем поле для удобных нам чисел
    int i = 0;
    int j = 0;
    while (i<6){
        while (j<6){
            if (array[i][j] == 0)
                array[i][j] = -1000;
            if (array [i][j] == 1)
                array[i][j] = 1000;
            j++;
        }
        j = 0;
        i++;
    }
}

void startovoesoobshenie(){  //что мы напишем игроку при старте программы
    printf("Dobro pojalovat' v labirint!\n");
    printf("+ eto kletki po kotorym mojno hodit\n");
    printf("- eto kletki po kotorym hodit' nelzya\n");
    printf("Viberite, otkuda hotite nachat put\n");
}
void viborna4ala (int array[][6]){  //предлагаем игроку выбрать начальную точку
    int stolbets = 0;
    int stro4ka = 0;
    printf("Vvedite stolbets\n");
    scanf("%d", &stolbets );
    printf("Vvedite stro4ku\n");
    scanf("%d", &stro4ka );
    array [stro4ka-1][stolbets-1] = 0;
}
int konetsstolb (){  //предлагаем игроку выбрать столбец конечной точки
    int stolbets = 1;
    printf("Vvedite stolbets\n");
    scanf("%d", &stolbets );
    return stolbets;
}

int konetsstro4ka (){ //предлагаем игроку выбрать строчку конечной точки
    int stro4ka = 1;
    printf("Vvedite, gde budet konets puteshestviya\n");
    printf("Vvedite stro4ku\n");
    scanf("%d", &stro4ka );
    return stro4ka;
}
void findthelowestelement (int array [][6], int suparray[]){ //находим дорогу с наименьшими шагами
    suparray [0]=0;
    suparray [1]=0;
    suparray [2] = -1;
    int i=0;
    int j=0;
    int l = -1;
    int k = 999;
    while (i<6){
        while (j<6) {
            if ((array[i][j]<k) && (array[i][j]>=0)){
                k = array [i][j];
                suparray[0]=i;
                suparray[1]=j;
                l++;
                suparray[2]=l;
            }
            j++;
        }
        i++;
        j=0;
    }

}

void changearray (int array [][6], int ai1, int ai2){  //собственно совершаем шаги
    int i=ai1-1;
    int znach = array[ai1][ai2]+1;
    if (i<0)
        i = 0;
    int j = ai2-1;
    if (j<0)
        j = 0;
    int k = ai1+1;
    if (k>5)
        k = 5;
    int l = ai2+1;
    if (l>5)
        l = 5;
    while (i<=k){
        while (j<=l){
            if (array[i][j]>znach)
                array [i][j] = znach;
            j++;
        }
        j = 0;
        i++;
    }
    array [ai1][ai2] = -(znach-1);
    if (array[ai1][ai2]==0)
        array[ai1][ai2]=-3000;
}

void vivodpolya2(int array [][6]){  //выводим итоговый результат игроку
    int i = 0;
    int j = 0;
    while (i<6){
        printf("|");
        while (j<6){
            if ((array[i][j] > (-1000)) && (array[i][j] < 1000)){
                array[i][j] = abs(array[i][j]);
                printf ("%d",array[i][j]);
            }
            if (array[i][j] == (-1000))
                printf ("-");
            if (array[i][j] == 1000)
                printf ("+");
            if (array[i][j] == -3000)
                printf ("0");
            printf("|");
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}
void allfunctions (){
    int array [6][6];
    int suparray [3];
    sozdpole(6,6,array);
    vivodpolya(6,6,array);
    preobrpolya(array);
    startovoesoobshenie();
    viborna4ala(array);
    int str = 0;
    str = konetsstro4ka() - 1;
    int stl = 0;
    stl = konetsstolb() - 1;
    array [str][stl] = 1001;
    int ai1 = 0;
    int ai2 = 0;
    while (array[str][stl] == 1001){
        findthelowestelement(array, suparray);
        if (suparray[2] == -1){
            printf("Net puti, poprobuite zaddat' drugie koordinati");
            exit(0);
        }
        ai1 = suparray[0];
        ai2 = suparray[1];
        changearray(array, ai1,ai2);
    }
    vivodpolya2(array);
}
int main() {
    allfunctions();
}
