#include <iostream>
#include <vector>

#define FIELD_SIZE 3

void path(int table[FIELD_SIZE][FIELD_SIZE], int startNode, int finish)
{
    int distance[FIELD_SIZE], index, u;
    int m=startNode+1;
    std::vector<int> thePath[FIELD_SIZE];

    bool visited[FIELD_SIZE];
    for (int i=0; i<FIELD_SIZE; i++)
    {
        distance[i]=INT32_MAX;
        visited[i]=false;
    }
    distance[startNode]=0;

    for (int counter=0; counter<FIELD_SIZE-1; counter++)
    {
        int min=INT32_MAX;
        for (int i=0; i<FIELD_SIZE; i++)
            if (!visited[i] && distance[i]<=min)
            {
                min=distance[i]; 
                index=i;
            }
        u=index;
        visited[u]=true;
        for (int i=0; i<FIELD_SIZE; i++)
            if (!visited[i] && table[u][i] && distance[u]!=INT32_MAX && distance[u]+table[u][i]<distance[i])
                { 
                    distance[i]=distance[u]+table[u][i];
                }
    }
    std::cout<<"Path length:\t\n";
    for (int i=0; i<FIELD_SIZE; i++) 
        if (distance[i]!=INT32_MAX)
        { 
            std::cout << m << " > " << i+1 << " = " << distance[i] <<std::endl;
       
        }
        else std::cout << m << " > " << i+1 << " = " << "no route " <<std::endl;
    }

int main()
{
    int s;
    int f;
    int table[FIELD_SIZE][FIELD_SIZE]={
    {0, 1, 2},
    {0, 1, 0},
    {4, 0, 0},
    };

    std::cin >> s;
    path(table,  s-1, f);
    return 0;

}