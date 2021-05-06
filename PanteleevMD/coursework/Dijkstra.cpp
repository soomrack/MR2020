//#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <string>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::microseconds;

#define FIELD_SIZE 6
#define MAX_SIZE 4000

int graphTable[MAX_SIZE][MAX_SIZE]={0};
int controlTable[MAX_SIZE][MAX_SIZE]={0};

void Dijkstra(int graphTable[MAX_SIZE][MAX_SIZE], int startNode, int fieldSize);

std::string Measure()
{
    std::string plotData = "{\"kind\":{ \"plotly\": true },\"data\":[{";
    std::string plotSize = "\"x\": [";
    std::string plotTime = "\"y\": [";
    const int maxSize = MAX_SIZE;
    int times[maxSize];

    for (int y = 0; y < MAX_SIZE; y++)
    {
        for (int x = 0; x < MAX_SIZE; x++)
        {
            int prob = std::rand() % 10;
            if (prob < 2 )     // 20% to generate a connection
            {   //&& graphTable[y][x] == 0 
                int weight = std::rand() % 10+1;
                graphTable[x][y] = weight;
                if (prob < 1)       // 10% to generate bi-directional connection
                {
                    graphTable[y][x] = weight;
                }
            }
        }
    }

    for (int size = 10; size < maxSize; size+=10)
    {
        auto t1 = steady_clock::now();
        Dijkstra(graphTable, 0, size);
        auto t2 = steady_clock::now();
        auto ms_int1 = duration_cast<microseconds>(t2 - t1);

        auto t3 = steady_clock::now();
        Dijkstra(graphTable, size/2, size);
        auto t4 = steady_clock::now();
        auto ms_int2 = duration_cast<microseconds>(t4 - t3);

        auto t5 = steady_clock::now();
        Dijkstra(graphTable, size-1, size);
        auto t6 = steady_clock::now();
        auto ms_int3 = duration_cast<microseconds>(t6 - t5);

        auto ms_int = (ms_int1 + ms_int2 + ms_int3)/3;
        //times[size] = ms_int.count();
        //duration<double, std::milli> ms_double = t2 - t1;
        plotTime += std::to_string(ms_int.count()) + ", ";
        plotSize += std::to_string(size) + ", ";

        std::cout << size << " ";

    }
    plotTime = plotTime.substr(0, plotTime.length()-2);
    plotTime += "],";
    plotSize = plotSize.substr(0, plotSize.length()-2);
    plotSize += "],";
    plotData += plotSize + plotTime + "\"layout\": {\"title\": \"Dijktra's execution time\"}";
    plotData += "}]}";

    return plotData;
}

void Dijkstra(int graphTable[MAX_SIZE][MAX_SIZE], int startNode, int fieldSize)
{
    int distance[MAX_SIZE];
    bool visited[MAX_SIZE];

    for (int i=0; i<fieldSize; i++)
    {
        distance[i]=INT_MAX;
        visited[i]=false;
    }
    distance[startNode]=0;
    int curNode = 0;
    
    for (int counter=0; counter<fieldSize-1; counter++)
    {
        int minDistance=INT_MAX;
        int minIndex = 0;
        for (int i=0; i<fieldSize; i++)
            if (!visited[i] && distance[i]<=minDistance)
            {
                minDistance=distance[i]; 
                minIndex=i;
            }
        curNode=minIndex;
        visited[curNode]=true;
        for (int i=0; i<fieldSize; i++)
            if (!visited[i] && graphTable[curNode][i] && distance[curNode]!=INT_MAX && distance[curNode]+graphTable[curNode][i]<distance[i])
                { 
                    distance[i]=distance[curNode]+graphTable[curNode][i];
                }
    }
}

void DijkstraVerbose(int graphTable[6][6], int startNode, int fieldSize)
{
    int distance[MAX_SIZE];
    bool visited[MAX_SIZE];

    for (int i=0; i<fieldSize; i++)
    {
        distance[i]=INT_MAX;
        visited[i]=false;
    }
    distance[startNode]=0;
    int curNode = 0;
    
    for (int counter=0; counter<fieldSize-1; counter++)
    {
        int minDistance=INT_MAX;
        int minIndex = 0;
        for (int i=0; i<fieldSize; i++)
            if (!visited[i] && distance[i]<=minDistance)
            {
                minDistance=distance[i]; 
                minIndex=i;
            }
        curNode=minIndex;
        visited[curNode]=true;
        for (int i=0; i<fieldSize; i++)
            if (!visited[i] && graphTable[curNode][i] && distance[curNode]!=INT_MAX && distance[curNode]+graphTable[curNode][i]<distance[i])
                { 
                    distance[i]=distance[curNode]+graphTable[curNode][i];
                }
    }
    std::cout<<"Path length:\t\n";
    for (int i=0; i<FIELD_SIZE; i++) 
        if (distance[i]!=INT_MAX)
        { 
             std::cout << startNode << " -> " << i << " = " << distance[i] << std::endl;
        }
        else std::cout << startNode << " -> " << i << " = " << "no route " << std::endl;
}



int main()
{
    int start;
    int testTable[FIELD_SIZE][FIELD_SIZE]={
    {0, 1, 4, 0, 2, 0},
    {0, 0, 0, 9, 0, 0},
    {4, 0, 0, 7, 0, 0},
    {0, 9, 7, 0, 0, 2},
    {0, 0, 0, 0, 0, 8},
    {0, 0, 0, 0, 0, 0}};
    DijkstraVerbose(testTable, 0, 6);

    std::string plot = Measure();
    std::cout<<plot;
    
    //Dijkstra(graphTable, start);
    return 0;
}