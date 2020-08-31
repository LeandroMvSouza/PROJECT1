#include <bits/stdc++.h>
#include <stdio.h>
#include <fstream>
#define MAX 999999999
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
//---------------------------------------------------------------------------
string pos_as_string(int posX,int posY){
	// Underline evita que sejam geradas chaves iguais para casas diferentes no tabuleiro (i.e. x=1;y=21 -> 1_21 || x=12;y=1 -> 12_1
	return ( to_string(posX) + "_" + to_string(posY) );
}

bool compare(const casa h1,const casa h2){
	return (h1.jump_steps < h2.jump_steps);
}
//---------------------------------------------------------------------------
casa mov_Esquerda(casa* start){
	casa aux = (*start);
	aux.posY -= start->jump_steps;
	aux.pos = pos_as_string(aux.posX,aux.posY);
	return aux;
}

casa mov_Direita(casa* start){
	casa aux = (*start);
	aux.posY += start->jump_steps;
	aux.pos = pos_as_string(aux.posX,aux.posY);
	return aux;
}

casa mov_Cima(casa* start){
	casa aux = (*start);
	aux.posX -= start->jump_steps;
	aux.pos = pos_as_string(aux.posX,aux.posY);
	return aux;
}

casa mov_Baixo(casa* start){
	casa aux = (*start);
	aux.posX += start->jump_steps;
	aux.pos = pos_as_string(aux.posX,aux.posY);
	return aux;
}
//---------------------------------------------------------------------------
void Graph::addEdge(casa node1, casa node2)
{
	string key = node1.pos;
	vector<casa> to_add = adjList[key];
	to_add.push_back(node2);
	adjList[key] = to_add;
}

void Graph::bfs(casa src,casa desired)
{	
	
	int added;
	int current = 0;
	int next = 0;
		
    queue<casa> q;
    map<string, bool> visited;
    q.push(src);
    visited[src.pos] = true;
    
	vector<casa> temporary;
	temporary.push_back(src);
    Graph::layers_set.push_back(temporary);
    
    temporary.clear();
    
    while(!q.empty())
    {
    	if(current==0)
		{
			added = 0;
        	casa node = q.front();
        	q.pop();
        	for(auto i = Graph::adjList[node.pos].begin(); i != Graph::adjList[node.pos].end(); i++)
        	{
        		string aux = (*i).pos;
        		if(!visited[aux])
				{
					visited[aux]=true;
					q.push(*i);
					temporary.push_back(*i);
					added+=1;
					if((*i).pos == desired.pos)
					{
						Graph::can_win = true;
					}
				}
			}
			next += added;
			current = next - 1;
			next = 0;
			
			Graph::layers_set.push_back(temporary);
			
			if(Graph::can_win){
				Graph::turns_it_takes_to_win = Graph::layers_set.size() - 1;
    			break;
			}
			temporary.clear();
		}
		else if(current>0)
		{
			added = 0;
        	casa node = q.front();
        	q.pop();
        	for(auto i = Graph::adjList[node.pos].begin(); i != Graph::adjList[node.pos].end(); i++)
        	{
        		string aux = (*i).pos;
        		if(!visited[aux])
				{
					visited[aux]=true;
					q.push(*i);
					temporary.push_back(*i);
					added+=1;
					if((*i).pos == desired.pos)
					{
						Graph::can_win = true;
					}
				}
			}
			next+=added;
			current-=1;
		}
    }
}
//---------------------------------------------------------------------------

