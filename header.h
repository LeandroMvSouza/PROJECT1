#ifndef HEADER_H
#define HEADER_H

#include <bits/stdc++.h>

#define MAX 10

using namespace std;

typedef struct casa{
	int jump_steps;
	int posX;
	int posY;
	string pos;
}casa;

class Graph
{
public:
    map<string,vector<casa> > adjList;
    void addEdge(casa node1, casa node2);
    void bfs(casa src,casa desired);
    
    //void add_Casa
    //vector<casa> Layer[MAX];
};

string pos_as_string(casa start);
casa mov_Esquerda(casa start);
casa mov_Direita(casa start);
casa mov_Cima(casa start);
casa mov_Baixo(casa start);
#endif
