#ifndef HEADER_H
#define HEADER_H

#include <bits/stdc++.h>
#include <stdio.h>
#include <fstream>

using namespace std;

typedef struct casa{
	int jump_steps;
	int posX;
	int posY;
	string pos;
	int player_id;
}casa;

typedef struct vector<vector<casa>> layers;

class Graph
{
public:
    map<string,vector<casa> > adjList;
    void addEdge(casa node1, casa node2);
    void bfs(casa src,casa desired);
    
    int turns_it_takes_to_win;
    int player_id;
    
    bool can_win = false;
    layers layers_set;
};

// Auxiliary Functions
string pos_as_string(int posX,int posY);
bool compare(const casa h1,const casa h2);
// Movement Functions
casa mov_Esquerda(casa* start);
casa mov_Direita(casa* start);
casa mov_Cima(casa* start);
casa mov_Baixo(casa* start);
#endif