int main(/*int argc,char* argv []*/)
{
	/*
	if(argc>1)
	{
	*/
		ifstream entrada;
		entrada.open("EX5");
		if (!entrada) {
    		cerr << "Nao foi possivel abrir o arquivo";
    		exit(1);
		}
		int N,M,K;
		int posX,posY;
		int pulos;
		int count = 0; // Contador para jogadores relevantes
		
		entrada>>N>>M;
		entrada>>K;
		
		Graph g;
		casa goal;
		casa from_vertex;
		casa to_vertex;
		
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++)
			{
				entrada>>pulos;
				casa *to_add = new casa;
				to_add->jump_steps = pulos;
				to_add->posX = i;
				to_add->posY = j;
				to_add->pos = pos_as_string(i,j);
				
				if((i==N-1) and (j==M-1)){
					goal = (*to_add);
				}

				from_vertex = (*to_add);
				// Esquerda (-y)
				if( (to_add->posY - to_add->jump_steps) >= 0 )
				{
					to_vertex = mov_Esquerda(to_add);
					g.addEdge(from_vertex,to_vertex);
				}
				// Direita (+y)
				if( (to_add->posY + to_add->jump_steps) <= (M-1) )
				{
					to_vertex = mov_Direita(to_add);
					g.addEdge(from_vertex,to_vertex);
				}
				// Cima (-x)
				if( ((to_add->posX - to_add->jump_steps) >= 0) and (N>1) )
				{
					to_vertex = mov_Cima(to_add);
					g.addEdge(from_vertex,to_vertex);
				}
				// Baixo (+x)
				if( ((to_add->posX + to_add->jump_steps) <= (N-1)) and (N>1))
				{
					to_vertex = mov_Baixo(to_add);
					g.addEdge(from_vertex,to_vertex);
				}
				free(to_add);
			}
		}
		
		Graph Player[K];		
		int min = MAX; // Esse inteiro armazenará o menor número de turnos necessários para que um jogador ganhe o jogo. Inicialmente atribuímos à ele um valor arbitrariamente grande MAX

		for(int i = 0;i<K;i++){ // Gerando o conjunto de layers de cada jogador e descobrindo qual o número mínimo de turnos necessários para alguém ganhar
			Player[i].player_id = i;
			Player[i].adjList = g.adjList;
			
			entrada>>posX>>posY;
			casa* to_add = new casa;
			to_add->posX = posX;
			to_add->posY = posY;
			to_add->pos = pos_as_string(posX,posY);
			
			Player[i].bfs( (*to_add) ,goal);
			
			if(Player[i].turns_it_takes_to_win < min)
			{
				min = Player[i].turns_it_takes_to_win;
			}
			free(to_add);
		}
		// Fechando o arquivo de entrada, uma vez que ele já foi percorrido
		entrada.close();
		
		vector<Graph> Relevant_Players;
		for(int i = 0;i<K;i++){
			if((Player[i].turns_it_takes_to_win == min) and (Player[i].can_win))
			{
				Relevant_Players.push_back(Player[i]);
				count+=1;
			}
		}
		
		if(count==0){
			cout<<"SEM VENCEDORES"<<endl;
		}
		
		else{
			vector<casa> aux;
			casa winner;
			bool found;
			int num_players = Relevant_Players.size();
			int num_houses;
			int count_while = 0;
			while(!found){
				for(int i=0;i < num_players;i++){
				
					num_houses = Relevant_Players[i].layers_set[min-count_while].size();
					
					for(int j=0;j < num_houses;j++)
					{
						Relevant_Players[i].layers_set[min-count_while][j].player_id = Relevant_Players[i].player_id;
						aux.push_back(Relevant_Players[i].layers_set[min-count_while][j]);
					}
				}
				
				sort(aux.begin(),aux.end(),compare);
				for(long unsigned int i=0 ; i<aux.size() ; i++){
					for(long unsigned int j=1 ; j<aux.size()-i ; j++)
					{
						if( (aux[i].player_id!=aux[j].player_id) and (aux[i].jump_steps<aux[j].jump_steps) ){
							winner = aux[i];
							found = true;
							break;
						}
					}
					if(found){
						break;
					}
				}
				aux.clear();
				count_while+=1;
			}
			
			int ascii_rep = winner.player_id+65;
			printf("%c",ascii_rep);
			cout<<endl<<min<<endl;
		}
	//}
	return 0; 
}
