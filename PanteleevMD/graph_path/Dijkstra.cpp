//#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

#define FIELD_SIZE 6


void Dijkstra(int graphTable[FIELD_SIZE][FIELD_SIZE], int startNode, int finish)
{
    int distance[FIELD_SIZE], index, u;
    int m=startNode+1;
    vector<int> thePath[FIELD_SIZE];

    bool visited[FIELD_SIZE];
    for (int i=0; i<FIELD_SIZE; i++)
    {
        distance[i]=INT_MAX;
        visited[i]=false;
    }
    distance[startNode]=0;

    for (int counter=0; counter<FIELD_SIZE-1; counter++)
    {
        int min=INT_MAX;
        for (int i=0; i<FIELD_SIZE; i++)
            if (!visited[i] && distance[i]<=min)
            {
                min=distance[i]; 
                index=i;
            }
        u=index;
        visited[u]=true;
        for (int i=0; i<FIELD_SIZE; i++)
            if (!visited[i] && graphTable[u][i] && distance[u]!=INT_MAX && distance[u]+graphTable[u][i]<distance[i])
                { 
                    distance[i]=distance[u]+graphTable[u][i];
                    //thePath[counter].push_back(u);
                }
    }
    cout<<"Path length:\t\n";
    for (int i=0; i<FIELD_SIZE; i++) 
        if (distance[i]!=INT_MAX)
        { 
            cout << m << " > " << i+1 << " = " << distance[i] <<endl;
        //2    for (int j = 0; j < thePath[i].size(); j++)
        //    {
        //        cout << thePath[i][j] << ' ';
        //        thePath[i].pop_back();
        //    }
        //    cout << endl;
        }
        else cout << m << " > " << i+1 << " = " << "no route " <<endl;
    }

int main()
{
    int start;
    int finish;
    int graphTable[FIELD_SIZE][FIELD_SIZE]={
    {0, 1, 4, 0, 2, 0},
    {0, 0, 0, 9, 0, 0},
    {4, 0, 0, 7, 0, 0},
    {0, 9, 7, 0, 0, 2},
    {0, 0, 0, 0, 0, 8},
    {0, 0, 0, 0, 0, 0}};
    cout<<"Specify starting node >> ";
    cin >> start;
    //cout << "Where do you want to get? >> ";
    //cin >> finish;
    Dijkstra(graphTable, start-1, finish);
    return 0;
}