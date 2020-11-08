#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
void create_field (int array [][8]){
    srand(time(NULL));
    for (int i = 0; i<8; i++){
        for (int j=0; j<8; j++){
            array[i][j]= rand() % 2;
        }
    }
}

void print_field (int array [][8])
{
    int i, j;
    printf("\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("  ");
            printf("%d",array[i][j]);
        }
        printf("  \n");
    }
}

void coordinates (int support_array []){
    int line=0;
    int column=0;
    printf("Coordinates: ");
    scanf("%d %d", &line, &column);
    support_array[0] = line-1;
    support_array[1] = column-1;
}

void change_field (int array [][8]){
    int i, j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if (array [i][j] == 0)
                array [i][j] = 50;
            if (array [i][j] == 1)
                array [i][j] = -50;
            if (array [i][j] == 2)
                array [i][j] = 0;
            if (array [i][j] == 3)
                array [i][j] = 100;
        }
    }
}

void print_field_2 (int array [][8])
{
    int i, j;
    printf("\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("  ");
            if (array [i][j] == -50)
                printf ("-");
            else
            if (array [i][j] == 50)
                printf ("+");
            else
                printf("%d",array[i][j]);
        }
        printf("  \n");
    }
}

void show_result (int array [][8]){
    int i, j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if (array [i][j] == -50)
                array [i][j] = 1;
            if (array [i][j] == 50)
                array [i][j] = 0;
            if (array [i][j] == 0)
                array [i][j] = 300;
        }
    }
}
void Deixtra (int array [][8], int i, int j, int step){
    int n=i-1;
    if (n<0)
        n = 0;
    int m = j-1;
    if (m<0)
        m = 0;
    int k = i+1;
    if (k>8)
        k = 8;
    int l = j+1;
    if (l>8)
        l = 8;
    while (n<=k){
        while (m<=l){
            if (array[n][m]>step)
                array [n][m] = step+1;
            m++;
        }
        m = 0;
        n++;
    }
}

void poisk_puti (int array [][8], int end_line, int end_column) {
    int step = 0;
    while (array[end_line][end_column] == 100) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (array[i][j] == step)
                    Deixtra(array, i, j, step);
            }
        }
        step ++;
    }
}
int main() {
    int support_array [3] = {0};
    int array [8][8] = {0};
    int start_column = 0;
    int start_line = 0;
    int end_column = 0;
    int end_line = 0;
    create_field(array);
    print_field(array);
    printf ("You can step on 0 and cant step on 1");
    printf("Enter the starting position \n");
    coordinates(support_array);
    start_line = support_array[0];
    start_column = support_array[1];
    printf("Enter the ending position \n");
    coordinates(support_array);
    end_line = support_array[0];
    end_column = support_array[1];
    array [start_line][start_column] = 2;
    array [end_line][end_column] = 3;
    change_field(array);
    print_field(array);
    poisk_puti(array,end_line,end_column);
    print_field_2(array);
}