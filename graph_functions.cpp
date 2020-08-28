#include "header.h"

void Graph::addEdge(casa node1, casa node2)
{
	string key = node1.pos;
	vector<casa> to_add = adjList[key];
	to_add.push_back(node2);
	adjList[key] = to_add;
    //adjList[node1.pos].push_back(node2);

}

void Graph::bfs(casa src,casa desired)
{	
	int count_while=0;
	int count_for=0;
	//int count_layer=0;
	
    queue<casa> q;
    map<string, bool> visited;
    q.push(src);
    visited[src.pos] = true;
    // ad src to Graph::Layer[count_layer];
    // count_layer++;
    
    while(!q.empty())
    {
    	count_while+=1;
    	cout<<"---------------------------------------------------------------------------------"<<endl;
    	cout<<"While loop : "<<count_while<<endl;
        casa node = q.front();
        cout <<"Node = "<< node.pos <<endl;
        cout<<"Estamos na lista de adjacencia de "<<node.pos<<endl;
        q.pop();
        for(auto i = adjList[node.pos].begin(); i != adjList[node.pos].end(); i++)
        {
        	count_for+=1;
        	string aux = (*i).pos;
        	cout<<"Item "<<count_for<<" da lista = "<<aux<<endl;
        	if(!visited[aux])
			{
				cout<<aux<<" nao foi visitado! Marcando-o como visitado e colocando-o na queue."<<endl;
				visited[aux]=true;
				q.push(*i);
				// add *i to Graph::Layer[count_layer]
				// count_layer++;
			}
		}
		count_for=0;
    }
    
}
