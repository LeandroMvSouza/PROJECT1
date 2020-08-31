#include "header.h"

#define MAX 999999999

int main(int argc,char* argv [])
{
	if(argc>1)
	{
		ifstream entrada;
		entrada.open(argv[1]);
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
		
		casa tabuleiro[N][M];
		Graph g;
		casa goal;
		casa from_vertex;
		casa to_vertex;
		
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++)
			{
				entrada>>pulos;
				tabuleiro[i][j].jump_steps = pulos;
				//entrada>>tabuleiro[i][j].jump_steps;
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
				if( ((tabuleiro[i][j].posX - tabuleiro[i][j].jump_steps) >= 0) and (N>1) )
				{
					to_vertex = mov_Cima(tabuleiro[i][j]);
						g.addEdge(from_vertex,to_vertex);
				}
				// Baixo (+x)
				if( ((tabuleiro[i][j].posX + tabuleiro[i][j].jump_steps) <= (N-1)) and (N>1))
				{
					to_vertex = mov_Baixo(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
			}
		}
		goal = tabuleiro[N-1][M-1];		
		Graph Player[K];
				
		int min = MAX; // Esse inteiro armazenará o menor número de turnos necessários para que um jogador ganhe o jogo. Inicialmente atribuímos à ele um valor arbitrariamente grande MAX

		for(int i = 0;i<K;i++){ // Gerando o conjunto de layers de cada jogador e descobrindo qual o número mínimo de turnos necessários para alguém ganhar
			Player[i].player_id = i;
			Player[i].adjList = g.adjList;

			entrada>>posX>>posY;
			Player[i].bfs(tabuleiro[posX][posY],goal);
			
			if(Player[i].turns_it_takes_to_win < min)
			{
				min = Player[i].turns_it_takes_to_win;
			}
			//
			cout<<"====================================END===================================="<<endl;
			cout<<"================================NEXT_PLAYER================================"<<endl;
			//
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
			//
			cout<<"Temos "<<Relevant_Players.size()<<" jogadores relevantes!"<<endl;
			cout<<"Rodada final = "<<min<<endl;
			//
			while(!found){
				//
				cout<<"==========While_Loop -> "<<count_while<<" ============"<<endl;
				//
				for(int i=0;i < num_players;i++){
				
					num_houses = Relevant_Players[i].layers_set[min-count_while].size();
					
					for(int j=0;j < num_houses;j++)
					{
						Relevant_Players[i].layers_set[min-count_while][j].player_id = Relevant_Players[i].player_id;
						aux.push_back(Relevant_Players[i].layers_set[min-count_while][j]);
					}
				}
				
				sort(aux.begin(),aux.end(),compare);
				//
				cout<<"Printando aux :"<<endl;
				for(unsigned long int i = 0;i<aux.size();i++){
					cout<<"aux["<<i<<"] -> player_id = "<<aux[i].player_id<<" jump_steps = "<<aux[i].jump_steps<<endl;
				}
				//
				for(long unsigned int i = 0;i < aux.size();i++){
					for(long unsigned int j=1;j<aux.size()-i;j++)
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
				//
				cout<<"***************************************"<<endl;
				cout<<"======================================="<<endl;
				//
			}
			
			int ascii_rep = winner.player_id+65;
			printf("%c",ascii_rep);
			cout<<endl<<min<<endl;
		}
	}
	return 0; 
}
