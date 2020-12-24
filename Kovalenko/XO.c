#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

 char pole[] = ("123456789");
 char board(){
     printf(
     " %c | %c | %c \n"
     "___|___|___\n"
     " %c | %c | %c \n"
     "___|___|___\n"
     " %c | %c | %c \n", pole [0], pole [1], pole [2], pole [3], pole [4], pole [5], pole [6], pole [7], pole [8]);
 }

char start(){
    printf( "This is board. If you want to make move, you need to choose number.\n"
            "You play for O, and you move first\n"
            " %c | %c | %c \n"
            "___|___|___\n"
            " %c | %c | %c \n"
            "___|___|___\n"
            " %c | %c | %c \n", pole [0], pole [1], pole [2], pole [3], pole [4], pole [5], pole [6], pole [7], pole [8]);

}
int read() {
    int number;
    printf("Select the cell number\n");
    scanf("%d", &number);
    if ((pole[number] == 'X') || (pole[number] == 'O')){
        printf("Cell is buse, you lose one move\n");
    }
    return number;
}

int you_win(){
    char igrok = 'O';
    if (
            (pole[0] == igrok && pole[1] == igrok && pole[2] == igrok) ||
            (pole[3] == igrok && pole[4] == igrok && pole[5] == igrok) ||
            (pole[6] == igrok && pole[7] == igrok && pole[8] == igrok) ||
            (pole[0] == igrok && pole[3] == igrok && pole[6] == igrok) ||
            (pole[1] == igrok && pole[4] == igrok && pole[7] == igrok) ||
            (pole[2] == igrok && pole[5] == igrok && pole[8] == igrok) ||
            (pole[0] == igrok && pole[4] == igrok && pole[8] == igrok) ||
            (pole[2] == igrok && pole[4] == igrok && pole[6] == igrok)
            )
        return false;
    else
        return true;
}
int comp_win(){
    char igrok = 'X';
    if (
            (pole[0] == igrok && pole[1] == igrok && pole[2] == igrok) ||
            (pole[3] == igrok && pole[4] == igrok && pole[5] == igrok) ||
            (pole[6] == igrok && pole[7] == igrok && pole[8] == igrok) ||
            (pole[0] == igrok && pole[3] == igrok && pole[6] == igrok) ||
            (pole[1] == igrok && pole[4] == igrok && pole[7] == igrok) ||
            (pole[2] == igrok && pole[5] == igrok && pole[8] == igrok) ||
            (pole[0] == igrok && pole[4] == igrok && pole[8] == igrok) ||
            (pole[2] == igrok && pole[4] == igrok && pole[6] == igrok)
            )
        return false;
    else
        return true;
}


void write(int a){
    if (a == 1) pole[0] = 'O';
    if (a == 2) pole[1] = 'O';
    if (a == 3) pole[2] = 'O';
    if (a == 4) pole[3] = 'O';
    if (a == 5) pole[4] = 'O';
    if (a == 6) pole[5] = 'O';
    if (a == 7) pole[6] = 'O';
    if (a == 8) pole[7] = 'O';
    if (a == 9) pole[8] = 'O';
}

int put(){
    srand(time(NULL));
    int comp = rand() % 8;
    for (int i = 0; i <= 8; i++) {
        if ((pole[i] != 'X') && (pole[i] != 'O')){
            if (i == comp){
                pole[i] = 'X';
            }
        }
    }
    printf("%d\n", comp);
}

int game(){
    do {
        int cell = read();
        write(cell);
        printf("Your choose\n");
        board();
        put();
        printf("Computer choose\n");
        board();
    }
    while (you_win() && comp_win());
    if (you_win() == false){
        printf("You win\n");
    }
    else {
        printf("Computer win");
    }
    return 0;
}

int main() {
  start();
  game();
  return 0;
}
