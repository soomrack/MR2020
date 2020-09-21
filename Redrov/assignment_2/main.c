#include "main.h"

int main() {

    char name[80];
    int age = 0;
    char choice;
    int score = 0;

    printf(NAME_QUESTION);
    scanf("%s", name);
    printf(AGE_QUESTION);
    scanf("%d", &age);
    printf(START_QUESTION, name, age);
    scanf(" %c", &choice);
    if (choice == 'y'){
        printf(READY_QUESTION);
        scanf(" %c", &choice);

        printf(FIRST_QUESTION);
        scanf(" %c", &choice);
        if (choice == 'y'){
            score ++;}

        printf(SECOND_QUESTION);
        scanf(" %c", &choice);
        if (choice == 'y'){
            score ++;}

        printf(THIRD_QUESTION);
        scanf(" %c", &choice);
        if (choice == 'n'){
            score ++;}

        printf(FOURTH_QUESTION);
        scanf(" %c", &choice);
        if (choice == 'n'){
            score ++;}

        printf(FIFTH_QUESTION);
        scanf(" %c", &choice);
        if (choice == 'y'){score ++;}

        switch (score) {
            case 5:
                printf(FIVE_OF_FIVE);
                break;
            case 4:
                printf(FOUR_OF_FIVE);
                break;
            case 3:
                printf(THREE_OF_FIVE);
                break;

            case 2:
                printf(TWO_OF_FIVE);
                break;

            case 1:
                printf(ONE_OF_FIVE);
                break;

            case 0:
                printf(ZERO_OF_FIVE);
                break;
        }
    }
    else{
        printf("Okay, see ya!");
    }
    return 0;
}
