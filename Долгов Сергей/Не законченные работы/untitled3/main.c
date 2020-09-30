#include <stdio.h>
int main () {
    char arr[3][3];

    int i, j, c, x, y;
    int i1, j1;
   int ar[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    c = 0;
    printf("0---->   X\n");
    printf("|\n");
    printf("|\n");
    printf("v  Y\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("\ny\n");//filling cycle
            scanf("%d", &x);
            printf("\nx\n");
            scanf("%d", &y);;
            y = y;//reverse y
            x = x;

            if (ar[x][y]==0) {if ( c == 0){ arr[x][y] = "0";// 0 esly ne zanyato switch c
                    c = 1; ar[x][y]= 1;}}

             else if (ar[x][y]==0){if (c == 1 ){ arr[x][y] = "X";// x esly ne zanyato switch c
                    c = 0; ar[x][y]= 1;}}
             else if (ar[x][y] == 1){printf("Zanyato\n");}

            for (i1 = 0; i1 < 3; i1++) {
                { printf("\n"); }
                for (j1 = 0; j1 < 3; j1++) { printf("%c", arr[i1][j1]); }
            }
        }
    }


        return 0;

}