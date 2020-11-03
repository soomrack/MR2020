#include <iostream>
#include <clocale>
#include <windows.h>

using namespace std;

const unsigned int rows = 9;
const unsigned int pils = 9;
const unsigned int rows_start = 8;
const unsigned int pils_start = 2;
const unsigned int rows_finish = 4;
const unsigned int pils_finish = 8;
unsigned int map_traveler[rows][pils];
unsigned int newmap[rows][pils];
unsigned int counter_of_steps;

bool map[rows][pils] = {
    {1, 1, 1, 1, 1 , 1, 1, 1, 1},
    {1, 0, 0, 1, 0 , 0, 0, 0, 1},
    {1, 0, 0, 0, 0 , 1, 0, 0, 1},
    {1, 1, 1, 0, 0 , 0, 1, 0, 1},
    {1, 0, 0, 0, 0 , 0, 0, 0, 1},
    {1, 0, 0, 1, 0 , 1, 1, 1, 1},
    {1, 1, 0, 1, 0 , 0, 0, 0, 1},
    {1, 0, 0, 1, 0 , 1, 0, 0, 1},
    {1, 1, 1, 1, 1 , 1, 1, 1, 1},
};

void draw_map()
{
    cout << "Карта местности. \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < pils; j++)
        {
            if (i == rows_start - 1 && j == pils_start - 1)
            {
                cout << "Y";
                continue;
            };
            if (i == rows_finish - 1 && j == pils_finish - 1)
            {
                cout << "X";
                continue;
            };
            cout << map[i][j];
        };
        cout << "\n";
    };
    cout << "\n";
};

void draw_map_traveler(unsigned int voidmap[rows][pils])
{
    cout << "Разведанная карта. \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < pils ; j++)
        {
            if (i == rows_start - 1 && j == pils_start - 1)
            {
                cout << "Y";
                continue;
            };
           cout << voidmap[i][j];
        };
        cout << "\n";
    };
    cout << "\n";
};

void draw_new_map(unsigned int voidmap1[rows][pils])
{
    cout << "Разведанная карта. \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < pils; j++)
        {
            cout << voidmap1[i][j];
        };
        cout << "\n";
    };
    cout << "\n";
};

void steps()
{
    newmap[rows_start-1][pils_start-1] = 1;
    for (int k = 2; k < (rows * pils)-((rows-1)*(pils/2)); k++)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < pils; j++)
            {
                if (newmap[i][j] == k - 1)
                {
                    if (i < rows - 1 && map[i + 1][j] == 0 && newmap[i + 1][j] == 0)
                    {
                        newmap[i + 1][j] = k;
                    };
                    if (i > 0 && map[i - 1][j] == 0 && newmap[i - 1][j] == 0)
                    {
                        newmap[i - 1 ][j] = k;
                    };
                    if (j < pils - 1 && map[i][j + 1] == 0 && newmap[i][j + 1] == 0)
                    {
                        newmap[i][j + 1] = k;
                    };
                    if (j > 0 && map[i][j - 1] == 0 && newmap[i][j - 1] == 0)
                    {
                        newmap[i][j - 1] = k;
                    };
                    if (i < rows - 1 && j < pils - 1 && map[i + 1][j + 1] == 0 && newmap[i + 1][j + 1] == 0)
                    {
                        newmap[i + 1][j + 1] = k;
                    };
                    if (i > 0 && j < pils - 1 && map[i - 1][j + 1] == 0 && newmap[i - 1][j + 1] == 0)
                    {
                        newmap[i - 1][j + 1] = k;
                    };
                    if (i < rows - 1 && j > 0 && map[i + 1][j - 1] == 0 && newmap[i + 1][j - 1] == 0)
                    {
                        newmap[i + 1][j - 1] = k;
                    };
                    if (i > 0 && j > 0 && map[i - 1][j - 1] == 0 && newmap[i - 1][j - 1] == 0)
                    {
                        newmap[i - 1][j - 1] = k;
                    };
                };
            };
        };
        draw_new_map(newmap);
        if (newmap[rows_finish - 1][pils_finish - 1] != 0) 
        {
        counter_of_steps = k;
        cout << "Вам нужно сделать " << counter_of_steps-1 <<", чтобы найти клад. /n";
        break;
        }
    };
      
};

int main()
{
    setlocale(LC_CTYPE, "rus");
    draw_map();
    draw_map_traveler(map_traveler);
    steps();
};

