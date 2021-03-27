#include <stdio.h>
#include <stdbool.h>

int board[7][7] = { 77, 77, 77, 77, 77, 77, 77,
                    77, 77, 77, 99, 77, 77, 77,
                    77, 77, 77, 99, 77, 77, 77,
                    77, 77, 99, 99, 99, 99, 77,
                    77, 99, 99, 99, 77, 99, 77,
                    77, 77, 77, 77, 77, 99, 77,
                    77, 77, 77, 77, 77, 77, 77 };
// 77 - ¯®«¥ á¢®¡®¤­®
// 99 - ¯à¨£à ¤ 
void print_board ()
{
    printf("\n");
    for (int i = 0; i <= 6; i++)
    {
        printf("|");
        for (int j = 0; j <= 6; j++)
            printf(" %d", board[i][j]);
        printf(" |\n");
    }
    printf("\n");
}
// ­ ­¨á¥­¨¥ ­ ç «ì­®© â®çª¨ ¨ æ¥«¨ ­  ¤®áªã
void board_initiate(int start_r, int start_c, int goal_r, int goal_c)
{
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            if (i == start_r && j == start_c)
                board[i][j] = 10;
            if (i == goal_r && j == goal_c)
                board[i][j] = 88;
        }
    }
}
// ¯à®¢¥àª  ­  á¢®¡®¤ã ïç¥©ª¨
bool matrix_border_check(int i, int j)
{
    bool res = false;
    if (board[i][j] == 77 || board[i][j] == 88)
        res = true;
    if (i < 0 || i > 6 || j < 0 || j > 6 || board[i][j] == 99)
        res = false;
    return res;
}
// ¯à®¢¥àª  á¢®¡ ¤­  «¨ ª«¥âª  ¯à¨ ®¡à â­®¬ å®¤¥
bool matrix_step_back_check(int i, int j)
{
    bool res = false;
    if (9 < board[i][j] && board[i][j] < 39)
        res = true;
    if (i < 0 || i > 6 || j < 0 || j > 6 || board[i][j] == 99)
        res = false;
    return res;
}
// ¯à®¢¥àª  ­  ­ «¨ç¨¥ ­¥ § ­ïâëå ª«¥â®ç¥ª ¢ ¯®«¥
bool board_free()
{
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            if (board[i][j] == 77 || board[i][j] == 88)
                return true;
        }
    }
    return false;
}
// à ááâ ­®¢ª  á®á¥¤¨©
void put_neighbors (int numb)
{
    for (int i = 0; i <= 6; i++)
    {
        for (int j = 0; j <= 6; j++)
        {
            if (board[i][j] == numb)
            {
                if (matrix_border_check(i-1,j-1))
                    board[i-1][j-1] = numb+1;
                if (matrix_border_check(i-1, j))
                    board[i-1][j] = numb+1;
                if (matrix_border_check(i-1,j+1))
                    board[i-1][j+1] = numb+1;

                if (matrix_border_check(i,j-1))
                    board[i][j-1] = numb+1;
                if (matrix_border_check(i,j+1))
                    board[i][j+1] = numb+1;

                if (matrix_border_check(i+1,j-1))
                    board[i+1][j-1] = numb+1;
                if (matrix_border_check(i+1,j))
                    board[i+1][j] = numb+1;
                if (matrix_border_check(i+1,j+1))
                    board[i+1][j+1] = numb+1;
            }
        }
    }
}

int step_back(int i, int j, int numb)
{
    int n = 44; // 44 - ¯ãâì ®â æ¥«¨ ¤® ­ ç « 
    while (numb != 10)
    {
        if (board[i-1][j-1] == numb-1 && matrix_step_back_check(i-1,j-1))
        {
            numb--;
            i--;
            j--;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
        if (board[i-1][j] == numb-1 && matrix_step_back_check(i-1,j))
        {
            numb--;
            i--;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
        if (board[i-1][j+1] == numb-1 && matrix_step_back_check(i-1,j+1))
        {
            numb--;
            i--;
            j++;
            if (numb == 10) return 0;
            board[i][j] = n;
        }

        if (board[i][j-1] == numb-1 && matrix_step_back_check(i,j-1))
        {
            numb--;
            j--;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
        if (board[i][j+1] == numb-1 && matrix_step_back_check(i,j+1))
        {
            numb--;
            j++;
            if (numb == 10) return 0;
            board[i][j] = n;
        }

        if (board[i+1][j-1] == numb-1 && matrix_step_back_check(i+1,j-1))
        {
            numb--;
            i++;
            j--;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
        if (board[i+1][j] == numb-1 && matrix_step_back_check(i+1,j))
        {
            numb--;
            i++;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
        if (board[i+1][j+1] == numb-1 && matrix_step_back_check(i+1,j+1))
        {
            numb--;
            i++;
            j++;
            if (numb == 10) return 0;
            board[i][j] = n;
        }
    }
    return 0;
}
// ¢ë¢®¤ ­ £«ï¤­®£® ¯®«ï á å®¤®¬ ®â ­ ç «  ¤® æ¥«¨
void rebuild_pole (int goal_row, int goal_col)
{
    char char_board[7][7] = {' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                             ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char_board[goal_row][goal_col] = 'G';
    for (int i = 0; i <= 6; i++)
    {
        printf("|");
        for (int j = 0; j <= 6; j++)
        {
            if (board[i][j] == 99)
                char_board[i][j] = 'X';
            if (board[i][j] == 10)
                char_board[i][j] = 'S';
            if (board[i][j] == 44)
                char_board[i][j] = '*';
            printf(" %c ", char_board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}


int main()
{
    int start_row = 3-1; // § ¤ ­¨¥ â®çª¨ áâ àâ 
    int start_col = 2-1;
    int goal_row = 5-1;  // § ¤ ­¨¥ â®çª¨ æ¥«¨
    int goal_col = 5-1;
    board_initiate(start_row, start_col, goal_row, goal_col);
    print_board();
    int initial_numb = 10;
    while (board_free()) // ¯à®æ¥¤ãà  § ¯®«­¥­¨ï ¯®«ï
    {
        put_neighbors(initial_numb);
        initial_numb++;
    }
    print_board();
    int goal_number = board[goal_row][goal_col]; // ã§­ ¥¬ ª ª®¥ ª®«¨çáâ¢® å®¤®¢ ­ã¦­® ¤® æ¥«¨

    step_back(goal_row, goal_col, goal_number); // ®¡à â­ë© å®¤ ®â æ¥«¨ ª ­ ç «ã
    print_board();
    rebuild_pole(goal_row, goal_col);
    printf("X - locked area\nS - Start\nG - Goal\n* - Shortest way");
    return 0;
}
