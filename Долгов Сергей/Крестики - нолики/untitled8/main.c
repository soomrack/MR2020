
#include <stdio.h>

int main() {
    int x,y;
    char arr[] = "e" "e" "e" "e" "e" "e" "e" "e" "e";
    printf("x axis goes from left to right  and the y axis goes from top to bottom\n");
    int switcher = 0;
    int victory = 0;
    while (victory == 0) {
        printf("x");
        scanf("%d", &x);
        printf("y");
        scanf("%d", &y);
        int pos = x - 1 + (y - 1) * 3;

        int errorswitcher = 0;
        if (arr[pos] == '0') { errorswitcher = 1; };
        if (x < 1) { errorswitcher = 1; }
        if (y < 1) { errorswitcher = 1; }
        if (y > 3) { errorswitcher = 1; }
        if (arr[pos] == 'X') { errorswitcher = 1; };
        if (x > 3 == '0') { errorswitcher = 1; }
        if ((switcher == 0) & (errorswitcher == 0)) {
            switcher = 1;
            arr[pos] = '0';
            printf(" \n%d switcher 1 \n", switcher);
        }
        else {
            if ((switcher == 1) & (errorswitcher == 0)) {
                switcher = 0;
                arr[pos] = 'X';
                printf(" \n%d switcher 2 \n", switcher);
            }
        }

        printf("%c %c %c \n", arr[0], arr[1], arr[2]);
        printf("%c %c %c \n", arr[3], arr[4], arr[5]);
        printf("%c %c %c \n", arr[6], arr[7], arr[8]);
        if ((arr[0]==arr[3]) & (arr[3]==arr[6]) &('0'==arr[3])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[1]==arr[4]) & (arr[4]==arr[7]) &('0'==arr[4])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[2]==arr[5]) & (arr[5]==arr[8]) &('0'==arr[5])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[0]==arr[3]) & (arr[3]==arr[6]) &('X'==arr[3])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
        if ((arr[1]==arr[4]) & (arr[4]==arr[7]) &('X'==arr[4])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
        if ((arr[2]==arr[5]) & (arr[5]==arr[8]) &('X'==arr[5])){victory = 1;printf("\n===X WON !===\n  ==     ==");}

        if ((arr[0]==arr[1]) & (arr[1]==arr[1]) &('0'==arr[0])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[3]==arr[4]) & (arr[4]==arr[5]) &('0'==arr[3])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[6]==arr[7]) & (arr[7]==arr[8]) &('0'==arr[6])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[0]==arr[1]) & (arr[1]==arr[1]) &('X'==arr[0])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
        if ((arr[3]==arr[4]) & (arr[4]==arr[5]) &('X'==arr[3])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
        if ((arr[6]==arr[7]) & (arr[7]==arr[8]) &('X'==arr[6])){victory = 1;printf("\n===X WON !===\n  ==     ==");}

        if ((arr[0]==arr[4]) & (arr[4]==arr[8]) &('0'==arr[0])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[2]==arr[4]) & (arr[4]==arr[6]) &('0'==arr[2])){victory = 1;printf("\n===0 WON !===\n  ==     ==");}
        if ((arr[0]==arr[4]) & (arr[4]==arr[8]) &('X'==arr[0])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
        if ((arr[2]==arr[4]) & (arr[4]==arr[6]) &('X'==arr[2])){victory = 1;printf("\n===X WON !===\n  ==     ==");}
    }
    return 0;
}

