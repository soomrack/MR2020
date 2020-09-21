#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void clear(){
system("cls");
}
int main() {
    int ball=0;
    int numer=0;
    printf("Good day to you, fellow seeker of truth!\nLet's test your level of knowledge in gaming industry!\n");
    printf("Prepare yourself to answer 7 tricky questions.\n");
    A: printf("1) What is the name of the fictional city in Grand Theft Auto 5?\n");
        printf("1-Los-Santos \n2-Liberty-City \n3-Vice-City \n4-San-Paris\n");
        scanf("%d",&numer);
        if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
            goto A ;
        }
    if (numer==1){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    B: printf("2) Which of the following series was released as a computer game in 2012?\n");
    printf("1-The Walking dead \n2-Dexter \n3-How I met your mother \n4-Breaking bad\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
        goto B ;
    }
    if (numer==1){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
        else
        printf("Unfortunately, you are wrong :(\n");
    C: printf("3) Which of the following characters you can't recruit in the game called Chrono Cross?\n");
    printf("1-Funguy\n2-Dario \n3-Razzly \n4-Marcy\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
        goto C ;
    }
    if (numer==2){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    D: printf("4) Where does the action in the game Sleeping Dogs take place?\n");
    printf("1-Tokyo\n2-Seoul \n3-Shanghai \n4-Hong Kong\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
        goto D ;
    }
    if (numer==4){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    E: printf("5) Which of the following characters you can't have romantic relationship with in Mass Effect 2 if you're playing a male character?\n");
    printf("1-Jack\n2-Garrus \n3-Kayden \n4-Miranda\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
        goto E ;
    }
    if (numer==2){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    F: printf("6) How long did the longest Monopoly game take\n");
    printf("1-70 days\n2-96 days \n3-81 days \n4-50 days\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number?\n");
        goto F ;
    }
    if (numer==1){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    G: printf("7) What type of parasitic form of life threatens humanity in the game Halo?\n");
    printf("1-The fall\n2-The Flawed \n3-The Flood \n4-The Frantic\n");
    scanf("%d",&numer);
    if (numer<1 || numer>4){
        printf("Please, right down the correct number\n");
        goto G ;
    }
    if (numer==3){
        printf("Nice job, you are right!\n");
        ball=ball+1;
    }
    else
        printf("Unfortunately, you are wrong :(\n");
    printf("Your score is ");
    printf("%d",ball);
    printf("/7 points. Well done!");
}