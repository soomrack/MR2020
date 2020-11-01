#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>

using namespace std;

const int rows = 4;
const int cols = 4;

// Задаваемое поле
int map[rows][cols] = {{0, 0, 1, 0},
                       {0, 1, 0, 1},
                       {0, 0, 1, 0},
                       {0, 0, 0, 0}};

// Матрица содержащее количество ходов до каждого элемента поля
int map_num[rows][cols];

// Очередь
vector<pair<int,int>>turn;

int group = 0; // За сколько ходов можно добрать в эту точку(группа)
int amount_same = 1; // Количество точек, в которое можно прийти за N ходов
int current_num = 1; // Оставшееся количество точек из списка amount_same

// Заполнить матрицу -2
void map_num_fill (void)
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            map_num[x][y] = -2;
        }
    }
}

// Нахождение возможных путей из текущей точки
int find_neighbour(int xs, int ys)
{
    map[xs][ys] = 1; // Заполнение этой точки единицей, чтобы не находить ее как возможный путь в дальнейшем
    int amount_roots = 0; // Количество путей из этой точки
    for (int y = ys - 1; y <= ys + 1; y++)
    {
        for (int x = xs - 1; x <= xs + 1; x++)
        {
            if ((map[x][y] == 0) && ((x != xs) || (y != ys)) && (x >= 0) && (x < cols) && (y >= 0) && (y < rows))
            {
                map[x][y] = 1; // Заполнение путей из точки единицами, чтобы не находить их как возможный путь в дальнейшем
                turn.push_back(make_pair(x,y)); // Запись в конец очереди на проверку
                amount_roots++;
            }
        }
    }
    if (current_num == 0) // Если количество точек принадлежащей одной группе закончилось
    {
        current_num = amount_same; // Передаем количество точек следующей группы
        amount_same = 0; // Заунляем количество точек следующей следующей группы
        group++;
    }
    map_num[xs][ys] = group; // Отмечаем принадлежность группе, то есть в эту точку можно добратьза за group ходов
    current_num--; // Уменьшаем количество оставшихся точек в группе
    return amount_roots;
}

// Определение длины пути и заполенение матрицы количества ходов до точек
int doyouknowtheway(int xs, int ys, int xf, int yf)
{
    amount_same = find_neighbour(xs, ys); // Задаем количество путей из стартовой точки
    for (int i = 0; i < turn.size(); i++) // Пока очередь не кончится проверяем ее элементы на соответствие финишу
    {
        if ((turn[i].first == xf) && (turn[i].second == yf))
        {
            find_neighbour(turn[i].first, turn[i].second); // Нужно чтобы этой точке присвоился номер группы
            printf("The shortest path's length is %d\n", map_num[xf][yf]); // Выводим длину пути из карты количества ходов до точек
            return 0;
        }
        else
        {
            amount_same += find_neighbour(turn[i].first, turn[i].second); // Продолжаем заполнять очередь и копить количество эелементов одной группы
        }
    }
    printf("Finish is unreachable\n");
    exit(1);
    return 1;
}

// Вектор координов точек пути
vector<pair<int,int>>path;

void input_path (int xs, int ys, int path_length)
{
    printf("Path: \n");
    int end = path_length;
    path.push_back(make_pair(xs,ys)); // Начинаем заполнять вектор, но с конца

    for (int i = 0; i < end; i++)
    {
        xs = path[i].first; // Координаты точки отсчета
        ys = path[i].second; // Координаты точки отсчета
        for (int y = ys - 1; y <= ys + 1; y++)
        {
            for (int x = xs - 1; x <= xs + 1; x++)
            {
                // Проверяем является ли точка соседом и идем ли мы по пути обратно
                if ((map_num[x][y] == path_length - 1) && ((x != xs) || (y != ys)) && (x >= 0) && (x < cols) && (y >= 0) && (y < rows))
                {
                    path_length--;
                    path.push_back(make_pair(x,y));
                }
            }
        }
    }

    // Выводим путь в обратном порядке
    for (int i = end - 1; i >= 0; i--)
    {
        printf("cols = %d rows = %d\n", path[i].second + 1, path[i].first + 1);
    }
}

// Вывод карты в целом полезно, но не необходимо
void input_map (void)
{
    printf("Map:\n");
    for (int x = 0; x < rows; x++)
    {
        int k = 0;
        for (int y = 0; y < cols; y++)
        {
            printf("%d ", map_num[x][y]);
            k++;
            if (k == cols)
            printf("\n");
        }
    }
}

int main(void) {
    int xs, ys, xf, yf;
    xs = 0; // Старт
    ys = 3; // Старт
    xf = 3; // Финиш
    yf = 3; // Финиш
    map_num_fill();
    doyouknowtheway(xs, ys, xf, yf);
    input_path(xf, yf, map_num[xf][yf]);
    return 0;
}
