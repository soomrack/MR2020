#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[3][3];


void print_field()
{
    int i, j;
    printf("\n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("|");
            if (a[i][j] == 1) printf("X");
            else if (a[i][j] == 2) printf("0");
            else printf(" ");
        }
        printf("|\n");
    }
}

int test_for_win(int x,int y)
{
    if((a[y][0] == a[y][1]) && (a[y][1] == a[y][2]) && (a[y][0] != 0)) return 1;
    if((a[0][x] == a[1][x]) && (a[1][x] == a[2][x]) && (a[0][x] != 0)) return 1;
    if(((a[0][0] == a[1][1]) && (a[1][1] == a[2][2]) && (a[0][0] != 0) || ((a[0][2] == a[1][1]) && (a[1][1] == a[2][0]) && a[0][2] != 0))) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    print_field();
    int i, j, val, c;
    for(c =0;c<9;c++)
    {
        if (c % 2==0) {
            A: printf("Coordinates: ");
            scanf("%d %d", &i, &j);
            if (a[i-1][j-1] != 0) {printf("This field is taken. Choose a free one\n");
            goto A;
            }
        }
        else{
            srand(time(NULL));
            B:i=rand()%3+1;
            j=rand()%3+1;
            if (a[i-1][j-1] != 0)
                goto B;
        }

        if(c % 2 == 0) a[i-1][j-1] = 2;
        else a[i-1][j-1] = 1;
        print_field();

        if (test_for_win(j-1, i-1))
        {
            if (c%2==0)
                printf("You won ^_^");
            else
                printf("Computer won -_-");
            exit(0);
        }

        }
   printf("Draw");
    return 0;
}