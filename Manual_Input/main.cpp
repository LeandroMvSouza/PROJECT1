#include "header.h"
int main()
{
	int N,M,K;
	int posX,posY;
	int count = 0; // Contador para jogadores relevantes
	
	/*
	cout<<"Entre a dimensao do tabuleiro"<<endl;
	*/
	cin>>N>>M;
	/*
	cout<<"Entre o numero de jogadores"<<endl;
	*/
	cin>>K;
	
	casa tabuleiro[N][M];
	Graph g;
	casa goal;
	casa from_vertex;
	casa to_vertex;
	
	/*
	cout<<"Preencha cada casa do tabuleiro"<<endl;
	*/
	if(N==1){ // Nesse caso, cada casa com jump_steps>0 comporta no m�ximo 2 movimentos poss�veis -> para esquerda; para direita
		for(int j=0;j<M;j++)
		{
			cin>>tabuleiro[0][j].jump_steps;
			tabuleiro[0][j].posX=0;
			tabuleiro[0][j].posY=j;
			tabuleiro[0][j].pos = pos_as_string(tabuleiro[0][j]);
			
			from_vertex = tabuleiro[0][j];
			
			// Esquerda (-y)
			if( (tabuleiro[0][j].posY - tabuleiro[0][j].jump_steps) >= 0 )
			{
				to_vertex = mov_Esquerda(tabuleiro[0][j]);
				g.addEdge(from_vertex,to_vertex);
			}
			// Direita (+y)
			if( (tabuleiro[0][j].posY + tabuleiro[0][j].jump_steps) <= (M-1) )
			{
				to_vertex = mov_Direita(tabuleiro[0][j]);
				g.addEdge(from_vertex,to_vertex);
			}
		}
		goal = tabuleiro[N-1][M-1];
	}
	
	if(N>1){ // Nesse caso, cada casa com jump_steps>0 comporta 4 movimentos poss�veis -> para esquerda; para direita; para cima; para baixo
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				cin>>tabuleiro[i][j].jump_steps;
				tabuleiro[i][j].posX=i;
				tabuleiro[i][j].posY=j;
				tabuleiro[i][j].pos = pos_as_string(tabuleiro[i][j]);
			
				from_vertex = tabuleiro[i][j];
				// Esquerda (-y)
				if( (tabuleiro[i][j].posY - tabuleiro[i][j].jump_steps) >= 0 )
				{
					to_vertex = mov_Esquerda(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
				// Direita (+y)
				if( (tabuleiro[i][j].posY + tabuleiro[i][j].jump_steps) <= (M-1) )
				{
					to_vertex = mov_Direita(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
				// Cima (-x)
				if( (tabuleiro[i][j].posX - tabuleiro[i][j].jump_steps) >= 0 )
				{
					to_vertex = mov_Cima(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
				// Baixo (+x)
				if( (tabuleiro[i][j].posX + tabuleiro[i][j].jump_steps) <= (N-1) )
				{
					to_vertex = mov_Baixo(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
			}
		}
		goal = tabuleiro[N-1][M-1];
	}
	
	Graph Player[K];
	goal = tabuleiro[N-1][M-1];
			
	char jogador = int_as_char(0);
	Player[0].player_id = jogador;
	Player[0].adjList = g.adjList;
	/*
	cout<<endl<<"Entre a casa em que o jogador "<<jogador<<" ira comecar :";
	*/
	cin>>posX>>posY;
	Player[0].bfs(tabuleiro[posX][posY],goal);
	
	int min; // minimum number of turns it takes to win
	min = Player[0].turns_it_takes_to_win;
	
	for(int i = 1;i<K;i++){ // Gerando o conjunto de layers de cada jogador e descobrindo qual o n�mero m�nimo de turnos necess�rios para algu�m ganhar
		jogador = int_as_char(i);
		Player[i].player_id = jogador;
		Player[i].adjList = g.adjList;
		/*
		cout<<endl<<"Entre a casa em que o jogador "<<jogador<<" ira comecar :";
		*/
		cin>>posX>>posY;
		Player[i].bfs(tabuleiro[posX][posY],goal);

		if(Player[i].turns_it_takes_to_win < min)
		{
			min = Player[i].turns_it_takes_to_win;
		}
		/*
		cout<<"===================================="<<endl;
		cout<<"===================================="<<endl;
		*/
	}
	
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
		/*
		cout<<"Temos "<<Relevant_Players.size()<<" jogadores relevantes!"<<endl;
		cout<<"Rodada final = "<<min<<endl;
		*/
		while(!found){
			cout<<"==========While_Loop -> "<<count_while<<" ============"<<endl;
			for(int i=0;i < num_players;i++){
			
				num_houses = Relevant_Players[i].layers_set[min-count_while].size();
				
				for(int j=0;j < num_houses;j++)
				{
					Relevant_Players[i].layers_set[min-count_while][j].player_id = Relevant_Players[i].player_id;
					aux.push_back(Relevant_Players[i].layers_set[min-count_while][j]);
				}
			}
			
			sort(aux.begin(),aux.end(),compare);
			
			cout<<"Printando aux :"<<endl;
			for(int i = 0;i<aux.size();i++){
				cout<<"aux["<<i<<"] -> player_id = "<<aux[i].player_id<<" jump_steps = "<<aux[i].jump_steps<<endl;
			}
			
			for(int i = 0;i < aux.size();i++){
				for(int j=1;j<aux.size()-i;j++)
				{
					if( (aux[i].player_id!=aux[j].player_id) and (aux[i].jump_steps<aux[j].jump_steps) ){
						winner = aux[i];
						found = true;
						break;
					}
				}
				if(found){break;}
			}
			aux.clear();
			count_while+=1;
			cout<<"***************************************"<<endl;
			cout<<"======================================="<<endl;
		}
		cout<<winner.player_id<<endl;
		cout<<min<<endl;
	}
	
    return 0;
}
