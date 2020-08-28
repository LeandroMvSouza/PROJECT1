#include "header.h"
int main()
{
	int N,M,K;
	int posX,posY;
	int cant_win,stuck;
	
	cout<<"Entre a dimensao do tabuleiro"<<endl;
	cin>>N>>M;
	cout<<"Entre o numero de jogadores"<<endl;
	cin>>K;
	
	casa tabuleiro[N][M];
	Graph g;
	casa goal;
	
	cout<<"Preencha cada casa do tabuleiro"<<endl;
	if(N==1){ // Nesse caso, cada casa com jump_steps>0 comporta no máximo 2 movimentos possíveis -> para esquerda; para direita
		casa from_vertex;
		casa to_vertex;
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
		cout<<endl;
	}
	
	if(N>1){ // Nesse caso, cada casa com jump_steps>0 comporta 4 movimentos possíveis -> para esquerda; para direita; para cima; para baixo
		casa from_vertex;
		casa to_vertex;
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
					to_vertex = mov_Cima(tabuleiro[i][j]);
					g.addEdge(from_vertex,to_vertex);
				}
			}
		}
		goal = tabuleiro[N-1][M-1];
		cout<<endl;
	}
	
	cout<<endl<<"Entre a casa em que o jogador ira comecar :";
	cin>>posX>>posY;
	g.bfs(tabuleiro[posX][posY],goal);
	
	/*// Printar os Layers de cada um dos jogadores
	for(int i = 0;i<K;i++){
		for(int j=0;j<K;j++){
			for(auto t = Layers[i][j].begin(); t != Layers[i][j].end(); t++){
				cout<<*t;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	*/
	
	/*// Printar Tabuleiro
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cout<<tabuleiro[i][j].pos<<" jump_steps="<<tabuleiro[i][j].jump_steps<<";\t";
		}
		cout<<endl;
	}
	*/
    return 0;
}
