#include <bits/stdc++.h>

using namespace std;

typedef struct casa{
	int jump_steps;
	int posX;
	int posY;
	string pos;
}casa;

string pos_as_string(casa start){
	return ( to_string(start.posX) + "_" + to_string(start.posY) );
}

int main(){
	map<string,vector<casa> > adjList;
	
	// adjList[string] = vector<casa>;
	
	// criando uma casa
	casa to_add;
	to_add.jump_steps = 4;
	to_add.posX = 0;
	to_add.posY = 0;
	to_add.pos = pos_as_string(to_add);
	// criando um vetor de casas
	vector<casa> teste;
	teste.push_back(to_add);
	// agora podemos inserir o vetor de casas no mapa
	adjList[to_add.pos] = teste;
	// yAy!!!
	cout<<adjList[to_add.pos][0].pos<<endl;
	// ----- TESTE2 ------
	casa yay = to_add;
	yay.pos = "OMG";
	teste.push_back(yay);
	adjList[to_add.pos] = teste;
	// -----
	cout<<adjList[to_add.pos][0].pos<<endl;
	cout<<adjList[to_add.pos][1].pos<<endl;
	// ----- TESTE3 ------
	casa node2 = to_add;
	node2.pos = "BBQ";
	vector<casa> adding = adjList[to_add.pos];
	adding.push_back(node2);
	adjList[to_add.pos] = adding;
	// -----
	cout<<adjList[to_add.pos][0].pos<<endl;
	cout<<adjList[to_add.pos][1].pos<<endl;
	cout<<adjList[to_add.pos][2].pos<<endl;
	// ----- TESTE 4 ------
	queue<casa> q;
	int count_for;
	for(auto i = adjList[to_add.pos].begin(); i != adjList[to_add.pos].end(); i++){
		count_for+=1;
		string aux = (*i).pos;
        cout<<"Item "<<count_for<<" da lista de adjacencia -> "<<aux<<endl;
        q.push(*i);
	}
	count_for = 0;
	// -----
	cout<<"q.front() = "<<q.front().pos<<endl;
	cout<<"q.back() = "<<q.back().pos<<endl;
	// ----------------------------------------------------------------------------
}
